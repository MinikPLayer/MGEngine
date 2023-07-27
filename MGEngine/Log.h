#pragma once

#include <iostream>
#include <string>
#include <vector>

#define RESET_COLOR 	"\x1B[0m"
#define INFO_COLOR 	"\x1B[1;34m"
#define DEBUG_COLOR 	"\x1B[1;30m"
#define WARNING_COLOR 	"\x1B[1;33m"
#define ERROR_COLOR 	"\x1B[31m"

#define ELOG(...)         log("[LOG]",  RESET_COLOR, __VA_ARGS__)
#define ELOG_TEST(...)    log("[TEST]", WARNING_COLOR, __VA_ARGS__)
#define ELOG_INFO(...)    log("[INFO]", INFO_COLOR, __VA_ARGS__)
#define ELOG_DEBUG(...)   log("[DEBUG]", DEBUG_COLOR, __VA_ARGS__)
#define ELOG_WARNING(...) log("[WARNING]", WARNING_COLOR, __VA_ARGS__)
#define ELOG_ERROR(...)   log("[ERROR]", ERROR_COLOR, __VA_ARGS__); __debugbreak()
#define ELOG_FATAL(...)   log("[FATAL ERROR]", ERROR_COLOR, __VA_ARGS__); __debugbreak()

template<typename ... Args>
void log(const char* type, const char* color, Args ... args)
{
    std::cout << color << type << " ";
    (..., (std::cout << args));
    std::cout << RESET_COLOR << std::endl;
}