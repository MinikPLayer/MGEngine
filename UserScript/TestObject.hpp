#pragma once
#include <GameObject.hpp>
#include <Mesh.hpp>
#include <Model.hpp>
#include "ITexture.hpp"

class TestObject : public GameObject {
	std::shared_ptr<ITexture> testTexture;

	std::shared_ptr<Material> testMaterial;

	int exitMapping = -1;
	int smallWindowMapping = -1;
	int mediumWindowMapping = -1;
	int largeWindowMapping = -1;
	int veryLargeWindowMapping = -1;

	void loadTestObject();

public:
	void start() override;
	void update() override;
};

