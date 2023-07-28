#include "Mesh.h"

std::vector<std::weak_ptr<Mesh>> Mesh::__meshes;

#if USE_GL
void Mesh::draw() {
	if (needsRendererUpdate)
		updateRenderer();

	glBindVertexArray(VAO.get());
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
#endif
