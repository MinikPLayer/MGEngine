#include "Config.h"

#if USE_GL
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

GL_Shader Shader::load_GL(std::string vertexPath, std::string fragmentPath) {
	auto vSource = File::loadAllText(vertexPath);
	auto vShader = glCreateShader(GL_VERTEX_SHADER);
	auto vSourcePtr = vSource.c_str();
	glShaderSource(vShader, 1, &vSourcePtr, NULL);
	glCompileShader(vShader);
	if (!checkShaderCompilationSuccess(vShader, "VERTEX"))
		return {};

	auto fSource = File::loadAllText(fragmentPath);
	auto fShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto fSourcePtr = fSource.c_str();
	glShaderSource(fShader, 1, &fSourcePtr, NULL);
	glCompileShader(fShader);
	if (!checkShaderCompilationSuccess(fShader, "FRAGMENT")) {
		glDeleteShader(vShader);
		return {};
	}
	auto shader = glCreateProgram();
	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);
	glLinkProgram(shader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (!checkShaderLinkSuccess(shader))
		return {};

	return GL_Shader(shader);
}

void Shader::setUniform3f(unsigned int location, float v0, float v1, float v2) {
	glUniform3f(location, v0, v1, v2);
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	load(vertexPath, fragmentPath);
}

bool Shader::load(std::string vertexPath, std::string fragmentPath) {
#if SC_WARNING_ON
	if (good) {
		ELOG_WARNING("Trying to load a shader twice");
	}
#endif

	this->shader = load_GL(vertexPath, fragmentPath);
	good = this->shader.has_value();
	return good;
}

void Shader::use() {
#if SC_ERROR_ON
	if (!good) {
		ELOG_ERROR("Trying to use a shader, that is not correctly loaded / compiled");
	}
#endif
	glUseProgram(shader.get());
}
unsigned int Shader::getUniformLocation(std::string name) {
	return glGetUniformLocation(this->shader.get(), name.c_str());
}
#endif