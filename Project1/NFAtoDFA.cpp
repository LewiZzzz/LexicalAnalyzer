#include "NFAtoDFA.h"
#include <queue>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

bool isEqual(const std::set<State*>& set1, const std::set<State*>& set2) {
    if (set1.size() != set2.size()) {
        return false;
    }
    return std::equal(set1.begin(), set1.end(), set2.begin());
}

std::set<State*> epsClosure(std::set<State*> startStates) {
    std::queue<State*> q;
    std::set<State*> closure = startStates;
    for (auto state : startStates) {
        q.push(state);
    }
    while (!q.empty()) {
        State* s = q.front();
        q.pop();
        set<State*> epsTransitions = s->getEpsTransitions();
        for (auto state : epsTransitions) {
            if (closure.find(state) == closure.end()) {
                closure.insert(state);
                q.push(state);
            }
        }
    }
    return closure;
}

DFA NFAtoDFA(NFA& nfa) {
    // 初始化
    std::vector<std::set<State*>> s;
    std::vector<State*> dfa_states;
    int idx_dfa_state = 0;

    // 计算起始状态的Eps闭包并加入s向量
    s.push_back(epsClosure({ nfa.getStartState() }));

    // 创建起始状态并加入dfa_states向量和DFA对象
    State* st = new State();
    dfa_states.push_back(st);
    DFA dfa(st, nfa.getAlphaBet());

    // 遍历dfa_states向量
    while (idx_dfa_state < dfa_states.size()) {
        // 获取当前状态集合
        std::set<State*> t = s[idx_dfa_state];

        // 对于NFA的每个字母
        for (auto c : nfa.getAlphaBet()) {
            // 计算新状态集合的Eps闭包
            std::set<State*> new_t = epsClosure(nfa.move(t, c));
            bool flag = false;
            int existing_index = -1;

            // 检查new_t是否已存在
            for (int i = 0; i < s.size(); i++) {
                if (isEqual(s[i], new_t)) {
                    flag = true;
                    existing_index = i;
                    break;
                }
            }

            if (!flag) {
                // 创建新状态并检查是否为终止状态
                bool is_final = std::any_of(new_t.begin(), new_t.end(), [](State* state) { return state->isFinalState(); });
                State* state = new State(is_final);
                dfa.addState(state);
                dfa_states.push_back(state);
                s.push_back(new_t);
                dfa.addTransition(c, dfa_states[idx_dfa_state], state);
                if (is_final) {
                    dfa.addFinalState(state);
                }
            }
            else {
                // 添加状态转换
                dfa.addTransition(c, dfa_states[idx_dfa_state], dfa_states[existing_index]);
            }
        }
        idx_dfa_state++;
    }

    // 返回构建好的DFA
    return dfa;
}


