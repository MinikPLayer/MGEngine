#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class Model : public GameObject {
private:
	std::shared_ptr<IShader> custom_shader = nullptr;

	std::string path;
	// model data
	std::vector<Mesh> meshes;

	bool loadModel(std::string path, std::shared_ptr<IShader> custom_shader);
	bool processNode(aiNode* node, const aiScene* scene, std::shared_ptr<GameObject> parent, std::shared_ptr<IShader> custom_shader);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene, std::shared_ptr<IShader> custom_shader);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

public:
	Model(std::string path, std::shared_ptr<IShader> custom_shader = nullptr);

	void start() override;
};

