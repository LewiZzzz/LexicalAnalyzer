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
    // ��ʼ��
    std::vector<std::set<State*>> s;
    std::vector<State*> dfa_states;
    int idx_dfa_state = 0;

    // ������ʼ״̬��Eps�հ�������s����
    s.push_back(epsClosure({ nfa.getStartState() }));

    // ������ʼ״̬������dfa_states������DFA����
    State* st = new State();
    dfa_states.push_back(st);
    DFA dfa(st, nfa.getAlphaBet());

    // ����dfa_states����
    while (idx_dfa_state < dfa_states.size()) {
        // ��ȡ��ǰ״̬����
        std::set<State*> t = s[idx_dfa_state];

        // ����NFA��ÿ����ĸ
        for (auto c : nfa.getAlphaBet()) {
            // ������״̬���ϵ�Eps�հ�
            std::set<State*> new_t = epsClosure(nfa.move(t, c));
            bool flag = false;
            int existing_index = -1;

            // ���new_t�Ƿ��Ѵ���
            for (int i = 0; i < s.size(); i++) {
                if (isEqual(s[i], new_t)) {
                    flag = true;
                    existing_index = i;
                    break;
                }
            }

            if (!flag) {
                // ������״̬������Ƿ�Ϊ��ֹ״̬
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
                // ���״̬ת��
                dfa.addTransition(c, dfa_states[idx_dfa_state], dfa_states[existing_index]);
            }
        }
        idx_dfa_state++;
    }

    // ���ع����õ�DFA
    return dfa;
}


