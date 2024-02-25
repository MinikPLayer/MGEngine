#pragma once
#include "..\..\Config.hpp"
#include "..\IShader.hpp"

#include "GL_RAII.hpp"
#include <string>
#include "..\..\Vector3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLShader : public IShader {
	std::optional<GL_Shader> shaderObject;

	// static GL_Shader load_GL(std::string vertexPath, std::string fragmentPath);
	bool _init_(std::string vertexSource, std::string fragmentSource) override;

	inline void debugCheckShaderIsLoaded();
public:
	unsigned int modelUniformLocation = 0;
	unsigned int vpUniformLocation = 1;
	unsigned int modelInversedUniformLocation = 2;

	void bind() override;

	unsigned int get_uniform_location(std::string name) override;

	void set_uniform_1f(unsigned int location, float v) override;
	void set_uniform_1i(unsigned int location, int v) override;
	void set_uniform_1ui(unsigned int location, unsigned int v) override;

	void set_uniform_3f(unsigned int location, float v0, float v1, float v2) override;
	void set_uniform_3f(unsigned int location, Vector3<float> v) override;

	void set_uniform_4f(unsigned int location, float v0, float v1, float v2, float v3) override;
	void set_uniform_mat4f(unsigned int location, glm::mat4 mat) override;
};