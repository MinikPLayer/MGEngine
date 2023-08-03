#pragma once
#include <vector>
#include "Vector3.h"
#include "Vector2.h"
#include "Config.h"
#include "GameObject.h"
#include "GLShader.h"

struct Vertex {
	Vector3<float> position;
	Vector3<float> normal;
	Vector2<float> uv;

	Vertex(Vector3<float> position, Vector3<float> normal, Vector2<float> uv) {
		this->position = position;
		this->normal = normal;
		this->uv = uv;
	}

	Vertex(float posX = 0, float posY = 0, float posZ = 0, float normX = 0, float normY = 0, float normZ = 0, float u = 0, float v = 0) {
		this->position = Vector3<float>(posX, posY, posZ);
		this->normal = Vector3<float>(normX, normY, normZ);
		this->uv = Vector2<float>(u, v);
	}
};

class Mesh : public GameObject {
public:
	static std::vector<std::weak_ptr<Mesh>> __meshes;

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	bool needsRendererUpdate = true;

#if USE_GL
	GL_VAO VAO = -1;
	GL_VBO VBO = -1;
	GL_EBO EBO = -1;

	void initRenderer() {
		VAO = -1;
		VBO = -1;
		EBO = -1;

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

	void Start() override {
		__meshes.push_back(std::static_pointer_cast<Mesh>(getSelfPtr().lock()));
	}

	void initialize() {
		initRenderer();
	}

	// TODO: Add dirty / clean based on transform changes
	glm::mat4 getModelMatrix() {
		return transform.getWorldSpaceMatrix();
	}
public:
#if USE_GL
	void draw(Shader& currentShader);
#endif

	// Disable copy constructor 
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh() { initialize(); }
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices) { initialize(); }

	~Mesh() {
		// Remove from meshes list
		for (auto it = __meshes.begin(); it != __meshes.end(); it++) {
			if (it->lock().get() == this) {
				__meshes.erase(it);
				break;
			}
		}
	}
};

