#pragma once
#include <GameObject.h>
#include <Mesh.h>

class TestObject : public GameObject {
	std::shared_ptr<Mesh> mesh;

	int exitMapping = -1;

public:
	void start() override;
	void update() override;
};

