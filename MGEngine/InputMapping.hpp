#pragma once
#include "InputStructs.hpp"
#include "IInputBackend.hpp"
#include <string>

struct InputMappingSettings {
	float multiplier = 1.0f;
	float deadzone = 0.0f;
	bool inverted = false;

	float getValue(float x);

	InputMappingSettings(float multiplier = 1, float deadzone = 0, bool inverted = 0);
};

class InputMapping {
	float value = 0;
	float lastValue = 0;

	std::string name;
	InputDevices device;

	KeyboardKeys positiveKey = KeyboardKeys::UNKNOWN;
	KeyboardKeys negativeKey = KeyboardKeys::UNKNOWN;

	MouseAxis mouseAxis = MouseAxis::UNKNOWN;

	InputMappingSettings settings;
public:
	InputDevices get_device();
	std::string get_name();
	void update(IInputBackend* backend, Vector2<float> mouseMovement, Vector2f scrollDelta);
	bool is_pressed();
	float get_value();
	bool is_just_pressed();

	InputMapping(std::string name, KeyboardKeys positiveKey, KeyboardKeys negativeKey = KeyboardKeys::UNKNOWN, InputMappingSettings settings = InputMappingSettings());
	InputMapping(std::string name, MouseAxis axis, InputMappingSettings settings = InputMappingSettings());
};