#include "MaterialProperty.hpp"

void MaterialPropertyFunctions::SendToShaderInt(MaterialProperty* prop, IShader* shader) {
	shader->set_uniform_1i(prop->location, prop->value_int);
}

void MaterialPropertyFunctions::SendToShaderUint(MaterialProperty* prop, IShader* shader) {
	shader->set_uniform_1ui(prop->location, prop->value_int);
}

void MaterialPropertyFunctions::SendToShaderFloat(MaterialProperty* prop, IShader* shader) {
#if SC_ERROR_ON
	if(prop->value_floats.size() != 1) {
		ELOG_ERROR("MaterialPropertyFunctions::SendToShaderFloat: value_floats.size() != 1. \nMaterialProperty function is set to type float, but value is not a single float type!\nExpected size() to be 1, actual value: ", prop->value_floats.size());
		return;
	}
#endif

	shader->set_uniform_1f(prop->location, prop->value_floats[0]);
}

void MaterialPropertyFunctions::SendToShaderFloat3(MaterialProperty* prop, IShader* shader) {
#if SC_ERROR_ON
	if (prop->value_floats.size() != 3) {
		ELOG_ERROR("MaterialPropertyFunctions::SendToShaderFloat: value_floats.size() != 3. \nMaterialProperty function is set to type float, but value is not a single float type!\nExpected size() to be 3, actual value: ", prop->value_floats.size());
		return;
	}
#endif

	shader->set_uniform_3f(prop->location, prop->value_floats[0], prop->value_floats[1], prop->value_floats[2]);
}
