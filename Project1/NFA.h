#pragma once
#ifndef NFA_H
#define NFA_H

#include "FA.h"
#include "Util.h"
#include <algorithm>
#include <cassert> 
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <unordered_map>


class NFA : public FA {
private:
    std::set<State*> startState;

public:
    NFA(std::string filename); // ���캯�������ļ��ж�ȡ�����ķ�������NFA
    NFA(std::set<State*> startState, std::set<State*> finalState); // ���캯����ʹ�ø�������ʼ״̬����ֹ״̬
    ~NFA(); // ���� NFA ����
    void buildNFA(std::string filename); // ���ļ��ж�ȡ�����ķ�������NFA
    // ����һ�������ַ�������ģ��NFA�Ը������ַ����Ĵ�����̣������Ƿ���������ַ�����
    bool accept(std::string input);
    void addStartState(State* state); // �����ʼ״̬
    std::set<State*> getStartState() const; // ��ȡ��ʼ״̬
};

#endif // NFA_H
