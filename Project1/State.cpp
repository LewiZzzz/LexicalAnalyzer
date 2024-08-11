#include "State.h"


State::State() {
	this->isFinal = false;
	stateCount++;
	this->id = stateCount;
}
	

State::State(bool isFinal) {
	this->isFinal = isFinal;
	stateCount++;
	this->id = stateCount;
}
// ���ת��
void State::addTransition(char input, State* nextState) {
	transitions[input].insert(nextState);
}

// ��ȡͨ�������ַ�ת�Ƶ���״̬����
set<State*> State::getTransitions(char input) {
	if (transitions.find(input) != transitions.end()) {
		return transitions[input];
	}
	return {};
}

// ��ȡ��״̬����һ��EPS��ת�Ƶ���״̬����
set<State*> State::getEpsTransition() {
	return getTransitions(EPS);
}

// ��ȡ��״̬����������EPS��ת�Ƶ���״̬���ϣ���EPS�հ�
set<State*> State::getEpsTransitions() {
	set<State*> epsTransitions;
	queue<State*> q;
	q.push(this);
	while (!q.empty()) {
		State* s = q.front();
		q.pop();
		set<State*> nextStates = s->getTransitions(EPS);
		for (auto state : nextStates) {
			if (epsTransitions.find(state) == epsTransitions.end()) {
				epsTransitions.insert(state);
				q.push(state);
			}
		}
	}
	return epsTransitions;
}

// �����Ƿ�����̬
void State::setFinalState(bool isFinal) {
	this->isFinal = isFinal;
}

bool State::isFinalState() const {
	return this->isFinal;
}

int State::getStateId() const {
	return this->id;
}