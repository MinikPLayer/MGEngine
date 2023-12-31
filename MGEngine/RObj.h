#pragma once

#include <optional>

template<typename T, void (*DestructorFunc)(T&)>
class RObj {
private:
	std::optional<T> value;

public:
	void dispose() {
		if (value.has_value()) {
			DestructorFunc(value.value());
			value = std::nullopt;
		}
	}

	T& get() {
		return value.value();
	}

	bool has_value() {
		return value.has_value();
	}

	// Disable copy constructors 
	RObj(const RObj&) = delete;
	RObj& operator=(const RObj&) = delete;

	// Move constructors
	RObj(RObj&& o) {
		dispose();

		value = std::move(o.value);
		o.value = std::nullopt;
	}
	RObj& operator=(RObj&& o) {
		dispose();

		value = std::move(o.value);
		o.value = std::nullopt;

		return *this;
	}

	RObj() {
		value = std::nullopt;
	}

	RObj(T value) {
		this->value = value;
	}

	~RObj() {
		dispose();
	}
};