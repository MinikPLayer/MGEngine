#include "Config.h"

#include "GLShader.h"
#include "File.h"

bool checkShaderCompilationSuccess(GLuint shader, std::string typeName) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		ELOG_FATAL(typeName, " shader compilation error - ", infoLog);
		return false;
	}
	return true;
}

bool checkShaderLinkSuccess(GLuint shader) {
	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		ELOG_FATAL("Shader program link error - ", infoLog);
		return false;
	}
	return true;
}

bool GLShader::_init_(std::string vSource, std::string fSource) {
	auto vShader = glCreateShader(GL_VERTEX_SHADER);
	auto vSourcePtr = vSource.c_str();
	glShaderSource(vShader, 1, &vSourcePtr, NULL);
	glCompileShader(vShader);
	if (!checkShaderCompilationSuccess(vShader, "VERTEX"))
		return false;

	auto fShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto fSourcePtr = fSource.c_str();
	glShaderSource(fShader, 1, &fSourcePtr, NULL);
	glCompileShader(fShader);
	if (!checkShaderCompilationSuccess(fShader, "FRAGMENT")) {
		glDeleteShader(vShader);
		return false;
	}
	auto shader = glCreateProgram();
	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);
	glLinkProgram(shader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (!checkShaderLinkSuccess(shader))
		return false;

	shaderObject = GL_Shader(shader);
	return true;
}

void GLShader::set_uniform_3f(unsigned int location, float v0, float v1, float v2) {
	glUniform3f(location, v0, v1, v2);
}

void GLShader::set_uniform_3f(unsigned int location, Vector3<float> v) {
	set_uniform_3f(location, v.x, v.y, v.z);
}

void GLShader::set_uniform_4f(unsigned int location, float v0, float v1, float v2, float v3) {
	glUniform4f(location, v0, v1, v2, v3);
}

void GLShader::set_uniform_mat4f(unsigned int location, glm::mat4 mat) {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}


void GLShader::use() {
#if SC_ERROR_ON
	if (!good) {
		ELOG_ERROR("Trying to use a shader, that is not correctly loaded / compiled");
	}
#endif
	glUseProgram(shaderObject.value().get());
}
unsigned int GLShader::get_uniform_location(std::string name) {
	return glGetUniformLocation(this->shaderObject.value().get(), name.c_str());
}