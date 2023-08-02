#include "Mesh.h"

std::vector<std::weak_ptr<Mesh>> Mesh::__meshes;

#if USE_GL
void Mesh::draw(Shader& currentShader) {
	if (needsRendererUpdate)
		updateRenderer();

	// Setup model matrices
	currentShader.setUniformMat4f(currentShader.modelUniformLocation, getModelMatrix());
	glBindVertexArray(VAO.get());
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
#endif
