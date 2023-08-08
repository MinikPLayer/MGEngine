#pragma once

#include "Config.h"
#if USE_GL
#include "GLFWInput.h"
#else
#error "No input system defined for this platform"
#endif