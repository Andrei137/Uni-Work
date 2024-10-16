#include "../Includes/NFA.h"

DFA NFA::transform_to_DFA()
{
    // noile componente DFA
    // starea initiala si alfabetul raman aceleasi
    graph paths_DFA{};
    std::set<str> states_DFA{};
    std::map<str, bool> final_states_DFA{};

    std::set<std::set<str>> visited{};
    std::queue<std::set<str>> new_nodes{};

    // incepem cu starea initiala
    std::set<str> beginning{};
    beginning.insert(m_initial_state);
    new_nodes.push(beginning);

    // cat timp apar stari noi
    while (!new_nodes.empty())
    {
        std::set<str> current_node = new_nodes.front();
        new_nodes.pop();

        // daca am mai vizitat nodul curent
        // sarim peste el
        if (visited.find(current_node) != visited.end())
        {
            continue;
        }
        visited.insert(current_node);
        new_nodes.push(current_node);

        // daca exista nod final in nodul curent
        // devine si el final
        if (std::any_of(current_node.begin(), current_node.end(), [&](const auto& state){ return m_final_states[state]; }))
        {
            final_states_DFA[to_string(current_node)] = true;
        }
        for (char letter : m_alphabet)
        {
            std::set<str> next_states{};

            // pentru fiecare nod din nodul curent
            // adaugam toate nodurile in care putem ajunge
            for (str node : current_node)
            {
                for (str next_state : m_paths[node][letter])
                {
                    next_states.insert(next_state);
                }
            }
            new_nodes.push(next_states);
            // daca exista muchie, o adaugam in DFA
            if (!next_states.empty())
            {
                paths_DFA[to_string(current_node)][letter].push_back(to_string(next_states));
            }
        }
    }
    Automata temp{m_alphabet, paths_DFA, states_DFA, m_initial_state, final_states_DFA};
    return DFA(temp);
}