#pragma once

#include <memory>
#include "Engine.hpp"
#include "InputMapping.hpp"

class Input {
	static std::unique_ptr<IInputBackend> backend;

	static Vector2f lastMousePos;

	static void init(std::unique_ptr<IInputBackend> backend);
	static void update();

	friend class Engine;
	friend class IRenderer;

	static int curMappingId;
	static std::map<int, InputMapping> idMappings;
	static std::map<std::string, int> nameToIdMappings;

	static Vector2f lastScrollValue;

public:
	static void set_cursor_mode(CursorModes mode);
	static bool is_key_pressed(KeyboardKeys key);

	static int register_mapping(InputMapping mapping);
	static void update_mapping(InputMapping mapping);
	static std::optional<InputMapping> get_value(int id);
	static std::optional<InputMapping> get_value(std::string name);
	static std::optional<int> get_mapping_id(std::string name);
	static bool remove_mapping(int id);
};