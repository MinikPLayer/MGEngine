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
	static DecomposedMatrix DecomposeMatrix(glm::mat4 matrix);
};