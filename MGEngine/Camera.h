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
	static void set_main_camera(std::shared_ptr<Camera> camera);
	static std::shared_ptr<Camera> get_main_camera();
	static std::shared_ptr<Camera> create_default();

	/// <summary>
	/// Calculates the view projection matrix for this camera
	/// </summary>
	/// <param name="aspect_ratio">Aspect ratio of current window / surface. Ignored if set to < 0</param>
	/// <returns>View projection matrix</returns>
	glm::mat4 get_VP_matrix(float aspect_ratio = -1);

	void set_clear_color(Color color);
	Color get_clear_color();

};

