#pragma once
#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

// 定义EPS常量
const char EPS = '\0';

// State 类声明
class State {
private:
    int id; // 状态ID
    bool isFinal; // 是否是终态
    std::unordered_map<char, std::set<State*>> transitions; // 字符到状态集合的转移映射
    static int stateCount; // 状态计数器
public:
    State(); // 默认构造函数
    explicit State(bool isFinal); // 带参数的构造函数
    // 添加转移
    void addTransition(char input, State* nextState);
    // 获取通过输入字符转移到的状态集合
    std::set<State*> getTransitions(char input);
    // 获取该状态经任一条EPS弧转移到的状态
    std::set<State*> getEpsTransition();
    // 获取该状态经任若干条EPS弧转移到的状态集合，即EPS闭包
    std::set<State*> getEpsTransitions();
    // 设置是否是终态
    void setFinalState(bool isFinal);
    bool isFinalState() const;
    int getStateId() const;
};

#endif // STATE_H
