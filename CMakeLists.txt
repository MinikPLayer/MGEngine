# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 4.0)
 
# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

IF (UNIX)
    set(CMAKE_LINKER_TYPE "MOLD")
endif (UNIX)

# set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
#set(CMAKE_CXX_FLAGS "-###")

# set(CMAKE_C_USING_LINKER_LLD "-fuse-ld=lld")
# set(CMAKE_CXX_USING_LINKER_LLD "-fuse-ld=lld")

project ("MGEngine")

set(PROJECT_EXTERNAL_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/llvm") 
set(PROJECT_INCLUDE_DIR "${PROJECT_EXTERNAL_LIB_DIR}/include")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_EXTERNAL_LIB_DIR}")

# Include sub-projects.
add_subdirectory("MGEngine")
add_subdirectory("UserScript")

add_subdirectory("tests")