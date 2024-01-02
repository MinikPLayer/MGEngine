#pragma once
#include <optional>
#include <chrono>

class Time
{
	static float _dt;
	static std::optional<std::chrono::high_resolution_clock::time_point> _lastTime;
	static std::chrono::high_resolution_clock::time_point _startTime;

public:
	static float ElapsedTime() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<float>(now - _startTime).count();
	}

	static float DeltaTime() {
		return _dt;
	}

	static void __Update() {
		auto now = std::chrono::high_resolution_clock::now();

		if (_lastTime.has_value()) {
			_dt = std::chrono::duration<float>(now - _lastTime.value()).count();
		}

		_lastTime = now;
	}
};

