#pragma once
#include <vector>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Config.hpp"
#include "GameObject.hpp"
#include "GLShader.hpp"
#include "Material.hpp"

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
	static std::vector<std::shared_ptr<Mesh>> __meshes;
private:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	bool needsRendererUpdate = true;

	// TODO: Change to material
	//std::shared_ptr<IShader> customShader = nullptr;
	std::shared_ptr<Material> material = nullptr;

#if USE_GL
	GL_VAO VAO = -1;
	GL_VBO VBO = -1;
	GL_EBO EBO = -1;

	void init_renderer();

	void update_renderer();
#endif

	void start() override;
	void on_destroy() override;

	void initialize() {
		init_renderer();
	}

	// TODO: Add dirty / clean based on transform changes
	glm::mat4 get_model_matrix() {
		return transform.get_world_space_matrix();
	}
public:

	void set_material(std::shared_ptr<Material> mat) {
		this->material = mat;
	}

	std::shared_ptr<Material> get_material() {
		return this->material;
	}

	bool is_custom_material() {
		return this->material != nullptr;
	}

	// TODO: Move USE_GL to IMeshRenderer
#if USE_GL
	void draw(std::shared_ptr<GLShader> currentShader);
#endif

	// Disable copy constructor 
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh() { initialize(); }
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices) { initialize(); }
};

