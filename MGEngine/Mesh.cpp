#include "Mesh.h"

std::vector<std::weak_ptr<Mesh>> Mesh::__meshes;

#if USE_GL
void Mesh::draw(Shader& currentShader) {
	if (needsRendererUpdate)
		update_renderer();

	// Setup model matrices
	currentShader.set_uniform_mat4f(currentShader.modelUniformLocation, get_model_matrix());
	glBindVertexArray(VAO.get());
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
#endif
