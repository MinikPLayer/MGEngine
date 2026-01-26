# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.30)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

project ("MGEngine")

set(PROJECT_EXTERNAL_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/llvm")
set(PROJECT_INCLUDE_DIR "${PROJECT_EXTERNAL_LIB_DIR}/include")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_EXTERNAL_LIB_DIR}")

# Include sub-projects.
add_subdirectory ("MGEngine")

add_subdirectory("UserScript")