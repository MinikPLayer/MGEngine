#pragma once

#include <string>
#include "..\Vector3.hpp"

class IShader {
protected:
	virtual bool _init_(std::string vertexSource, std::string fragmentSource) = 0;

	bool good = false;
public:
	/// <summary>
	/// Shader will use model matrices for rendering. 
	/// If disabled, objects will be drawn without any transformations.
	/// </summary>
	bool usingModelMatrices = true;

	bool load(std::string vertexPath, std::string fragmentPath);

	virtual void bind() = 0;

	virtual unsigned int get_uniform_location(std::string name) = 0;

	virtual void set_uniform_1f(unsigned int location, float v) = 0;
	virtual void set_uniform_1i(unsigned int location, int v) = 0;
	virtual void set_uniform_1ui(unsigned int location, unsigned int v) = 0;
	virtual void set_uniform_3f(unsigned int location, float v0, float v1, float v2) = 0;
	virtual void set_uniform_3f(unsigned int location, Vector3<float> v) = 0;
	virtual void set_uniform_4f(unsigned int location, float v0, float v1, float v2, float v3) = 0;
	virtual void set_uniform_mat4f(unsigned int location, glm::mat4 mat) = 0;
};