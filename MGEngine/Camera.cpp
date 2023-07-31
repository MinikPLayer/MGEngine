#include "Camera.h"
#include "Config.h"
#include "Log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void Camera::setMainCamera(std::shared_ptr<Camera> camera) {
	mainCamera = camera;
}

std::shared_ptr<Camera> Camera::getMainCamera() {
#if SC_FATAL_ON
	if (mainCamera == nullptr) {
		ELOG_FATAL("Trying to get main camera, but main camera is not set / null");
		exit(1);
	}
#endif

	return mainCamera;
}

Camera Camera::createDefault() {
	Camera cam;
	cam.clearColor = Color(0.53f, 0.81f, 0.92f);
	cam.transform.setPosition(Vector3<float>(0, 0, -5));
	return cam;
}

// TODO: Implement dirty / clean system, so we don't have to recalculate the VP matrix every frame
glm::mat4 Camera::getVPMatrix(float aspectRatio) {
#if SC_ERROR_ON
	if (aspectRatio < 0 && this->aspectRatio < 0) {
		ELOG_ERROR("Camera aspect ratio not set, and no aspect ratio provided as an argument");
		this->aspectRatio = 1;
	}
#endif
	if (aspectRatio > 0)
		this->aspectRatio = aspectRatio;

	auto viewMatrix = glm::lookAt(
		this->transform.getPosition().toGlm(),
		this->transform.getPosition().toGlm() + this->transform.getForwardVector().toGlm(),
		this->transform.getUpVector().toGlm()
	);

	auto projectionMatrix = glm::perspective(glm::radians(45.0f), this->aspectRatio, 0.1f, 100.0f);
	return projectionMatrix * viewMatrix;
}

void Camera::setClearColor(Color color) {
	this->clearColor = color;
}

Color Camera::getClearColor() {
	return this->clearColor;
}

std::shared_ptr<Camera> Camera::mainCamera = nullptr;