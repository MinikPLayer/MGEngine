#include "Renderer/ITexture.hpp"
#include <cstdint>
#include "Log.hpp"
#include "File.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void ITexture::loadFromFile(const char* path) {
	auto rawPath = File::GetUriLocation(path);

	int width, height, nrChannels;
	uint8_t* data = stbi_load(rawPath.c_str(), &width, &height, &nrChannels, 0);
	if (data == nullptr) {
		ELOG_FATAL("Failed to load texture");
		return;
	}

	init(width, height, nrChannels);
	update(data);
}
