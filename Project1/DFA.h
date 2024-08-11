#pragma once
#ifndef DFA_H
#define DFA_H

#include "FA.h"
#include <queue> 
#include <iostream>

class DFA : public FA {
private:
    State* startState; // 起始状态指针

public:
    DFA(State* startState, std::set<char> alphabet); // 构造函数，接受起始状态和字母表作为参数
    ~DFA(); // 析构函数
    State* getStartState() const; // 获取起始状态指针
    void print(); // 打印 DFA 状态转移图 用于debug
    bool accept(std::string input); // 接受一个输入字符串，并模拟 DFA 对该输入字符串的处理过程，返回是否接受输入字符串。
    State* getTransitionSource(State* state, char input); // 找到能经过input到达该状态的状态
};

#endif // DFA_H
