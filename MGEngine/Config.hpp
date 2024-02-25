#pragma once

#define MG_RENDERER GL
#define USE_GL (MG_RENDERER == GL)

#if USE_GL
#include <glad/glad.h>
#include "Renderer/GL/GL_RAII.hpp"

#if NDEBUG
#define USE_GL_DEBUG 0
#else
#define USE_GL_DEBUG 1
#endif

#else
#error No renderer type specified!
#endif

#if NDEBUG
#define SECURITY_CHECKS 1
#else
#define SECURITY_CHECKS 3
#endif

#define SC_NONE SECURITY_CHECKS == 0
#define SC_FATAL_ON SECURITY_CHECKS >= 1
#define SC_ERROR_ON SECURITY_CHECKS >= 2
#define SC_WARNING_ON SECURITY_CHECKS >= 3