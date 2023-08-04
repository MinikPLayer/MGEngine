#include "Camera.h"
#include "Config.h"
#include "Log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void Camera::set_main_camera(std::shared_ptr<Camera> camera) {
	mainCamera = camera;
}

std::shared_ptr<Camera> Camera::get_main_camera() {
#if SC_FATAL_ON
	if (mainCamera == nullptr) {
		ELOG_FATAL("Trying to get main camera, but main camera is not set / null");
		exit(1);
	}
#endif

	return mainCamera;
}

std::shared_ptr<Camera> Camera::create_default() {
	Camera* cam = new Camera();
	cam->clearColor = Color(0.53f, 0.81f, 0.92f);
	cam->transform.set_position(Vector3<float>(0, 0, -5));
	return std::shared_ptr<Camera>(cam);
}

// TODO: Implement dirty / clean system, so we don't have to recalculate the VP matrix every frame
glm::mat4 Camera::get_VP_matrix(float aspect_ratio) {
#if SC_ERROR_ON
	if (aspect_ratio < 0 && this->aspectRatio < 0) {
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

std::shared_ptr<Camera> Camera::mainCamera = nullptr;