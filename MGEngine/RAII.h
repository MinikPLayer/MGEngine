#pragma once
#include <optional>

// Move Only Object
template<typename T>
class MOO {
private:
	std::optional<T> value;

protected:
	virtual void __dispose() {}
public:
	void dispose() {
		if (value.has_value()) {
			__dispose();
			value = std::nullopt;
		}
	}

	T& get() {
		return value.value();
	}

	// Disable copy constructors 
	MOO(const MOO&) = delete;
	MOO& operator=(const MOO&) = delete;

	// Move constructors
	MOO(MOO&& o) {
		if (value.has_value()) {
			__dispose();
		}

		value = std::move(o.value);
		o.value = std::nullopt;
	}
	MOO& operator=(MOO&& o) {
		if (value.has_value()) {
			__dispose();
		}

		value = std::move(o.value);
		o.value = std::nullopt;

		return *this;
	}

	MOO() {
		value = std::nullopt;
	}

	MOO(T value) {
		this->value = value;
	}

	~MOO() {
		if (value != std::nullopt)
			__dispose();
	}
};

// Define a MOO type, dispose function gets the value as x
#define DEF_MOO_TYPE(name, T, dispose_func) \
	class name : public MOO<T> { \
	protected: \
		void __dispose() override { \
			auto x = get(); \
			dispose_func; \
		} \
	public: \
		name() : MOO<T>() {} \
		name(T value) : MOO<T>(value) {} \
	}