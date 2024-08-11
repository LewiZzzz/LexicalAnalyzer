#include "DFA.h"

// ���캯����ʵ��
DFA::DFA(State* startState, std::set<char> alphabet) {
    this->startState = startState;
    this->alphabet = alphabet;
}

// ����������ʵ��
DFA::~DFA() {
    delete startState;
}

// ��ȡ��ʼ״ָ̬���ʵ��
State* DFA::getStartState() const {
    return startState;
}

// ��ӡ DFA ״̬ת��ͼ��ʵ��
void DFA::print() {
    std::queue<State*> q;
    std::set<State*> visited;
    std::cout << "��ʼ��ӡdfa:" << std::endl;
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
                // ���״̬ת����Ϣ
                std::cout << s->getStateId() - startState->getStateId() << " " << c << " " << state->getStateId() - startState->getStateId() << " " << state->isFinalState() << std::endl;
                q.push(state);
            }
        }
    }
}

// ����һ�������ַ�������ģ�� DFA �Ը������ַ����Ĵ�����̣������Ƿ���������ַ�����
bool DFA::accept(std::string input) {
    State* currentState = startState;
    for (char c : input) {
        // �����ǰ��ĸ������ĸ���У����� false
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
    // ��ȡDFA������״̬
    std::set<State*> states = this->getState();

    // ��������״̬
    for (State* s : states) {
        // ��ȡ��״̬sͨ�������ַ�input�ܹ������״̬����
        std::set<State*> nextStates = s->getTransitions(input);

        // ����Ƿ���ͨ��input����Ŀ��״̬state
        if (nextStates.find(state) != nextStates.end()) {
            return s; // �ҵ�Դ״̬������
        }
    }

    return nullptr; // ���û���ҵ�������nullptr
}
