#include "MatrixUtils.h"
#include "Vector3.h"

// Based on https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
DecomposedMatrix MatrixUtils::DecomposeMatrix(glm::mat4 matrix) {
	glm::vec3 pos(matrix[3]);
	glm::vec3 scale(
		Vector3<float>(matrix[0]).magnitude(),
		Vector3<float>(matrix[1]).magnitude(),
		Vector3<float>(matrix[2]).magnitude()
	);

	auto c0 = matrix[0] / scale.x;
	c0[3] = 0;

	auto c1 = matrix[1] / scale.y;
	c1[3] = 0;

	auto c2 = matrix[2] / scale.z;
	c2[3] = 0;

	auto c3 = glm::vec4(0, 0, 0, 1);
	glm::mat4 rot(c0, c1, c2, c3);

	return DecomposedMatrix(pos, scale, glm::quat(rot));
}
