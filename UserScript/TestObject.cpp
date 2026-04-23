#include "TestObject.hpp"
#include <Engine.hpp>
#include <TimeUtils.hpp>
#include <Renderer/GL/GLTexture.hpp>

#include "File.hpp"

std::string vSource;
std::string fSource;

void TestObject::start() {
	auto renderer = Engine::get_renderer();
	auto size = renderer.lock()->get_main_screen_resolution();
	renderer.lock()->set_resolution(size / 2);
	renderer.lock()->set_vertical_sync(true);

	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngines!");
	Input::SetCursorMode(CursorModes::Disabled);

	auto textureShader = std::make_shared<GLShader>();
	textureShader->load("engine://shaders/mainShader.vert", "engine://shaders/mainShader_texture.frag");
	textureShader->bind();
	// textureShader->set_uniform_1i(3, 1);

	testTexture = std::make_shared<GLTexture>();
	testTexture->loadFromFile("user://Backpack/1001_albedo.jpg");
	testTexture->bind(0);
	textureShader->set_uniform_1i(3, 0);

	testMaterial = std::make_shared<Material>(textureShader);
	auto cubes = std::make_shared<Model>("user://Backpack/Survival_BackPack_2.fbx", testMaterial);
	add_component(cubes);	

	cubes->lateStartEvent += [](GameObject* obj) {
		LOG_INFO("Late start event called for ", obj->get_type_name());
		obj->get_transform().set_local_scale(Vector3(1.0f, 1.0f, 1.0f) * 0.01f);
	};

	vSource = File::LoadAllText("engine://shaders/mainShader.vert");
	fSource = File::LoadAllText("engine://shaders/mainShader.frag");
}

bool _checkShaderCompilationSuccess(GLuint shader, std::string typeName) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		ELOG_FATAL(typeName, " shader compilation error - ", infoLog);
		return false;
	}
	return true;
}

bool _checkShaderLinkSuccess(GLuint shader) {
	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		ELOG_FATAL("Shader program link error - ", infoLog);
		return false;
	}
	return true;
}

void allocateTestProgram() {
	auto vShader = glCreateShader(GL_VERTEX_SHADER);
	auto vSourcePtr = vSource.c_str();
	glShaderSource(vShader, 1, &vSourcePtr, NULL);
	glCompileShader(vShader);
	if (!_checkShaderCompilationSuccess(vShader, "VERTEX")) {
		LOG_ERROR("Vertex shader compilation failed!");
		return;
	}

	const auto fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const auto fSourcePtr = fSource.c_str();
	glShaderSource(fShader, 1, &fSourcePtr, NULL);
	glCompileShader(fShader);
	if (!_checkShaderCompilationSuccess(fShader, "FRAGMENT")) {
		glDeleteShader(vShader);
		LOG_ERROR("Fragment shader compilation failed.");
		return;
	}
	const auto shader = glCreateProgram();
	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);
	glLinkProgram(shader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (!_checkShaderLinkSuccess(shader)) {
		LOG_ERROR("Shader linkage failed.");
		return;
	}

	glDeleteProgram(shader);
}

void TestObject::update() {
	allocateTestProgram();

	auto prop = testMaterial->get_property("brightness");
	prop.lock()->set_float(sin(Time::ElapsedTime()) * 0.5f + 0.5f);

	testTexture->bind(0);

    if(Input::key_is_pressed(Keyboard::KEY_M)) {
        auto mapping = Input::findMapping("CameraSideways");
		if(!mapping.has_value()) {
			LOG_WARNING("Input mapping CameraSideways not found!");
			return;
		}

		const auto value = Input::get(mapping.value())->get_value();
		LOG_INFO("Value: ", value);
    }

	if (Input::key_is_pressed(Keyboard::KEY_H)) {
		GameObject::PrintObjectsHierarchy();  
	}
	

	if (Input::key_is_pressed(Keyboard::KEY_V)) {
		Engine::get_renderer().lock()->set_vertical_sync(true);
	}

	if (Input::key_is_pressed(Keyboard::KEY_B)) {
		Engine::get_renderer().lock()->set_vertical_sync(false);
	}

	if (Input::key_is_pressed(Keyboard::ESCAPE)) {
		Engine::stop();
	}
}
