#pragma once
#include <vector>
#include <string>
#include "Token.h"

class Lexer {
public:
    void lexicalAnalysis(const std::string& filename);
    void processTokens(const std::vector<std::string>& tokens, int lineNumber, std::vector<Token>& tokenizer);
private:
    void processLine(const std::string& line, int lineNumber, std::vector<Token>& tokens);
    
};
