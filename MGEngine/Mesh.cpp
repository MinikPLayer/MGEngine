#include "Mesh.h"

std::vector<std::weak_ptr<Mesh>> Mesh::__meshes;

#if USE_GL
void Mesh::init_renderer() {
	VAO = -1;
	VBO = -1;
	EBO = -1;

	glGenVertexArrays(1, &VAO.get());
	glGenBuffers(1, &VBO.get());
	glGenBuffers(1, &EBO.get());

	update_renderer();
}

void Mesh::update_renderer() {
	glBindVertexArray(VAO.get());

	glBindBuffer(GL_ARRAY_BUFFER, VBO.get());
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO.get());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
	needsRendererUpdate = false;
}

void Mesh::draw(Shader& currentShader) {
	if (needsRendererUpdate)
		update_renderer();

	// Setup model matrices
	auto modelMatrix = get_model_matrix();
	currentShader.set_uniform_mat4f(currentShader.modelUniformLocation, modelMatrix);
	// TODO: Definitely add caching
	currentShader.set_uniform_mat4f(currentShader.modelInversedUniformLocation, glm::inverse(modelMatrix));

	glBindVertexArray(VAO.get());
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
#endif

void Mesh::start() {
	__meshes.push_back(std::static_pointer_cast<Mesh>(get_self_ptr().lock()));
}

Mesh::~Mesh() {
	// Remove from meshes list
	for (auto it = __meshes.begin(); it != __meshes.end(); it++) {
		if (it->lock().get() == this) {
			__meshes.erase(it);
			break;
		}
	}
}