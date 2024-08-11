#pragma once
#ifndef FA_H
#define FA_H

#include <set>
#include "State.h" 

class FA {
protected:
    std::set<State*> finalState; // 终止状态集合
    std::set<State*> state; // 状态集合
    std::set<char> alphabet; // 字母表

public:
    FA(); // 构造函数
    ~FA(); // 析构函数
    void addState(State* state); // 添加状态
    void addFinalState(State* state); // 添加终止状态
    void addAlphabet(char input); // 添加字母表
    void addTransition(char input, State* fromState, State* toState); // 添加转移
    std::set<char> getAlphaBet(); // 获取字母表
    // 状态的 a 弧转换: 是状态 S 经输入字符 a 而能到达的状态的集合。
    std::set<State*> move(State* state, char c);
    // 状态集合 I 的 a 弧转换: 是状态集 I 中的任何状态 S 经输入字符 a 而能到达的状态的集合。
    std::set<State*> move(std::set<State*> states, char c);
    std::set<State*> getFinalState() const; // 获取终止状态
    std::set<State*> getState() const; // 获取状态集合
};

#endif // FA_H
