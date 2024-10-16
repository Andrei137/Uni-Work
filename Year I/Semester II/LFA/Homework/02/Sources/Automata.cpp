#include "../Includes/Automata.h"
#include <numeric>

template<typename T>
T read(std::istream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

Automata::Automata(const std::set<char>& a_alphabet, const std::map<str, std::map<char, std::vector<str>>>& a_paths, const std::set<str>& a_states, const str& a_initial_state, const std::map<str, bool>& a_final_states) 
    : m_alphabet(a_alphabet), m_paths(a_paths), m_states(a_states), m_initial_state(a_initial_state), m_final_states(a_final_states)
{
    m_nr_states = m_states.size();
    m_nr_final_states = a_final_states.size();
    m_nr_paths = a_paths.size();
}

str Automata::to_string(std::set<str> a_states)
{
    // set de stringuri -> string
    return std::accumulate(a_states.begin(), a_states.end(), str{},
                           [](const str& acc, const str& s) { return acc + s; });
}

std::istream& operator>>(std::istream& a_in, Automata& a_A)
{
    // citire stari
    a_in >> a_A.m_nr_states;
    for (size_t i = 0; i < a_A.m_nr_states; ++i)
    {
        a_A.m_states.insert(read<str>(a_in));
    }

    // citire muchii
    a_in >> a_A.m_nr_paths;
    for (size_t i = 0; i < a_A.m_nr_paths; ++i)
    {
        str current_state{ read<str>(a_in) }, next_state{ read<str>(a_in) };
        char letter{ read<char>(a_in) };
        a_A.m_paths[current_state][letter].push_back(next_state);
        a_A.m_alphabet.insert(letter);
    }

    // citire stare initiala
    a_in >> a_A.m_initial_state;

    // citire stari finale
    a_in >> a_A.m_nr_final_states;
    for (size_t i = 0; i < a_A.m_nr_final_states; ++i)
    {
        str final_state{ read<str>(a_in) };
        a_A.m_final_states[final_state] = true;
    }
    return a_in;
}