#pragma once

#include "ITexture.hpp"
#include "IShader.hpp"
#include "MacroUtils.hpp"
#include "Color.hpp"
#include <vector>
#include "MaterialProperty.hpp"

class Material {
	std::vector<std::shared_ptr<MaterialProperty>> properties;
	std::shared_ptr<IShader> shader;
public:
	bool remove_property(const std::string& name) {
		for (auto it = properties.begin(); it != properties.end(); ++it) {
			if ((*it)->get_name() == name) {
				properties.erase(it);
				return true;
			}
		}

		return false;
	}

	bool has_property(const std::string& name) {
		for (auto& prop : properties) {
			if (prop->get_name() == name) {
				return true;
			}
		}

		return false;
	}

	/// <summary>
	/// Returns a property with the given name. If it does not exist, it will be created.
	/// </summary>
	/// <param name="name">Name of the property.</param>
	/// <returns>Weak ptr to the referenced property.</returns>
	std::weak_ptr<MaterialProperty> get_property(const std::string& name) {
		for (auto& prop : properties) {
			if (prop->get_name() == name) {
				return prop;
			}
		}

		auto prop = std::make_shared<MaterialProperty>(shader.get(), name);
		properties.push_back(prop);
		return prop;
	}

	void send_to_shader();

	std::shared_ptr<IShader> get_shader() const { return shader; }
	void set_shader(std::shared_ptr<IShader> value) { 
		shader = value; 
		for(auto& prop : properties) {
			prop->update_shader_location(value.get());
		}
	}

	Material(std::shared_ptr<IShader> shader) {
		set_shader(shader);
	}
};