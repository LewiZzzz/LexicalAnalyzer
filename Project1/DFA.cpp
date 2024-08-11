#include "DFA.h"

// 构造函数的实现
DFA::DFA(State* startState, std::set<char> alphabet) {
    this->startState = startState;
    this->alphabet = alphabet;
}

// 析构函数的实现
DFA::~DFA() {
    delete startState;
}

// 获取起始状态指针的实现
State* DFA::getStartState() const {
    return startState;
}

// 打印 DFA 状态转移图的实现
void DFA::print() {
    std::queue<State*> q;
    std::set<State*> visited;
    std::cout << "开始打印dfa:" << std::endl;
    q.push(startState);
    while (!q.empty()) {
        State* s = q.front();
        q.pop();
        if (visited.find(s) != visited.end()) {
            continue;
        }
        visited.insert(s);
        for (auto c : alphabet) {
            for (auto state : s->getTransitions(c)) {
                // 输出状态转移信息
                std::cout << s->getStateId() - startState->getStateId() << " " << c << " " << state->getStateId() - startState->getStateId() << " " << state->isFinalState() << std::endl;
                q.push(state);
            }
        }
    }
}

// 接受一个输入字符串，并模拟 DFA 对该输入字符串的处理过程，返回是否接受输入字符串。
bool DFA::accept(std::string input) {
    State* currentState = startState;
    for (char c : input) {
        // 如果当前字母不在字母表中，返回 false
        if (alphabet.find(c) == alphabet.end()) {
            return false;
        }
        std::set<State*> nextStates = currentState->getTransitions(c);
        if (nextStates.empty()) {
            return false;
        }
        currentState = *nextStates.begin();
    }
    return currentState->isFinalState();
}


State* DFA::getTransitionSource(State* state, char input) {
    // 获取DFA的所有状态
    std::set<State*> states = this->getState();

    // 遍历所有状态
    for (State* s : states) {
        // 获取从状态s通过输入字符input能够到达的状态集合
        std::set<State*> nextStates = s->getTransitions(input);

        // 检查是否能通过input到达目标状态state
        if (nextStates.find(state) != nextStates.end()) {
            return s; // 找到源状态，返回
        }
    }

    return nullptr; // 如果没有找到，返回nullptr
}
