#include "Camera.h"
#include "Config.h"
#include "Log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#if USE_GL
#include "GLFWInput.h"
#endif
#include "TimeUtils.h"

void Camera::SetMainCamera(std::shared_ptr<Camera> camera) {
	mainCamera = camera;
}

std::shared_ptr<Camera> Camera::GetMainCamera() {
#if SC_FATAL_ON
	if (mainCamera == nullptr) {
		ELOG_FATAL("Trying to get main camera, but main camera is not set / null");
		exit(1);
	}
#endif

	return mainCamera;
}

std::shared_ptr<Camera> Camera::CreateDefault() {
	Camera* cam = new Camera();
	cam->clearColor = Color(0.53f, 0.81f, 0.92f);
	cam->transform.set_position(Vector3<float>(0, 0, -5));
	return std::shared_ptr<Camera>(cam);
}

// TODO: Implement dirty / clean system, so we don't have to recalculate the VP matrix every frame
glm::mat4 Camera::get_VP_matrix(float aspect_ratio) {
#if SC_ERROR_ON
	if (aspect_ratio <= 0 && this->aspectRatio <= 0) {
		ELOG_ERROR("Camera aspect ratio not set, and no aspect ratio provided as an argument");
		this->aspectRatio = 1;
	}
#endif
	if (aspect_ratio > 0)
		this->aspectRatio = aspect_ratio;

	auto viewMatrix = glm::lookAt(
		this->transform.get_position().to_glm(),
		this->transform.get_position().to_glm() + this->transform.get_forward_vector().to_glm(),
		this->transform.get_up_vector().to_glm()
	);

	auto projectionMatrix = glm::perspective(glm::radians(60.0f), this->aspectRatio, 0.1f, 100.0f);
	return projectionMatrix * viewMatrix;
}

void Camera::set_clear_color(Color color) {
	this->clearColor = color;
}

Color Camera::get_clear_color() {
	return this->clearColor;
}

void Camera::start() {
	forwardMapping = Input::register_mapping(InputMapping("CameraForward", Keyboard::KEY_W, Keyboard::KEY_S));
	sidewaysMapping = Input::register_mapping(InputMapping("CameraSideways", Keyboard::KEY_D, Keyboard::KEY_A));

	// rotateXMapping = Input::register_mapping(InputMapping("CameraRotateX", MouseAxis::X));
	// rotateYMapping = Input::register_mapping(InputMapping("CameraRotateY", MouseAxis::Y));
	rotateXMapping = Input::register_mapping(InputMapping("CameraRotateX", Keyboard::ARROW_RIGHT, Keyboard::ARROW_LEFT));
	rotateYMapping = Input::register_mapping(InputMapping("CameraRotateY", Keyboard::ARROW_UP, Keyboard::ARROW_DOWN));
}

void Camera::update() {
	auto rotation = this->transform.get_local_rotation();
	auto rotateX = Input::get(rotateXMapping).value().get_value() * 0.01f;
	auto rotateY = Input::get(rotateYMapping).value().get_value() * 0.01f;

	rotation = rotation.rotated_around(Vector3<float>(0, 1, 0), rotateX);
	rotation = rotation.rotated_around(rotation.right(), rotateY);
	this->transform.set_local_rotation(rotation);

	auto right = -Input::get(sidewaysMapping).value().get_value() * moveSpeed * Time::DeltaTime();
	auto forward = Input::get(forwardMapping).value().get_value() * moveSpeed * Time::DeltaTime();

	auto movement = rotation.forward() * forward + rotation.right() * right;
	this->transform.set_position(this->transform.get_position() + movement);

	auto localRot = this->transform.get_local_rotation();
	auto euler = localRot.to_euler();
	LOG_INFO("Camera rotation: ", euler.to_string());
}

std::shared_ptr<Camera> Camera::mainCamera = nullptr;