#pragma once
#include "Color.h"
#include <memory>
#include "GameObject.h"
#include <glm/glm.hpp>

class Camera : public GameObject {
	Color clearColor;
	static std::shared_ptr<Camera> mainCamera;

	float aspectRatio = -1;
public:
	static void setMainCamera(std::shared_ptr<Camera> camera);
	static std::shared_ptr<Camera> getMainCamera();
	static std::shared_ptr<Camera> createDefault();

	/// <summary>
	/// Calculates the view projection matrix for this camera
	/// </summary>
	/// <param name="aspect_ratio">Aspect ratio of current window / surface. Ignored if set to < 0</param>
	/// <returns>View projection matrix</returns>
	glm::mat4 getVPMatrix(float aspect_ratio = -1);

	void setClearColor(Color color);
	Color getClearColor();
};

