#pragma once
#include <vector>
#include <optional>
#include <cstdint>

class Compression {
public:
	static std::optional<std::vector<uint8_t>> DecompressGZip(std::vector<uint8_t> data);
};