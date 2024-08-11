#include <iostream>
#include "Lexer.h"
#include "State.h"

int State::stateCount = 0;

int main() {
    Lexer lexer;
    lexer.lexicalAnalysis("input.txt");
    return 0;
}
