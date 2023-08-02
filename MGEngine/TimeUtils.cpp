#include "TimeUtils.h"

std::optional<std::chrono::high_resolution_clock::time_point> Time::_lastTime = std::nullopt;
std::chrono::high_resolution_clock::time_point Time::_startTime = std::chrono::high_resolution_clock::now();
float Time::_dt = 0;