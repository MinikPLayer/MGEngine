#pragma once
#include <GameObject.h>
#include <Mesh.h>
#include <Model.h>

class TestObject : public GameObject {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Model> model;

	int exitMapping = -1;
	int smallWindowMapping = -1;
	int mediumWindowMapping = -1;
	int largeWindowMapping = -1;
	int veryLargeWindowMapping = -1;

public:
	void start() override;
	void update() override;
};

