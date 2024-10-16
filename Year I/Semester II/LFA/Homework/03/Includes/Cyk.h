#pragma once

#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using str = std::string;

class Cyk
{
    size_t m_nr_non_terminals{};
    std::vector<char> m_non_terminals{};
    std::unordered_map<char, int> m_non_terminals_index{};

    size_t m_nr_rules{};
    std::unordered_map<char, std::vector<str>> m_rules{};

    size_t m_nr_words{};
    std::vector<str> m_words{};

    bool check_word(str&);

public:
    Cyk() = default;
    ~Cyk() = default;

    friend std::istream& operator>>(std::istream&, Cyk&);
    friend std::ostream& operator<<(std::ostream&, Cyk&);
};