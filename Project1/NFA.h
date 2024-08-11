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
    NFA(std::string filename); // 构造函数，从文件中读取正规文法，生成NFA
    NFA(std::set<State*> startState, std::set<State*> finalState); // 构造函数，使用给定的起始状态和终止状态
    ~NFA(); // 销毁 NFA 对象
    void buildNFA(std::string filename); // 从文件中读取正规文法，生成NFA
    // 接受一个输入字符串，并模拟NFA对该输入字符串的处理过程，返回是否接受输入字符串。
    bool accept(std::string input);
    void addStartState(State* state); // 添加起始状态
    std::set<State*> getStartState() const; // 获取初始状态
};

#endif // NFA_H
