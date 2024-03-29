add_executable(UserScript "main.cpp" "TestObject.hpp" "TestObject.cpp")

target_include_directories(UserScript PUBLIC "../MGEngine")
target_link_libraries(UserScript MGEngineLib)

# find_package(glad CONFIG REQUIRED)
# target_link_libraries(UserScript glad::glad)

set_property(TARGET UserScript PROPERTY CXX_STANDARD 20)
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

if(WIN32)
    set(CREATE_ASSETS_SCRIPT "${CMAKE_SOURCE_DIR}/utils/create_assets_link.bat")
elseif(LINUX)
    set(CREATE_ASSETS_SCRIPT "${CMAKE_SOURCE_DIR}/utils/create_assets_link.sh")
else()
    message("Unsupported platform")
endif()


message("Binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET UserScript POST_BUILD
 	COMMAND ${CREATE_ASSETS_SCRIPT} ${CMAKE_SOURCE_DIR}/MGEngine/assets ${CMAKE_CURRENT_BINARY_DIR}/assets/engine
    COMMENT "Running engine assets link script"
)

add_custom_command(TARGET UserScript POST_BUILD
 	COMMAND ${CREATE_ASSETS_SCRIPT} ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets/user
    COMMENT "Running user assets link script"
)
