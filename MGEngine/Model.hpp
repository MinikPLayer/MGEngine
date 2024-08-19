#pragma once
#include "GameObject.hpp"
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class Model : public GameObject {
private:
	std::vector<std::shared_ptr<Material>> materials;

	std::shared_ptr<Material> customMaterial = nullptr;

	std::string path;
	// model data
	std::vector<Mesh> meshes;

	bool loadMaterials(const aiScene* scene);

	bool loadModel(std::string path, std::shared_ptr<Material> customMaterial);
	bool processNode(aiNode* node, const aiScene* scene, std::shared_ptr<GameObject> parent, std::shared_ptr<Material> customMaterial);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene, std::shared_ptr<Material> customMaterial);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

public:
	Model(std::string path, std::shared_ptr<Material> customMaterial = nullptr);

	void start() override;
};

