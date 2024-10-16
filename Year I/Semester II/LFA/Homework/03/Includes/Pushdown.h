#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <vector>

using str = std::string;
using graph = std::map<int, std::map<char, std::map<char, std::pair<int, str>>>>;
using config = std::map<int, std::map<char, std::map<char, std::map<int, bool>>>>;

class Pushdown
{
    size_t m_nr_states{};
    std::map<int, int> m_states{};

    size_t m_nr_paths{};
    graph m_paths{};
    std::map<int, std::set<std::pair<char, char>>> m_possible{};

    int m_initial_state{};
    size_t m_nr_final_states{};
    std::map<int, bool> m_final_states{};

    config m_visited{};
    std::stack<char> m_stack{};

    std::vector<int> m_path{};

    size_t m_nr_words{};
    std::vector<str> m_words{};

    int next_path(int a_q);
    bool pushdown(int, int, str);

public:
    Pushdown();
    ~Pushdown() = default;

    friend std::istream& operator>>(std::istream&, Pushdown&);
    friend std::ostream& operator<<(std::ostream&, Pushdown&);
};