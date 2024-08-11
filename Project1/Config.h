#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <cstring>

std::vector<std::string> keyword = {
	"int", "double", "float", "complex", "long", "short", "char", "string",
	"bool", "void", "if", "else", "while", "for", "return", "break", "continue", "function", "using",
	"namespace","include"
};

std::vector<std::string> operators = {
	"+", "-", "*", "/", "%", "++", "--", "+=", "-=", "*=", "/=", "%=",
	"==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^",
	"~",  "&=", "|=", "^=", "=", 
};

std::vector<std::string> punctuators = {
	"(", ")", "[", "]", "{", "}", ",", ";", ":", "#", "##", "<", ">"
};

std::vector<std::string> splitTokens = {
	"(", ")", "[", "]", "{", "}", ",", ";", ":", "#", "##", "<", ">",
	"++", "--", "+=", "-=", "*=", "/=", "%=",
	"==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^",
	"~",  "&=", "|=", "^=", "=",
};

std::vector<std::string> qualifiers = {
	"const", "volatile", "restrict", "mutable", "register", "inline", "extern", "static", 
};

#endif