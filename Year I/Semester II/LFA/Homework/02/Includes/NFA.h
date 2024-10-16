#pragma once

#include "DFA.h"

class NFA : public Automata
{
public:
    NFA() = default;
    DFA transform_to_DFA(); 
};