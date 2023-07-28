#pragma once
#include <string>
#include <vector>

class StringUtils {
public:
	static std::vector<std::string> split(std::string str, char delim) {
		std::vector<std::string> result;
		std::string temp = "";
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == delim) {
				result.push_back(temp);
				temp = "";
			}
			else {
				temp += str[i];
			}
		}
		result.push_back(temp);
		return result;
	}
};