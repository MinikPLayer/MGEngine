#pragma once

#include "ITexture.hpp"
#include "IShader.hpp"
#include "MacroUtils.hpp"
#include "Color.hpp"
#include <vector>
#include "MaterialProperty.hpp"

class Material {
	std::vector<MaterialProperty> properties;
	std::shared_ptr<IShader> shader;
public:
	void send_to_shader();

	std::shared_ptr<IShader> get_shader() const { return shader; }
	void set_shader(std::shared_ptr<IShader> value) { 
		shader = value; 
		for(auto& prop : properties) {
			prop.update_shader_location(value.get());
		}
	}

	Material(std::shared_ptr<IShader> shader) {
		set_shader(shader);
	}
};