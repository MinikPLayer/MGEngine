#pragma once

#define MG_RENDERER GL
#define USE_GL (MG_RENDERER == GL)

#if USE_GL
#include <glad/glad.h>
#include "GL_RAII.h"
#endif