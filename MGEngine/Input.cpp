#include "Input.hpp"
#include "InputMapping.hpp"

void Input::init(std::unique_ptr<IInputBackend> backend) {
	Input::backend = std::move(backend);
	lastMousePos = Input::backend->get_cursor_position();
}

void Input::update() {
	auto newScrollValue = backend->get_scroll_value();
	auto scrollDelta = newScrollValue - lastScrollValue;
	lastScrollValue = newScrollValue;

	auto newMousePos = backend->get_cursor_position();
	auto mousePosDelta = newMousePos - lastMousePos;
	lastMousePos = newMousePos;

	for (auto it = idMappings.begin(); it != idMappings.end(); it++) {
		it->second.update(backend.get(), mousePosDelta, scrollDelta);
	}
}

void Input::set_cursor_mode(CursorModes mode) {
	backend->set_cursor_mode(mode);
}

bool Input::is_key_pressed(KeyboardKeys key) {
	return backend->is_key_pressed(key);
}

int Input::register_mapping(InputMapping mapping) {
#if SC_WARNING_ON
	if (nameToIdMappings.contains(mapping.get_name())) {
		ELOG_WARNING("Mapping already exists: \"", mapping.get_name(), "\"");
	}
#endif	

	int id = curMappingId++;
	idMappings.insert({ id, mapping });
	nameToIdMappings.insert({ mapping.get_name(), id });

	return id;
}

void Input::update_mapping(InputMapping mapping) {
	auto id = get_mapping_id(mapping.get_name());
	if (!id.has_value()) {
		ELOG_ERROR("Trying to update mapping that doesn't exist (\"" + mapping.get_name() + "\"");
		return;
	}

	idMappings.at(id.value()) = mapping;
}

std::optional<InputMapping> Input::get_value(int id) {
	try {
		auto mapping = idMappings.at(id);
		return mapping;
	}
	catch (std::out_of_range) {
		ELOG_ERROR("Input id not found: ", id);
		return std::nullopt;
	};
}

std::optional<int> Input::get_mapping_id(std::string name) {
	int id = 0;
	try {
		id = nameToIdMappings.at(name);
	}
	catch (std::out_of_range) {
		ELOG_ERROR("Input name not found: \"", name, "\"");
		return std::nullopt;
	};

	return std::nullopt;
}

std::optional<InputMapping> Input::get_value(std::string name) {
	auto id = get_mapping_id(name);
	if (!id.has_value())
		return std::nullopt;

	return get_value(id.value());
}

bool Input::remove_mapping(int id) {
	auto mapping = get_value(id);
	if (!mapping.has_value())
		return false;

	idMappings.erase(id);
	nameToIdMappings.erase(mapping.value().get_name());
	return true;
}

Vector2f Input::lastMousePos = Vector2f::zero();
int Input::curMappingId;
std::map<int, InputMapping> Input::idMappings;
std::map<std::string, int> Input::nameToIdMappings;
Vector2f Input::lastScrollValue;
std::unique_ptr<IInputBackend> Input::backend;