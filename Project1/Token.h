#pragma once
#include <string>
#include <vector>

struct Token {
    int lineNumber;
    std::string type;
    std::string token;

    // ÖØÔØ == ²Ù×÷·û
    bool operator==(const Token& other) const {
        return lineNumber == other.lineNumber &&
            type == other.type &&
            token == other.token;
    }
};


void writeToken(const std::vector<Token>& tokens, const std::string& filename);
