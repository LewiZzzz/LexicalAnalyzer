#pragma once
#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

// ����EPS����
const char EPS = '\0';

// State ������
class State {
private:
    int id; // ״̬ID
    bool isFinal; // �Ƿ�����̬
    std::unordered_map<char, std::set<State*>> transitions; // �ַ���״̬���ϵ�ת��ӳ��
    static int stateCount; // ״̬������
public:
    State(); // Ĭ�Ϲ��캯��
    explicit State(bool isFinal); // �������Ĺ��캯��
    // ���ת��
    void addTransition(char input, State* nextState);
    // ��ȡͨ�������ַ�ת�Ƶ���״̬����
    std::set<State*> getTransitions(char input);
    // ��ȡ��״̬����һ��EPS��ת�Ƶ���״̬
    std::set<State*> getEpsTransition();
    // ��ȡ��״̬����������EPS��ת�Ƶ���״̬���ϣ���EPS�հ�
    std::set<State*> getEpsTransitions();
    // �����Ƿ�����̬
    void setFinalState(bool isFinal);
    bool isFinalState() const;
    int getStateId() const;
};

#endif // STATE_H
