#pragma once
#include <string>
#include <fstream>
#include "Log.h"
#include <filesystem>

class File {
public:
	static std::string LoadAllText(std::string path) {
		std::string text;
		std::string line;
		std::ifstream file(path);
		if (file.is_open()) {
			while (getline(file, line)) {
				text += line + "\n";
			}
			file.close();
		}
		else {
			ELOG_INFO("Current directory: ", std::filesystem::current_path().string());
			ELOG_FATAL("Unable to open file: ", path);
		}
		return text;
	}

	static std::vector<std::string> LoadAllLines(std::string path) {
		std::vector<std::string> ret;
		std::string line;
		std::ifstream file(path);
		if (file.is_open()) {
			while (getline(file, line)) {
				ret.push_back(line);
			}
			file.close();
		}
		else {
			ELOG_FATAL("Unable to open file: ", path);
		}
		return ret;
	}

	static uint8_t ReadUInt8(std::ifstream& file, int& offset) {
		uint8_t ret;
		file.read((char*)&ret, sizeof(uint8_t));
		offset += sizeof(uint8_t);
		return ret;
	}

	static uint16_t ReadUInt16(std::ifstream& file, int& offset) {
		uint16_t ret;
		file.read((char*)&ret, sizeof(uint16_t));
		offset += sizeof(uint16_t);
		return ret;
	}

	static uint32_t ReadUInt32(std::ifstream& file, int& offset) {
		uint32_t ret;
		file.read((char*)&ret, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		return ret;
	}

	static float ReadFloat(std::ifstream& file, int& offset) {
		float ret;
		file.read((char*)&ret, sizeof(float));
		offset += sizeof(float);
		return ret;
	}

	static double ReadDouble(std::ifstream& file, int& offset) {
		double ret;
		file.read((char*)&ret, sizeof(double));
		offset += sizeof(double);
		return ret;
	}

	static uint64_t ReadUInt64(std::ifstream& file, int& offset) {
		uint64_t ret;
		file.read((char*)&ret, sizeof(uint64_t));
		offset += sizeof(uint64_t);
		return ret;
	}
};