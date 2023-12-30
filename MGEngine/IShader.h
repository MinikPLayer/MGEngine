#pragma once

#include <string>
#include "Vector3.h"

class IShader {
protected:
	virtual bool _init_(std::string vertexSource, std::string fragmentSource) = 0;

	bool good = false;
public:
	bool load(std::string vertexPath, std::string fragmentPath);

	virtual void use() = 0;

	virtual unsigned int get_uniform_location(std::string name) = 0;
	virtual void set_uniform_3f(unsigned int location, float v0, float v1, float v2) = 0;
	virtual void set_uniform_3f(unsigned int location, Vector3<float> v) = 0;
	virtual void set_uniform_4f(unsigned int location, float v0, float v1, float v2, float v3) = 0;
	virtual void set_uniform_mat4f(unsigned int location, glm::mat4 mat) = 0;
};