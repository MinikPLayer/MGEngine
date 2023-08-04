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
};