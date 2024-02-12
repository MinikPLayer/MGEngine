#pragma once

#define DEF_GET_SET_PROP(type, name) \
protected: type name; \
public: \
	type get_##name() const { return name; } \
	void set_##name(type value) { name = value; }

#define DEF_GET_SET_PROP_VALUE(type, name, value) \
protected: type name = value; \
public: \
	type get_##name() const { return name; } \
	void set_##name(type v) { name = v; }