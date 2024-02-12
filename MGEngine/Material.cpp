#include "Material.hpp"

 void Material::send_to_shader() {
	 for(MaterialProperty& prop : this->properties) {
		 prop.send_to_shader(this->shader.get());
	 }
 }
