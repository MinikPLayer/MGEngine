#include "Material.hpp"

std::shared_ptr<Material> Material::create(std::shared_ptr<IShader> shader) {
	auto newMaterial = new Material(shader);
	return std::shared_ptr<Material>(newMaterial);
}

std::shared_ptr<Material> Material::createDefault() {
	// TODO: Add properties
	std::shared_ptr<IShader> shader = IShader::create_default();
	return create(shader);
}

bool Material::remove_property(const std::string& name) {
	for (auto it = properties.begin(); it != properties.end(); ++it) {
		if ((*it)->get_name() == name) {
			properties.erase(it);
			return true;
		}
	}

	return false;
}

bool Material::has_property(const std::string& name) {
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
std::weak_ptr<MaterialProperty> Material::get_property(const std::string& name) {
	for (auto& prop : properties) {
		if (prop->get_name() == name) {
			return prop;
		}
	}

	auto prop = std::make_shared<MaterialProperty>(shader.get(), name);
	properties.push_back(prop);
	return prop;
}

void Material::send_to_shader() {
	 for(auto& prop : this->properties) {
		 prop->send_to_shader(this->shader.get());
	 }
 }

void Material::set_shader(std::shared_ptr<IShader> value) {
	shader = value;
	for (auto& prop : properties) {
		prop->update_shader_location(value.get());
	}
}

Material::Material(std::shared_ptr<IShader> shader) {
	set_shader(shader);
}
