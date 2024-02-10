#pragma once
#include "Config.hpp"
#include "Log.hpp"

class ITexture {

	virtual void _init_() = 0;
	virtual void _update_(unsigned char* data) = 0;
	virtual void _dispose_() = 0;

protected:
	unsigned int width;
	unsigned int height;
	unsigned int channelCount;

public:

	// TODO: Add other texture parameters (format, etc)
	void init(unsigned int width, unsigned int height, unsigned int channelCount) {
		this->width = width;
		this->height = height;
		this->channelCount = channelCount;
		_init_();
	}

	void update(unsigned char* data) {
#if SC_WARNING_ON
		if(this->width == 0 || this->height == 0) {
			ELOG_WARNING("Texture not initialized");
		}
#endif

		_update_(data);
	}

	void update(unsigned int width, unsigned int height, unsigned char* data) {
		if(this->width != width || this->height != height) {
			_dispose_();
			init(width, height, channelCount);
		}
		update(data);
	}

	void loadFromFile(const char* path);

	// TODO: Add different targets (1D, 2D, 3D, slots, etc)
	// TODO: Add bind TRACE log calls in the entire engine
	virtual void bind(unsigned int slot) = 0;
};