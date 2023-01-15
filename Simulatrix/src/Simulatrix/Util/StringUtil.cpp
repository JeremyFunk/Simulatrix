#include "simixpch.h"
#include "StringUtil.h"

namespace Simulatrix {
	std::vector<std::string> Split(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
	std::string Replace(const std::string& s, char find, char replace) {
		std::string result = s;
		for (size_t i = 0; i < result.size(); i++) {
			if (result[i] == find) {
				result[i] = replace;
			}
		}
		return result;
	}
	std::string DirectoryUp(const std::string& path) {
		return path.substr(0, path.find_last_of("\\"));
	}
}