#include "FBXImporter.h"
#include <fstream>
#include "File.h"
#include "Compression.h"
#include <functional>

template<typename T>
void read_array(std::vector<uint8_t>& bytes, FBXProperty& prop, std::function<void(FBXProperty&, T)> addElementFunc) {
	auto perObjectBytes = sizeof(T);
	if (bytes.size() % perObjectBytes != 0) {
		ELOG_ERROR("Incorrect array size, should be a multiple of ", perObjectBytes, ", but is ", bytes.size());
		throw std::runtime_error("Incorrect array size");
	}

	for (size_t i = 0; i < bytes.size(); i += perObjectBytes) {
		T value;
		memcpy((uint8_t*)&value, bytes.data() + i, perObjectBytes);
		addElementFunc(prop, value);
	}
}

// WARNING! Code expects a little endian system
std::optional<FBXNode> load_node(std::ifstream& file, int& offset) {
	uint32_t endOffset = File::ReadUInt32(file, offset);
	uint32_t numProperties = File::ReadUInt32(file, offset);
	uint32_t propertyListLen = File::ReadUInt32(file, offset);
	uint8_t nameLen = File::ReadUInt8(file, offset);

	FBXNode node;
	node.name.resize(nameLen);
	file.read(node.name.data(), nameLen); // read name
	offset += nameLen;

	// End of node - 13 zeros
	if (endOffset == 0 && numProperties == 0 && propertyListLen == 0 && nameLen == 0) {
		return std::nullopt;
	}

	// Properties
	for (uint32_t i = 0; i < numProperties; i++) {
		char typeCode = File::ReadUInt8(file, offset);

		FBXProperty property(typeCode);
		// Array type
		if (typeCode >= 'a' && typeCode <= 'z') {
			uint32_t arrayLen = File::ReadUInt32(file, offset);
			uint32_t encoding = File::ReadUInt32(file, offset);
			uint32_t compressedLen = File::ReadUInt32(file, offset);

			std::vector<uint8_t> bytes;
			bytes.reserve(compressedLen);
			for (uint32_t j = 0; j < compressedLen; j++) {
				bytes.push_back(File::ReadUInt8(file, offset));
			}

			if (encoding != 0) {
				auto newBytes = Compression::DecompressGZip(bytes);
				if (!newBytes.has_value()) {
					ELOG_ERROR("[FBX] Cannot decompress gzip stream");
					throw std::runtime_error("Cannot decompress gzip stream");
				}

				bytes = newBytes.value();
			}

			switch (typeCode) {
			case 'f':
			{
				read_array<float>(bytes, property, [&](FBXProperty& prop, float value) { prop.add_float(value); });
				break;
			}
			case 'd':
			{
				read_array<double>(bytes, property, [&](FBXProperty& prop, double value) { prop.add_double(value); });
				break;
			}
			case 'l':
			{
				read_array<int64_t>(bytes, property, [&](FBXProperty& prop, int64_t value) { prop.add_int64(value); });
				break;
			}
			case 'i':
			{
				read_array<int32_t>(bytes, property, [&](FBXProperty& prop, int32_t value) { prop.add_int32(value); });
				break;
			}
			case 'b':
			{
				read_array<int8_t>(bytes, property, [&](FBXProperty& prop, int8_t value) { prop.add_bool(value > 0); });
				break;
			}
			default:
				ELOG_FATAL("Unknown array property type: " + std::to_string(typeCode));
				throw std::runtime_error("Unknown array property type: " + std::to_string(typeCode));
			}
		}
		else {
			switch (typeCode) {

			case 'S': {
				uint32_t length = File::ReadUInt32(file, offset);
				std::string str;
				str.reserve(length);
				for (uint32_t j = 0; j < length; j++) {
					char c = File::ReadUInt8(file, offset);
					str.push_back(c);
				}
				property.add_string(str);
				break;
			}

			case 'R': {
				uint32_t length = File::ReadUInt32(file, offset);
				std::vector<unsigned char> rawData;
				rawData.reserve(length);
				for (uint32_t j = 0; j < length; j++) {
					unsigned char c = File::ReadUInt8(file, offset);
					rawData.push_back(c);
				}
				property.add_raw(rawData);
				break;
			}

			case 'Y': {
				int16_t value = (int16_t)File::ReadUInt16(file, offset);
				property.add_int16(value);
				break;
			}
			case 'C': {
				bool value = File::ReadUInt8(file, offset) != 0;
				property.add_bool(value);
				break;
			}
			case 'I': {
				int32_t value = (int32_t)File::ReadUInt32(file, offset);
				property.add_int32(value);
				break;
			}
			case 'F': {
				float value = File::ReadFloat(file, offset);
				property.add_float(value);
				break;
			}
			case 'D': {
				double value = File::ReadDouble(file, offset);
				property.add_double(value);
				break;
			}
			case 'L': {
				int64_t value = (int64_t)File::ReadUInt64(file, offset);
				property.add_int64(value);
				break;
			}
			default:
				ELOG_FATAL("Unknown property type: " + std::to_string(typeCode));
				return std::nullopt;
			}
		}

		node.properties.push_back(property);
	}

	// Nested list
	while (offset < endOffset) {
		auto nextNode = load_node(file, offset);
		if (nextNode.has_value())
			node.children.push_back(nextNode.value());
	}

	return node;
}

FBXData FBXImporter::Load(std::string path) {
	char magic[] = { 'K', 'a', 'y', 'd', 'a', 'r', 'a', ' ', 'F', 'B', 'X', ' ', 'B', 'i', 'n', 'a', 'r', 'y', ' ', ' ', '\x00', '\x1A', '\x00' };

	std::ifstream file(path, std::ios_base::binary);
	if (!file.good()) {
		ELOG_ERROR("Failed to open file: " + path);
		throw std::runtime_error("Failed to open file: " + path);
	}

	int offset = 0;
	for (int i = 0; i <= 22; i++) {
		unsigned char c = File::ReadUInt8(file, offset);

		if (c != magic[i]) {
			ELOG_ERROR("Failed to read file (magic is incorrect)");
			throw std::runtime_error("Failed to read file (magic is incorrect)");
		}
	}

	FBXData data;
	data.version = File::ReadUInt32(file, offset);
	data.root = FBXNode();
	while (!file.eof()) {
		auto nextNode = load_node(file, offset);
		if (nextNode.has_value())
			data.root.children.push_back(nextNode.value());
	}


	return data;
}
