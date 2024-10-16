#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using str = std::string;
using graph = std::map<str, std::map<char, std::vector<str>>>;

class Automata
{
protected:
    std::set<char> m_alphabet{};

    size_t m_nr_paths{};
    graph m_paths{};

    size_t m_nr_states{};
    std::set<str> m_states{};

    str m_initial_state{};
    size_t m_nr_final_states{};
    std::map<str, bool> m_final_states{};

    str to_string(std::set<str>);

public:
    Automata() = default;
    explicit Automata(const std::set<char>&, const graph&,  const std::set<str>&, const str&, const std::map<str, bool>&);
    friend std::istream& operator >>(std::istream&, Automata&);
};