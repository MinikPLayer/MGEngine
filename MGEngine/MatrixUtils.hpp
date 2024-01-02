#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class DecomposedMatrix {
public:
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;

	DecomposedMatrix(glm::vec3 pos, glm::vec3 scale, glm::quat rotation) {
		this->translation = pos;
		this->scale = scale;
		this->rotation = rotation;
	}
};

class MatrixUtils {
public:
	static glm::vec3 GetTranslation(glm::mat4 matrix);
	static glm::vec3 GetScale(glm::mat4 matrix);
	static glm::quat GetRotation(glm::mat4 matrix, glm::vec3 scale);
	static glm::quat GetRotation(glm::mat4 matrix);
	static DecomposedMatrix DecomposeMatrix(glm::mat4 matrix);
};