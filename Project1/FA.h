#pragma once
#ifndef FA_H
#define FA_H

#include <set>
#include "State.h" 

class FA {
protected:
    std::set<State*> finalState; // ��ֹ״̬����
    std::set<State*> state; // ״̬����
    std::set<char> alphabet; // ��ĸ��

public:
    FA(); // ���캯��
    ~FA(); // ��������
    void addState(State* state); // ���״̬
    void addFinalState(State* state); // �����ֹ״̬
    void addAlphabet(char input); // �����ĸ��
    void addTransition(char input, State* fromState, State* toState); // ���ת��
    std::set<char> getAlphaBet(); // ��ȡ��ĸ��
    // ״̬�� a ��ת��: ��״̬ S �������ַ� a ���ܵ����״̬�ļ��ϡ�
    std::set<State*> move(State* state, char c);
    // ״̬���� I �� a ��ת��: ��״̬�� I �е��κ�״̬ S �������ַ� a ���ܵ����״̬�ļ��ϡ�
    std::set<State*> move(std::set<State*> states, char c);
    std::set<State*> getFinalState() const; // ��ȡ��ֹ״̬
    std::set<State*> getState() const; // ��ȡ״̬����
};

#endif // FA_H
