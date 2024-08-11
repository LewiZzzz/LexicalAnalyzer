#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cstring>

// ����ָ���ķָ����ָ��ַ���
inline std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// ���ݸ������ַ������Ͻ��ַ����ָ�ɵ��� ����s = "a," v = {","}�� ��Ҫ�ָ�� "a" ","
inline std::vector<std::string> split(const std::string& s, const std::vector<std::string>& delimiters) {
	std::vector<std::string> tokens;
	std::string::size_type start = 0;

	while (start < s.size()) {
		std::string::size_type end = s.size();
		std::string delimiter;
		for (const std::string& delim : delimiters) {
			std::string::size_type pos = s.find(delim, start);
			if (pos != std::string::npos && pos < end) {
				end = pos;
				delimiter = delim;
			}
		}
		if (start < end) {
			tokens.push_back(s.substr(start, end - start));
		}

		if (!delimiter.empty()) {
			tokens.push_back(delimiter);
			start = end + delimiter.size();
		}
		else {
			start = end;
		}
	}

	return tokens;
}


inline void trim(std::string& str) {
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), str.end());
}

// ����ַ��Ƿ�Ϊ��д��ĸ
inline bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

// ����ַ��Ƿ�ΪСд��ĸ
inline bool isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

// ����ַ��Ƿ��ڸ������ַ�������
inline bool inCharSet(char c, const std::set<char>& C) {
    return C.find(c) != C.end();
}

// ����ַ����Ƿ�Ϊ�����
inline bool isOperator(const std::string& s, const std::vector<std::string>& operators) {
    return std::find(operators.begin(), operators.end(), s) != operators.end();
}

// ����ַ����Ƿ�Ϊ�ؼ���
inline bool isKeyWord(const std::string& s, const std::vector<std::string>& keywords) {
    return std::find(keywords.begin(), keywords.end(), s) != keywords.end();
}

// ����ַ����Ƿ�Ϊ������
inline bool isPunctuator(const std::string& s, const std::vector<std::string>& punctuators) {
    return std::find(punctuators.begin(), punctuators.end(), s) != punctuators.end();
}

// ����ַ����Ƿ�Ϊ�޶���
inline bool isQualifier(const std::string& s, const std::vector<std::string>& qualifiers) {
    return std::find(qualifiers.begin(), qualifiers.end(), s) != qualifiers.end();
}

#endif // UTILS_H
