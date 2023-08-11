#pragma once
#include <GameObject.h>
#include <Mesh.h>
#include <Model.h>

class TestObject : public GameObject {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Model> model;

	int exitMapping = -1;

public:
	void start() override;
	void update() override;
};

