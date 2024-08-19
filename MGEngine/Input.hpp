#pragma once

#include "Config.hpp"
#if INPUT_BACKEND_GLFW_SUPPORT
#include "GLFWInput.hpp"
#else
#error "No input system defined for this platform"
#endif