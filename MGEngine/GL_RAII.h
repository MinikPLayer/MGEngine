#pragma once
#include "RAII.h"
#include "Config.h"

DEF_MOO_TYPE(GL_VAO, GLuint, glDeleteVertexArrays(1, &x));
DEF_MOO_TYPE(GL_VBO, GLuint, glDeleteBuffers(1, &x));
DEF_MOO_TYPE(GL_EBO, GLuint, glDeleteBuffers(1, &x));
DEF_MOO_TYPE(GL_Shader, GLuint, glDeleteProgram(x));