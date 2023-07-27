#pragma once
#include <vector>
#include "Vector3.h"
#include "Vector2.h"
#include "Config.h"

struct Vertex {
	Vector3<float> position;
	Vector3<float> normal;
	Vector2<float> uv;
};

class Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	bool needsRendererUpdate = true;

#if USE_GL
	GL_VAO VAO = -1;
	GL_VBO VBO = -1;
	GL_EBO EBO = -1;

	void initRenderer() {
		VAO.dispose();
		VBO.dispose();
		EBO.dispose();

		glGenVertexArrays(1, &VAO.get());
		glGenBuffers(1, &VBO.get());
		glGenBuffers(1, &EBO.get());

		updateRenderer();
	}

	void updateRenderer() {
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
#endif

public:
	// Disable copy constructor 
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh() { initRenderer(); }
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices) { initRenderer(); }
};

