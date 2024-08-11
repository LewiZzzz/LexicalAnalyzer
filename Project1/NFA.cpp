#include "NFA.h"

// 构造函数，从文件中读取正规文法，生成NFA
NFA::NFA(std::string filename) {
    buildNFA(filename);
}

// 构造函数，使用给定的起始状态和终止状态
NFA::NFA(std::set<State*> startState, std::set<State*> finalState) {
    this->startState = startState;
    this->finalState = finalState;
}

// 销毁 NFA 对象
NFA::~NFA() {
    for (auto state : startState) {
        delete state;
    }
    for (auto state : finalState) {
        delete state;
    }
}

// 从文件中读取正规文法，生成NFA
void NFA::buildNFA(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "文件打开失败！" << std::endl;
        return;
    }
    std::string line;
    std::set<char> nonTerminal;
    State* finalState = new State(true);
    addFinalState(finalState);
    State* startState = new State();
    addStartState(startState);
    std::unordered_map<char, State*> nonTerminalStateMap;
    while (std::getline(file, line)) {
        // 产生式形如： A->aA
        // 大写字母是非终结符，小写字母是终结符
        if (line.empty()) continue;
        while (line.back() == ' ' || line.back() == '\t') line.pop_back();
        if (line.size() <= 3 || line.size() > 5) {
            std::cout << "产生式格式错误！" << std::endl;
            std::cout << "错误的产生式格式为：" << line << std::endl;
            return;
        }

        if (!inCharSet(line[3], alphabet) && line[3] != '$') {
            addAlphabet(line[3]);
        }

        if (!inCharSet(line[0], nonTerminal) && line[0] != '@') {
            nonTerminal.insert(line[0]);
            nonTerminalStateMap[line[0]] = new State();
            addState(nonTerminalStateMap[line[0]]);
        }

        // case 1: A->aA @->aA
        if (line.size() == 5) {
            if (!inCharSet(line[4], nonTerminal)) {
                nonTerminal.insert(line[4]);
                nonTerminalStateMap[line[4]] = new State();
                addState(nonTerminalStateMap[line[4]]);
            }
            if (line[0] == '@') {
                addTransition(line[3], startState, nonTerminalStateMap[line[4]]);
                continue;
            }
            addTransition(line[3], nonTerminalStateMap[line[0]], nonTerminalStateMap[line[4]]);
        }
        // case 2: A->a A->$
        else {
            if (line[3] == '$') {
                addTransition(EPS, nonTerminalStateMap[line[0]], finalState);
            }
            else {
                if (!inCharSet(line[3], nonTerminal)) {
                    nonTerminal.insert(line[3]);
                    nonTerminalStateMap[line[3]] = new State();
                    addState(nonTerminalStateMap[line[3]]);
                }
                addTransition(line[3], nonTerminalStateMap[line[0]], finalState);
            }
        }
    }
    nonTerminalStateMap.clear();
}

// 接受一个输入字符串，并模拟NFA对该输入字符串的处理过程，返回是否接受输入字符串。
bool NFA::accept(std::string input) {
    std::set<State*> currentStates = startState;
    for (char c : input) {
        // 如果当前字母不在字母表中，返回false
        if (alphabet.find(c) == alphabet.end() && c != EPS) {
            return false;
        }
        std::set<State*> nextStates;
        for (auto state : currentStates) {
            std::set<State*> next = state->getTransitions(c);
            nextStates.insert(next.begin(), next.end());
        }
        currentStates = nextStates;
    }
    for (auto state : currentStates) {
        if (state->isFinalState()) {
            return true;
        }
    }
    return false;
}

// 添加起始状态
void NFA::addStartState(State* state) {
    startState.insert(state);
}

// 获取初始状态
std::set<State*> NFA::getStartState() const {
    return startState;
}
