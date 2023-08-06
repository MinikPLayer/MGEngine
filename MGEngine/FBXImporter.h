#pragma once
#include <vector>
#include "Mesh.h"
#include <string>

enum FBXPropertyType {
	TYPE_INT16 = 'Y',
	TYPE_BOOL = 'C',
	TYPE_INT32 = 'I',
	TYPE_FLOAT = 'F',
	TYPE_DOUBLE = 'D',
	TYPE_INT64 = 'L',
	ARRAY_FLOAT = 'f',
	ARRAY_DOUBLE = 'd',
	ARRAY_INT64 = 'l',
	ARRAY_INT32 = 'i',
	ARRAY_BOOL = 'b',
	STRING = 'S',
	RAW = 'R',
};

struct FBXProperty {
	struct Data {
		int64_t value64;
		double valueDouble;
		std::string valueString;
		std::vector<unsigned char> valueRaw;

		Data(int64_t value) : value64(value) {}
		Data(double value) : valueDouble(value) {}
		Data(std::string value) : valueString(value) {}
		Data(std::vector<unsigned char> value) : valueRaw(value) {}

		std::string toString(FBXPropertyType type) {
			switch (type)
			{
			case TYPE_INT16:
				return std::to_string((int16_t)value64);
			case ARRAY_BOOL:
			case TYPE_BOOL:
				return std::to_string((bool)value64);
			case ARRAY_INT32:
			case TYPE_INT32:
				return std::to_string((int32_t)value64);
			case ARRAY_FLOAT:
			case TYPE_FLOAT:
				return std::to_string((float)valueDouble);
			case ARRAY_DOUBLE:
			case TYPE_DOUBLE:
				return std::to_string(valueDouble);
			case ARRAY_INT64:
			case TYPE_INT64:
				return std::to_string(value64);
			case STRING:
				return valueString;
			case RAW:
				return "?RAW?"; // TODO: Implement this
			default:
				break;
			}
		}
	};

	std::vector<Data> data;

	FBXPropertyType type;

	void add_int16(int16_t value) {
		data.push_back(Data((int64_t)value));
	}

	void add_bool(bool value) {
		data.push_back(Data((int64_t)value));
	}

	void add_int32(int32_t value) {
		data.push_back(Data((int64_t)value));
	}

	void add_float(float value) {
		data.push_back(Data((double)value));
	}

	void add_double(double value) {
		data.push_back(Data((double)value));
	}

	void add_int64(int64_t value) {
		data.push_back(Data(value));
	}

	void add_string(std::string value) {
		data.push_back(Data(value));
	}

	void add_raw(std::vector<unsigned char> value) {
		data.push_back(Data(value));
	}

	std::string to_string() {
		std::string line = "[";
		for (auto d : data) {
			line += d.toString(type) + ", ";
		}
		line += "]";
		return line;
	}

	FBXProperty(char type) : type((FBXPropertyType)type) {}
};

struct FBXNode {
	std::vector<FBXNode> children;
	std::vector<FBXProperty> properties;
	std::string name;
};

struct FBXData {
	uint32_t version;
	FBXNode root;
};

class FBXImporter {
public:
	static FBXData Load(std::string path);
};