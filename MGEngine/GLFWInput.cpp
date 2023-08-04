#include "GLFWInput.h"

int Input::curMappingId = 0;
std::map<int, InputMapping> Input::idMappings;
std::map<std::string, int> Input::nameToIdMappings;