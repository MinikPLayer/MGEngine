#pragma once
#include "Color.hpp"
#include <memory>
#include "GameObject.hpp"
#include <glm/glm.hpp>

class Camera : public GameObject {
	Color clearColor;
	static std::shared_ptr<Camera> mainCamera;

	float aspectRatio = -1;

	int forwardMapping = -1;
	int sidewaysMapping = -1;

	int sprintMapping = -1;

	int rotateXMapping = -1;
	int rotateYMapping = -1;

	float moveSpeed = 10.f;
public:
	static void SetMainCamera(std::shared_ptr<Camera> camera);
	static std::shared_ptr<Camera> GetMainCamera();
	static std::shared_ptr<Camera> CreateDefault();

	/// <summary>
	/// Calculates the view projection matrix for this camera
	/// </summary>
	/// <param name="aspect_ratio">Aspect ratio of current window / surface. Ignored if set to < 0</param>
	/// <returns>View projection matrix</returns>
	glm::mat4 get_VP_matrix(float aspect_ratio = -1);

	void set_clear_color(Color color);
	Color get_clear_color();

	void start() override;
	void update() override;
};

