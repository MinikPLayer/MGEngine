#include "MatrixUtils.hpp"
#include "Vector3.hpp"

glm::vec3 MatrixUtils::GetTranslation(glm::mat4 matrix) {
	return glm::vec3(matrix[3]);
}

glm::vec3 MatrixUtils::GetScale(glm::mat4 matrix) {
	return glm::vec3(
		Vector3<float>(matrix[0]).magnitude(),
		Vector3<float>(matrix[1]).magnitude(),
		Vector3<float>(matrix[2]).magnitude()
	);
}

glm::quat MatrixUtils::GetRotation(glm::mat4 matrix, glm::vec3 scale) {
	auto c0 = matrix[0] / scale.x;
	c0[3] = 0;

	auto c1 = matrix[1] / scale.y;
	c1[3] = 0;

	auto c2 = matrix[2] / scale.z;
	c2[3] = 0;

	auto c3 = glm::vec4(0, 0, 0, 1);
	return glm::quat(glm::mat4(c0, c1, c2, c3));
}

glm::quat MatrixUtils::GetRotation(glm::mat4 matrix) {
	return GetRotation(matrix, GetScale(matrix));
}

// Based on https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
DecomposedMatrix MatrixUtils::DecomposeMatrix(glm::mat4 matrix) {
	glm::vec3 pos = GetTranslation(matrix);
	glm::vec3 scale = GetScale(matrix);
	glm::quat rotation = GetRotation(matrix, scale);

	return DecomposedMatrix(pos, scale, rotation);
}
