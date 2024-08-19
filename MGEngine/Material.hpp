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
	static std::shared_ptr<Material> create(std::shared_ptr<IShader> shader);
	static std::shared_ptr<Material> createDefault();

	bool remove_property(const std::string& name);
	bool has_property(const std::string& name);

	/// <summary>
	/// Returns a property with the given name. If it does not exist, it will be created.
	/// </summary>
	/// <param name="name">Name of the property.</param>
	/// <returns>Weak ptr to the referenced property.</returns>
	std::weak_ptr<MaterialProperty> get_property(const std::string& name);

	void send_to_shader();

	std::shared_ptr<IShader> get_shader() const { return shader; }
	void set_shader(std::shared_ptr<IShader> value);

private:
	Material(std::shared_ptr<IShader> shader);
};