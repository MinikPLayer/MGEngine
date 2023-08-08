#include "Model.h"
#include <assimp/postprocess.h>

Model::Model(std::string path) {
	this->path = path;
}

void Model::start() {
	if (!loadModel(path))
		throw std::runtime_error("Unable to load model: " + path);
}

bool Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		ELOG_ERROR("Assimp error: ", importer.GetErrorString());
		return false;
	}

	return processNode(scene->mRootNode, scene);
}

bool Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		add_component(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		if (!processNode(node->mChildren[i], scene))
			return false;
	}

	return true;
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	// TODO: textures

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex v;
		v.position = Vector3<float>(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		v.normal = Vector3<float>(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		v.uv = Vector2<float>(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// TODO: textures

	return std::make_shared<Mesh>(vertices, indices);
}
