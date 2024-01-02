#pragma once
#include <vector>
#include <optional>

class Compression {
public:
	static std::optional<std::vector<uint8_t>> DecompressGZip(std::vector<uint8_t> data);
};