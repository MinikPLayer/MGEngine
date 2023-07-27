#pragma once

template<typename T>
class Dirty {
	bool isDirty = false;
	T value;
public:
	Dirty() = default;
	Dirty(T value) : value(value) {}

	void set(T value) {
		this->value = value;
		isDirty = true;
	}

	T get() {
		return value;
	}

	void setDirty(bool dirty) {
		isDirty = dirty;
	}

	bool dirty() {
		return isDirty;
	}
};