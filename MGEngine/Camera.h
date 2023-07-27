#pragma once
#include "Color.h"
#include <memory>
#include "GameObject.h"

class Camera : public GameObject {
	Color clearColor;
	static std::shared_ptr<Camera> mainCamera;
public:
	static void setMainCamera(std::shared_ptr<Camera> camera);
	static std::shared_ptr<Camera> getMainCamera();
	static Camera createDefault();

	void setClearColor(Color color);
	Color getClearColor();
};

