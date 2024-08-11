#include <set>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>

#include "config.h"


std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(s);
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

// 如果有在v中的字符，就单独将它分出来作为一个token 例如v中有key ，s中有keyword，那么就将key分出来
std::vector<std::string> split(const std::string& s, std::vector<std::string> v) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(s);
	while (ss >> token) {
		if (find(v.begin(), v.end(), token) != v.end()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

// 是否是大写字母
bool isUpperCase(char c) {
	return c >= 'A' && c <= 'Z';
}

// 是否是小写字母
bool isLowerCase(char c) {
	return c >= 'a' && c <= 'z';
}

// 字符c是否在字符集合C中
bool inCharSet(char c, std::set<char> C) {
	return C.find(c) != C.end();
}

bool isOperator(std::string s) {
	for (auto op : operators) {
		if (s == op) {
			return true;
		}
	}
	return false;
}

bool isKeyWord(std::string s) {
	for (auto kw : keyword) {
		if (s == kw) {
			return true;
		}
	}
	return false;
}

bool isPunctuator(std::string s) {
	for (auto p : punctuators) {
		if (s == p) {
			return true;
		}
	}
	return false;
}

bool isQualifier(std::string s) {
	for (auto q : qualifiers) {
		if (s == q) {
			return true;
		}
	}
	return false;
}