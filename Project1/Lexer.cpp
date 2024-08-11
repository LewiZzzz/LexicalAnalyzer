#include "Lexer.h"
#include "NFAtoDFA.h"
#include "Util.h"
#include "Config.h"
#include <iostream>
#include <fstream>

int symbolNumber = 0, error = 0;

void Lexer::lexicalAnalysis(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << filename << " 文件打开失败！" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 1;
    std::vector<Token> tokenizer;
    NFA constNFA("ConstGrammer.txt");
    DFA constDFA = NFAtoDFA(constNFA);
    NFA identifyerNFA("IdentifierGrammer.txt");
    DFA identifyerDFA = NFAtoDFA(identifyerNFA);
    NFA operatorNFA("OperatorGrammer.txt");
    DFA operatorDFA = NFAtoDFA(operatorNFA);
    NFA otherNFA("OtherGrammer.txt");
    DFA otherDFA = NFAtoDFA(otherNFA);

    while (std::getline(file, line)) {
        processLine(line, lineNumber, tokenizer);
        lineNumber++;
    }

    printf("Summary: %d lines, %d symbols, %d errors found\n", lineNumber - 1, symbolNumber - 1, error);
    // 写入result.


    writeToken(tokenizer, "output.txt");

    // 创建并打开文件
    std::ofstream outFile("result.txt");
    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // 写入文件
    outFile << "Summary: " << (lineNumber - 1) << " lines, " << (symbolNumber - 1)
        << " symbols, " << error << " errors found" << std::endl;

    // 关闭文件
    outFile.close();
}


void Lexer::processTokens(const std::vector<std::string>& tokens, int lineNumber, std::vector<Token>& tokenizer) {
    static NFA constNFA("ConstGrammer.txt");
    static DFA constDFA = NFAtoDFA(constNFA);
    static NFA identifyerNFA("IdentifierGrammer.txt");
    static DFA identifyerDFA = NFAtoDFA(identifyerNFA);
    static NFA operatorNFA("OperatorGrammer.txt");
    static DFA operatorDFA = NFAtoDFA(operatorNFA);
    static NFA otherNFA("OtherGrammer.txt");
    static DFA otherDFA = NFAtoDFA(otherNFA);

    std::vector<std::string> newTokens;
    std::string tempToken;
    for (const auto& token : tokens) {
        if (constDFA.accept(tempToken + token) || operatorDFA.accept(tempToken + token)) {
            tempToken += token;
        }
        else {
            if (!tempToken.empty()) {
                newTokens.push_back(tempToken);
            }
            tempToken = token;
        }
    }
    if (!tempToken.empty()) {
        newTokens.push_back(tempToken);
    }

    for (const auto& token : newTokens) {
        if (identifyerDFA.accept(token)) {
            if (isKeyWord(token, keyword)) {
                printf("<line:%2d> Symbol(%2d) Keyword       [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
                tokenizer.push_back({ lineNumber, "Keyword", token });
            }
            else if (isQualifier(token, qualifiers)) {
                printf("<line:%2d> Symbol(%2d) Qualifier     [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
                tokenizer.push_back({ lineNumber, "Qualifier", token });
            }
            else {
                printf("<line:%2d> Symbol(%2d) Identifier    [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
                tokenizer.push_back({ lineNumber, "Identifier", token });
            }
        }
        else if (constDFA.accept(token)) {
            printf("<line:%2d> Symbol(%2d) Constant      [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
            tokenizer.push_back({ lineNumber, "Constant", token });
        }
        else if (operatorDFA.accept(token)) {
            printf("<line:%2d> Symbol(%2d) Operator      [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
            tokenizer.push_back({ lineNumber, "Operator", token });
        }
        else if (otherDFA.accept(token)) {
            printf("<line:%2d> Symbol(%2d) Other         [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
            tokenizer.push_back({ lineNumber, "Other", token });
        }
        else {
            error++;
            printf("<line:%2d> Symbol(%2d) Error!!!      [token: %10s]\n", lineNumber, symbolNumber++, token.c_str());
            tokenizer.push_back({ lineNumber, "ErrorNode", token });
        }
    }
}


void Lexer::processLine(const std::string& line, int lineNumber, std::vector<Token>& tokenizer) {
    std::vector<std::string> processTokens = split(line, ' ');
    for (auto& token : processTokens) {
        trim(token);
    }

    std::vector<std::string> tokens;
    for (auto& p : processTokens) {
        auto temp = split(p, splitTokens);
        tokens.insert(tokens.end(), temp.begin(), temp.end());
    }

    Lexer::processTokens(tokens, lineNumber, tokenizer);
}
