#pragma once
#ifndef DFA_H
#define DFA_H

#include "FA.h"
#include <queue> 
#include <iostream>

class DFA : public FA {
private:
    State* startState; // ��ʼ״ָ̬��

public:
    DFA(State* startState, std::set<char> alphabet); // ���캯����������ʼ״̬����ĸ����Ϊ����
    ~DFA(); // ��������
    State* getStartState() const; // ��ȡ��ʼ״ָ̬��
    void print(); // ��ӡ DFA ״̬ת��ͼ ����debug
    bool accept(std::string input); // ����һ�������ַ�������ģ�� DFA �Ը������ַ����Ĵ�����̣������Ƿ���������ַ�����
    State* getTransitionSource(State* state, char input); // �ҵ��ܾ���input�����״̬��״̬
};

#endif // DFA_H
