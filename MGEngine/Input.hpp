#pragma once

#include "Config.hpp"
#if USE_GL
#include "GLFWInput.hpp"
#else
#error "No input system defined for this platform"
#endif