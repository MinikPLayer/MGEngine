#include "Camera.h"
#include "Config.h"
#include "Log.h"

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
	return cam;
}

void Camera::setClearColor(Color color) {
	this->clearColor = color;
}

Color Camera::getClearColor() {
	return this->clearColor;
}

std::shared_ptr<Camera> Camera::mainCamera = nullptr;