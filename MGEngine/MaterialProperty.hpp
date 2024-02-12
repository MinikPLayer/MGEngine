#pragma once

#include <string>
#include "IShader.hpp"
#include "Log.hpp"
#include <functional>
#include "Config.hpp"
#include <vector>

class MaterialProperty;
class MaterialPropertyFunctions {
public:
	static void SendToShaderInt(MaterialProperty* prop, IShader* shader);
	static void SendToShaderUint(MaterialProperty* prop, IShader* shader);

	static void SendToShaderFloat(MaterialProperty* prop, IShader* shader);
	static void SendToShaderFloat3(MaterialProperty* prop, IShader* shader);
};

class MaterialProperty {
	friend class MaterialPropertyFunctions;

	// Value
	unsigned int value_int = 0;
	std::vector<float> value_floats;

	bool dirty = false;

	int location = -1;
	std::string name;

	std::function<void(MaterialProperty*, IShader*)> sendToShaderFunc = nullptr;

public:
	std::string get_name() {
		return name;
	}

	int get_location() {
		return location;
	}

	void update_shader_location(IShader* shader) {
		location = shader->get_uniform_location(name);
	}

	void set_int(int value) {
		value_int = value;
		sendToShaderFunc = MaterialPropertyFunctions::SendToShaderInt;
		dirty = true;
	}

	void set_uint(unsigned int value) {
		value_int = value;
		sendToShaderFunc = MaterialPropertyFunctions::SendToShaderUint;
		dirty = true;
	}

	void set_float(float value) {
		value_floats = { value };
		sendToShaderFunc = MaterialPropertyFunctions::SendToShaderFloat;
		dirty = true;
	}

	void set_vec3(Vector3<float> value) {
		value_floats = { value.x, value.y, value.z };
		sendToShaderFunc = MaterialPropertyFunctions::SendToShaderFloat3;
		dirty = true;
	}

	void send_to_shader(IShader* shader) {
#if SC_ERROR_ON
		if(sendToShaderFunc == nullptr) {
			ELOG_ERROR("sendToShaderFunc is not set. This should not happen.");
			return;
		}
#endif	

		if (location == -1) {
			ELOG_WARNING("Material property is defined, but it's shader location is not set. It probably doesn't exist in current shader.");
			return;
		}

		if(dirty)
			sendToShaderFunc(this, shader);
	}

	MaterialProperty(IShader* shader, std::string name) {
		this->name = name;
		update_shader_location(shader);
	}
};