#pragma once

#ifdef RENDER_BACKEND_OGL_SUPPORT
#include "GLInclude.hpp"

#include "RObj.hpp"
#include "Config.hpp"

void delFbo(GLuint& x);
void delTexture(GLuint& x);
void delRbo(GLuint& x);
void delShaderProgram(GLuint& x);
void delVao(GLuint& x);
void delVbo(GLuint& x);
void delEbo(GLuint& x);

using GL_FBO = RObj<GLuint, delFbo>;
using GL_Texture = RObj<GLuint, delTexture>;
using GL_RBO = RObj<GLuint, delRbo>;
using GL_ShaderProgram = RObj<GLuint, delShaderProgram>;
using GL_VAO = RObj<GLuint, delVao>;
using GL_VBO = RObj<GLuint, delVbo>;
using GL_EBO = RObj<GLuint, delEbo>;

#endif // RENDER_BACKEND_OGL_SUPPORT