#include "Token.h"
#include <fstream>
#include <iostream>

// 重载 std::vector<Token> 的 == 操作符
bool operator==(const std::vector<Token>& lhs, const std::vector<Token>& rhs) {
    // 如果大小不同，直接返回 false
    if (lhs.size() != rhs.size()) {
        return false;
    }

    // 比较每个元素是否相等
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }

    return true;
}

void writeToken(const std::vector<Token>& tokens, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    for (const auto& token : tokens) {
        outFile << token.lineNumber << " " << token.type << " " << token.token << std::endl;
    }

    outFile.close();
}
