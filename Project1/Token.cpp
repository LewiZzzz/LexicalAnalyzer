#include "Token.h"
#include <fstream>
#include <iostream>

// ���� std::vector<Token> �� == ������
bool operator==(const std::vector<Token>& lhs, const std::vector<Token>& rhs) {
    // �����С��ͬ��ֱ�ӷ��� false
    if (lhs.size() != rhs.size()) {
        return false;
    }

    // �Ƚ�ÿ��Ԫ���Ƿ����
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
