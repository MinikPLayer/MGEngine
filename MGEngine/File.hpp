#pragma once
#include <string>
#include <fstream>
#include "Log.hpp"
#include <filesystem>

class File {
public:
	const static std::string engineAssetsPath;
	const static std::string userAssetsPath;

	const static std::string engineUri;
	const static std::string userUri;

#if defined(_WIN32) || defined(__WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif	


	static std::string CombinePaths(std::string p1, std::string p2) {
		if (p1.size() != 0 && (p1.ends_with("\\") || p1.ends_with("/"))) {
			p1 = p1.substr(0, p1.length() - 1);
		}

		if (p2.starts_with("/") || (p2.length() >= 2 && p2[1] == ':')) {
			ELOG_WARNING("Second path is an absolute path. Using it as a whole path");
			return p2;
		}

		std::stringstream ss;
		ss << p1 << PATH_SEPARATOR << p2;
		return ss.str();
	}

	static std::string GetUriLocation(std::string path) {
		if (path.starts_with(engineUri)) {
			path = path.substr(engineUri.length());
			return CombinePaths(engineAssetsPath, path);
		}
		else if (path.starts_with(userUri)) {
			path = path.substr(userUri.length());
			return CombinePaths(userAssetsPath, path);
		}
		else {
			if (path.find("://") == -1) {
				return path;
			}

			ELOG_FATAL("Unknown uri: ", path);
		}
	}

	static std::string LoadAllText(std::string path) {
		path = GetUriLocation(path);

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
		path = GetUriLocation(path);

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