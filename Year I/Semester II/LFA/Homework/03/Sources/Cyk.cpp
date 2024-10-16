#include "../Includes/Cyk.h"

template<typename T>
T read(std::istream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

std::istream& operator>>(std::istream& a_in, Cyk& a_cyk)
{
    a_cyk.m_non_terminals.push_back('-');
    a_cyk.m_nr_non_terminals = read<size_t>(a_in);
    for (size_t i = 0; i < a_cyk.m_nr_non_terminals; ++i)
    {
        char non_terminal{ read<char>(a_in) };
        a_cyk.m_non_terminals.push_back(non_terminal);
        a_cyk.m_non_terminals_index[non_terminal] = i + 1;
    }
    
    a_cyk.m_nr_rules = read<size_t>(a_in);
    for (size_t i = 0; i < a_cyk.m_nr_rules; ++i)
    {
        char non_terminal{ read<char>(a_in) };
        str rule{ read<str>(a_in) };
        a_cyk.m_rules[non_terminal].push_back(rule);
    }

    a_cyk.m_nr_words = read<size_t>(a_in);
    for (size_t i = 0; i < a_cyk.m_nr_words; ++i)
    {
        str word{ read<str>(a_in) };
        a_cyk.m_words.push_back(word);
    }
    return a_in;
}

bool Cyk::check_word(str& a_word)
{
    std::map<int, std::map<int, std::map<int, bool>>> table{};
    int word_size{ (int)a_word.size() };
    a_word = '-' + a_word;
    for (int s = 1; s <= word_size; ++s)
    {
        for (int v = 1; v <= (int)m_nr_non_terminals; ++v)
        {
            for (int i = 0; i < (int)m_rules[m_non_terminals[v]].size(); ++i)
            {
                if (m_rules[m_non_terminals[v]][i][0] == a_word[s])
                {
                    table[1][s][v] = true;
                }
            }
        }
    }
    for (int l = 2; l <= word_size; ++l)
    {   
        for (int s = 1; s <= word_size - l + 1; ++s)
        {
            for (int p = 1; p <= l - 1; ++p)
            {
                for (int a = 1; a <= (int)m_nr_non_terminals; ++a)
                {
                    for (int i = 0; i < (int)m_rules[m_non_terminals[a]].size(); ++i)
                    {
                        if (m_rules[m_non_terminals[a]][i].size() != 2)
                        {
                            continue;
                        }
                        int b{ m_non_terminals_index[m_rules[m_non_terminals[a]][i][0]] };
                        int c{ m_non_terminals_index[m_rules[m_non_terminals[a]][i][1]] };
                        if (table[p][s][b] && table[l - p][s + p][c])
                        {
                            table[l][s][a] = true;
                        }
                    }
                }
            }
        }
    }
    return table[word_size][1][1];
}

std::ostream& operator<<(std::ostream& a_out, Cyk& a_cyk)
{
    for (auto& word : a_cyk.m_words)
    {
        a_out << (a_cyk.check_word(word) ? "DA" : "NU") << '\n';
    }
    return a_out;
}
