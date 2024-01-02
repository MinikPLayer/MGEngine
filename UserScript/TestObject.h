#pragma once
#include <GameObject.h>
#include <Mesh.h>
#include <Model.h>
#include "ITexture.h"

class TestObject : public GameObject {
	std::shared_ptr<ITexture> testTexture;

	int exitMapping = -1;
	int smallWindowMapping = -1;
	int mediumWindowMapping = -1;
	int largeWindowMapping = -1;
	int veryLargeWindowMapping = -1;

public:
	void start() override;
	void update() override;
};

