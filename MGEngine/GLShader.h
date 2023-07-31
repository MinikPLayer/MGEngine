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

	bool load(std::string vertexPath, std::string fragmentPath);
	void use();

	unsigned int getUniformLocation(std::string name);

	void setUniform3f(unsigned int location, float v0, float v1, float v2);
	void setUniform3f(unsigned int location, Vector3<float> v) {
		setUniform3f(location, v.x, v.y, v.z);
	}
	void setUniform4f(unsigned int location, float v0, float v1, float v2, float v3) {
		glUniform4f(location, v0, v1, v2, v3);
	}
	void setUniformMat4f(unsigned int location, glm::mat4 mat) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	Shader(std::string vertexPath, std::string fragmentPath);
	Shader() {}
};
#endif