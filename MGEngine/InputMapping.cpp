#include "InputMapping.hpp"
#include "Log.hpp"
#include "IInputBackend.hpp"


InputDevices InputMapping::get_device() {
	return device;
}

std::string InputMapping::get_name() {
	return name;
}

void InputMapping::update(IInputBackend* backend, Vector2<float> mouseMovement, Vector2f scrollDelta) {
	float ret = 0;
	switch (device) {
	case InputDevices::Keyboard:
		if (positiveKey != KeyboardKeys::UNKNOWN) {
			ret = backend->is_key_pressed(positiveKey) ? 1.0f : 0.0f;
		}

		if (negativeKey != KeyboardKeys::UNKNOWN) {
			ret -= backend->is_key_pressed(negativeKey) ? 1.0f : 0.0f;
		}
		break;

	case InputDevices::Mouse:
		if (mouseAxis != MouseAxis::UNKNOWN) {
			switch (mouseAxis) {
			case MouseAxis::X:
				ret = mouseMovement.x;
				break;
			case MouseAxis::Y:
				ret = mouseMovement.y;
				break;
			case MouseAxis::ScrollX:
				ret = scrollDelta.x;
				break;
			case MouseAxis::ScrollY:
				ret = scrollDelta.y;
				break;
			}
		}
		break;
	case InputDevices::Joystick:
		ELOG_FATAL("Not implemented");
		break;
	}

	ret = settings.getValue(ret);
	lastValue = this->value;
	this->value = ret;
}

bool InputMapping::is_pressed() {
	return value >= 0.5f;
}

float InputMapping::get_value() {
	return value;
}

bool InputMapping::is_just_pressed() {
	return is_pressed() && (lastValue < 0.5f);
}

InputMapping::InputMapping(std::string name, KeyboardKeys positiveKey, KeyboardKeys negativeKey, InputMappingSettings settings) {
	this->name = name;
	this->positiveKey = positiveKey;
	this->negativeKey = negativeKey;
	this->device = InputDevices::Keyboard;
	this->settings = settings;
}

InputMapping::InputMapping(std::string name, MouseAxis axis, InputMappingSettings settings) {
	this->name = name;
	this->mouseAxis = axis;
	this->device = InputDevices::Mouse;
	this->settings = settings;
}

float InputMappingSettings::getValue(float x) {
	int sign = inverted ? -FloatUtils::Sign(x) : FloatUtils::Sign(x);
	float abs = std::abs(x);
	float val = (abs - deadzone) / (1.0f - deadzone);
	if (val < 0)
		val = 0;

	return sign * val * multiplier;
}

InputMappingSettings::InputMappingSettings(float multiplier, float deadzone, bool inverted) {
	this->multiplier = multiplier;
	this->deadzone = deadzone;
	this->inverted = inverted;
}
