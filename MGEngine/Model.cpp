#include "Model.hpp"
#include <assimp/postprocess.h>

Model::Model(std::string path, std::shared_ptr<Material> customMaterial) {
	this->path = path;
	this->customMaterial = customMaterial;

	this->get_transform().set_local_scale(Vector3<float>(0.01f, 0.01f, 0.01f));
}

void Model::start() {
	if (!loadModel(path, this->customMaterial))
		throw std::runtime_error("Unable to load model: " + path);
}

bool Model::loadMaterials(const aiScene* scene) {
	ELOG_TRACE("Loading materials for model: ", path);

	materials.reserve(scene->mNumMaterials);
	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		// TODO: Add materials
		auto newMat = Material::createDefault();
		
		auto mat = scene->mMaterials[i];
		
		aiColor3D diffuse;
		if (AI_SUCCESS != mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse)) {
			ELOG_WARNING("Failed to load diffuse color for material ", i);
		}

		ELOG_TRACE("Material ", i, " diffuse color: ", diffuse.r, " ", diffuse.g, " ", diffuse.b);
	}

	return true;
}

bool Model::loadModel(std::string path, std::shared_ptr<Material> customMaterial) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		ELOG_ERROR("Assimp error: ", importer.GetErrorString());
		return false;
	}

	if (!loadMaterials(scene)) {
		ELOG_ERROR("Failed to load materials");
		return false;
	}

	return processNode(scene->mRootNode, scene, this->get_self_ptr().lock(), customMaterial);
}

bool Model::processNode(aiNode* node, const aiScene* scene, std::shared_ptr<GameObject> parent, std::shared_ptr<Material> customMaterial) {
	auto newParent = parent;
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		auto transformation = node->mTransformation;
		auto meshObject = processMesh(mesh, scene, customMaterial);
		parent->add_component(meshObject);
		meshObject->get_transform().update_matrix(glm::transpose(glm::make_mat4(&transformation.a1)));

		//aiVector3D position, scaling, rotation;
		//node->mTransformation.Decompose(scaling, rotation, position);
		newParent = meshObject;
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		if (!processNode(node->mChildren[i], scene, newParent, customMaterial))
			return false;
	}

	return true;
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene, std::shared_ptr<Material> customMaterial) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	// TODO: textures

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex v;
		v.position = Vector3<float>(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if(mesh->HasNormals())
			v.normal = Vector3<float>(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if(mesh->HasTextureCoords(0))
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

	auto newMesh = std::make_shared<Mesh>(vertices, indices);
	newMesh->set_material(customMaterial);
	return newMesh;
}
