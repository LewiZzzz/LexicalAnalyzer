#include "NFA.h"

// ���캯�������ļ��ж�ȡ�����ķ�������NFA
NFA::NFA(std::string filename) {
    buildNFA(filename);
}

// ���캯����ʹ�ø�������ʼ״̬����ֹ״̬
NFA::NFA(std::set<State*> startState, std::set<State*> finalState) {
    this->startState = startState;
    this->finalState = finalState;
}

// ���� NFA ����
NFA::~NFA() {
    for (auto state : startState) {
        delete state;
    }
    for (auto state : finalState) {
        delete state;
    }
}

// ���ļ��ж�ȡ�����ķ�������NFA
void NFA::buildNFA(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "�ļ���ʧ�ܣ�" << std::endl;
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
        // ����ʽ���磺 A->aA
        // ��д��ĸ�Ƿ��ս����Сд��ĸ���ս��
        if (line.empty()) continue;
        while (line.back() == ' ' || line.back() == '\t') line.pop_back();
        if (line.size() <= 3 || line.size() > 5) {
            std::cout << "����ʽ��ʽ����" << std::endl;
            std::cout << "����Ĳ���ʽ��ʽΪ��" << line << std::endl;
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

// ����һ�������ַ�������ģ��NFA�Ը������ַ����Ĵ�����̣������Ƿ���������ַ�����
bool NFA::accept(std::string input) {
    std::set<State*> currentStates = startState;
    for (char c : input) {
        // �����ǰ��ĸ������ĸ���У�����false
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

// �����ʼ״̬
void NFA::addStartState(State* state) {
    startState.insert(state);
}

// ��ȡ��ʼ״̬
std::set<State*> NFA::getStartState() const {
    return startState;
}
