#include "GL_RAII.hpp"

void delFbo(GLuint& x) {
	glDeleteFramebuffers(1, &x);
}

void delTexture(GLuint& x) {
	glDeleteTextures(1, &x);
}

void delRbo(GLuint& x) {
	glDeleteRenderbuffers(1, &x);
}

void delShaderProgram(GLuint& x) {
	glDeleteProgram(x);
}

void delVao(GLuint& x) {
	glDeleteVertexArrays(1, &x);
}

void delVbo(GLuint& x) {
	glDeleteBuffers(1, &x);
}

void delEbo(GLuint& x) {
	glDeleteBuffers(1, &x);
}
