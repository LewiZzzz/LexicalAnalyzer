#pragma once
#include "NFA.h"
#include "DFA.h"

DFA NFAtoDFA(NFA& nfa);
DFA minimizeDFA(DFA dfa);