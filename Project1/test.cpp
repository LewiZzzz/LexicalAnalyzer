//#include <iostream>
//#include <vector>
//#include <string>
//#include "Lexer.h"
//#include "State.h"
//
//
//
//void runTest(const std::vector<std::string>& tokens, int lineNumber, const std::vector<Token>& expectedTokens) {
//    Lexer lexer;
//    std::vector<Token> tokenizer;
//    lexer.processTokens(tokens, lineNumber, tokenizer);
//
//    if (tokenizer == expectedTokens) {
//        std::cout << "Test passed." << std::endl;
//    }
//    else {
//        std::cout << "Test failed." << std::endl;
//        std::cout << "Expected: ";
//        for (const auto& token : expectedTokens) {
//            std::cout << "{" << token.lineNumber << ", " << token.type << ", " << token.token << "} ";
//        }
//        std::cout << std::endl;
//        std::cout << "Actual: ";
//        for (const auto& token : tokenizer) {
//            std::cout << "{" << token.lineNumber << ", " << token.type << ", " << token.token << "} ";
//        }
//        std::cout << std::endl;
//    }
//}
//
//int main() {
//    runTest({ "int",  "main", "(", ")", "{", "int", "a", "=", "5", ";" }, 1, {
//        {1, "Keyword", "int"}, {1, "Identifier", "main"}, {1, "Other", "("},
//        {1, "Other", ")"}, {1, "Other", "{"}, {1, "Keyword", "int"},
//        {1, "Identifier", "a"}, {1, "Operator", "="}, {1, "Constant", "5"},
//        {1, "Other", ";"}
//        });
//
//    runTest({ "1", "+", "2", "i" }, 2, {
//        {2, "Constant", "1+2i"}
//        });
//
//    runTest({ "@invalidToken" }, 3, {
//        {3, "ErrorNode", "@invalidToken"}
//        });
//
//    runTest({ "int", "x", "=", "10", ";", "float", "y", "=","20.5", ";" }, 4, {
//        {4, "Keyword", "int"}, {4, "Identifier", "x"}, {4, "Operator", "="},
//        {4, "Constant", "10"}, {4, "Other", ";"}, {4, "Keyword", "float"},
//        {4, "Identifier", "y"}, {4, "Operator", "="}, {4, "Constant", "20.5"},
//        {4, "Other", ";"}
//        });
//
//    return 0;
//}
