#pragma once

class ITexture {
	virtual void _init_(unsigned int width, unsigned int height) = 0;

public:

	// TODO: Add other texture parameters (format, etc)
	void init(unsigned int width, unsigned int height) {
		_init_(width, height);
	}

	// TODO: Add different targets (1D, 2D, 3D, slots, etc)
	virtual void bind(unsigned int slot) = 0;
};