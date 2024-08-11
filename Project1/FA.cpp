#include "FA.h"

FA::FA() {
}

FA::~FA() {
}

void FA::addState(State* state) {
    this->state.insert(state);
}

void FA::addFinalState(State* state) {
    finalState.insert(state);
}

void FA::addAlphabet(char input) {
    // �����ظ������ĸ
    if (alphabet.find(input) == alphabet.end()) alphabet.insert(input);
}

void FA::addTransition(char input, State* fromState, State* toState) {
    fromState->addTransition(input, toState);
}

std::set<char> FA::getAlphaBet() {
    return alphabet;
}

// ״̬���� I �� a ��ת��: ��״̬�� I �е��κ�״̬ S �������ַ� a ���ܵ����״̬�ļ��ϡ�
std::set<State*> FA::move(State* state, char c) {
    return state->getTransitions(c);
}

// ״̬���� I �� a ��ת��: ��״̬�� I �е��κ�״̬ S �������ַ� a ���ܵ����״̬�ļ��ϡ�
std::set<State*> FA::move(std::set<State*> states, char c) {
    std::set<State*> nextStates;
    for (auto state : states) {
        std::set<State*> next = state->getTransitions(c);
        nextStates.insert(next.begin(), next.end());
    }
    return nextStates;
}

std::set<State*> FA::getFinalState() const {
    return finalState;
}

std::set<State*> FA::getState() const {
    return state;
}