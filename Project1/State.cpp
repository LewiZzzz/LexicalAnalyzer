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
// 添加转移
void State::addTransition(char input, State* nextState) {
	transitions[input].insert(nextState);
}

// 获取通过输入字符转移到的状态集合
set<State*> State::getTransitions(char input) {
	if (transitions.find(input) != transitions.end()) {
		return transitions[input];
	}
	return {};
}

// 获取该状态经任一条EPS弧转移到的状态集合
set<State*> State::getEpsTransition() {
	return getTransitions(EPS);
}

// 获取该状态经任若干条EPS弧转移到的状态集合，即EPS闭包
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

// 设置是否是终态
void State::setFinalState(bool isFinal) {
	this->isFinal = isFinal;
}

bool State::isFinalState() const {
	return this->isFinal;
}

int State::getStateId() const {
	return this->id;
}