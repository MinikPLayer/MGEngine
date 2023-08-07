#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class Model : public GameObject {
public:
	Model(std::string path);

private:
	// model data
	std::vector<Mesh> meshes;

	bool loadModel(std::string path);
	bool processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

