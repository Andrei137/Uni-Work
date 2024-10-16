#pragma once

#include "Automata.h"

class DFA : public Automata
{
private:
    bool same_set(const str&, const str&, const std::set<std::set<str>>&);
    std::set<std::set<str>> get_states_sets(std::ostream&);

public:
    DFA() = default;
    explicit DFA(const Automata&);
    friend std::ostream& operator <<(std::ostream&, const DFA&);
    DFA minimize(std::ostream&);
};