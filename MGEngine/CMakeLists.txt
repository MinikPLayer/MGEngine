# CMakeList.txt : CMake project for MGEngine, include source and define
# project specific logic here.
#


# Add source to this project's executable.
add_library (MGEngineLib 
	"Camera.cpp"
	"Camera.hpp"
	"Color.cpp"
	"Color.hpp"
	"Compression.cpp"
	"Compression.hpp"
	"Config.hpp"
	"Dirty.hpp"
	"Engine.cpp"
	"Engine.hpp"
	"ErrorCodes.hpp"
	"Event.hpp"
	"File.hpp"
	"FloatUtils.hpp"
	"GameObject.cpp"
	"GameObject.hpp"
	"Renderer/GL/GLFramebuffer.cpp"
	"Renderer/GL/GLFramebuffer.hpp"
	"GLFWInput.cpp"
	"GLFWInput.hpp"
	"Renderer/GL/GLRenderer.cpp"
	"Renderer/GL/GLRenderer.hpp"
	"Renderer/GL/GLShader.cpp"
	"Renderer/GL/GLShader.hpp"
	"Renderer/GL/GLTexture.cpp"
	"Renderer/GL/GLTexture.hpp"
	"Renderer/GL/GL_DebugLayers.hpp"
	"Renderer/GL/GL_RAII.cpp"
	"Renderer/GL/GL_RAII.hpp"
	"Renderer/IFramebuffer.hpp"
	"Input.hpp"
	"Renderer/IRenderer.hpp"
	"Renderer/IShader.cpp"
	"Renderer/IShader.hpp"
	"Renderer/ITexture.cpp"
	"Renderer/ITexture.hpp"
	"Log.hpp"
	"MacroUtils.hpp"
	"Material.cpp"
	"Material.hpp"
	"MaterialProperty.cpp"
	"MaterialProperty.hpp"
	"MatrixUtils.cpp"
	"MatrixUtils.hpp"
	"Mesh.cpp"
	"Mesh.hpp"
	"Model.cpp"
	"Model.hpp"
	"Quaternion.cpp"
	"Quaternion.hpp"
	"RObj.hpp"
	"StringUtils.hpp"
	"TimeUtils.cpp"
	"TimeUtils.hpp"
	"Transform.cpp"
	"Transform.hpp"
	"Vector2.hpp"
	"Vector3.hpp"  "File.cpp")

set_property(TARGET MGEngineLib PROPERTY CXX_STANDARD 20)

find_package(glm CONFIG REQUIRED)
target_link_libraries(MGEngineLib PRIVATE glm::glm)

find_package(Stb REQUIRED)
target_include_directories(MGEngineLib PRIVATE ${Stb_INCLUDE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(MGEngineLib PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(MGEngineLib PRIVATE glfw)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(MGEngineLib PRIVATE assimp::assimp)

find_package(ZLIB REQUIRED)
target_link_libraries(MGEngineLib PRIVATE ZLIB::ZLIB)

add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

# TODO: Add tests and install targets if needed.
