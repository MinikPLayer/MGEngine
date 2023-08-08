#pragma once
#include "Config.h"

#if USE_GL
#include "GL_RAII.h"
#include <string>
#include "Vector3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
	GL_Shader shader;

	bool good = false;
	static GL_Shader load_GL(std::string vertexPath, std::string fragmentPath);
public:
	unsigned int modelUniformLocation = 0;
	unsigned int vpUniformLocation = 1;
	unsigned int modelInversedUniformLocation = 2;

	bool load(std::string vertexPath, std::string fragmentPath);
	void use();

	unsigned int get_uniform_location(std::string name);

	void set_uniform_3f(unsigned int location, float v0, float v1, float v2);
	void set_uniform_3f(unsigned int location, Vector3<float> v);

	void set_uniform_4f(unsigned int location, float v0, float v1, float v2, float v3);
	void set_uniform_mat4f(unsigned int location, glm::mat4 mat);

	Shader(std::string vertexPath, std::string fragmentPath);
	Shader() {}
};
#endif