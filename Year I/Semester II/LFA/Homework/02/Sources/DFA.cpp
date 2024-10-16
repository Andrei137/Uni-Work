#include "../Includes/DFA.h"

DFA::DFA(const Automata& a_A) : Automata(a_A) {};

bool DFA::same_set(const str& a_first_state, const str& a_second_state, const std::set<std::set<str>>& a_states_sets)
{
    for (std::set<str> states_set : a_states_sets)
    {
        if (states_set.find(a_first_state) != states_set.end() && states_set.find(a_second_state) != states_set.end())
        {
            return true;
        }
    }
    return false;
}

std::set<std::set<str>> DFA::get_states_sets(std::ostream& a_out)
{
    // eliminam nodurile la care nu putem ajunge
    std::set<str> accessible_states{};
    std::queue<str> states{};

    // incepem cu starea initiala,
    // care evident este accesibila
    states.push(m_initial_state);
    accessible_states.insert(m_initial_state);

    // cat timp mai avem stari de vizitat
    while (!states.empty())
    {
        str state = states.front();
        states.pop();

        for (char letter : m_alphabet)
        {
            str new_state = m_paths.at(state).at(letter)[0];

            // daca nu am vizitat starea curenta,
            // o vizitam si o adaugam in coada
            if (accessible_states.find(new_state) == accessible_states.end())
            {
                states.push(new_state);
                accessible_states.insert(new_state);
            }
        }
    }

    // impartim starile accesibile 
    // in 2 multimi initiale : finale si nefinale
    std::set<std::set<str>> states_sets{};

    std::set<str> final_states{};
    std::set<str> non_final_states{};
    for (str state : accessible_states)
    {
        if (m_final_states.find(state) != m_final_states.end())
        {
            final_states.insert(state);
        }
        else
        {
            non_final_states.insert(state);
        }
    }
    states_sets.insert(final_states);
    states_sets.insert(non_final_states);

    // Cat timp apar modificari
    do
    {
        std::set<std::set<str>> new_states_sets{};
        for (auto states_set : states_sets)
        {
            str first_state{};
            for (const str& temp_state : states_set) 
            {
                first_state = temp_state;
                break;
            }
            std::set<str> new_set1{}, new_set2{};
            for (str second_state : states_set)
            {
                bool ok{ true };
                // pentru fiecare litera din alfabet, verificam daca
                // tranzitiile celor doua stari duc in aceeasi multime
                for (char letter : m_alphabet)
                {
                    if (ok)
                    {
                        str next_first_state{ m_paths.at(first_state).at(letter)[0] };
                        str next_second_state{ m_paths.at(second_state).at(letter)[0] };
                        ok = same_set(next_first_state, next_second_state, states_sets);
                    }
                }
                if (ok)
                {
                    // ambele stari fac parte din aceeasi multime
                    new_set1.insert(first_state);
                    new_set1.insert(second_state);
                }
                else
                {
                    // cele doua stari nu fac parte din aceeasi multime
                    new_set1.insert(first_state);
                    new_set2.insert(second_state);
                }
            }
            if (!new_set1.empty())
            {
                new_states_sets.insert(new_set1);
            }
            if (!new_set2.empty())
            {
                new_states_sets.insert(new_set2);
            }
        }
        // daca nu s-au produs modificari
        // atunci iesim din while
        if (new_states_sets == states_sets)
        {
            break;
        }
        states_sets = new_states_sets;
    } while (true);

    int index{ 0 };
    for (std::set<str> states_set : states_sets)
    {
        a_out << "Multime " << ++index << " : ";
        for (str state : states_set)
        {
            a_out << state;
        }
        a_out << '\n';
    }
    a_out << "\n\n";
    return states_sets;
}

DFA DFA::minimize(std::ostream& a_out)
{
    std::set<std::set<str>> states_sets{ get_states_sets(a_out) };

    // Componentele grafului minimizat
    graph paths_MinDFA{};
    std::set<str> states_MinDFA{};
    str initial_state_MinDFA{};
    std::map<str, bool> final_states_MinDFA{};
    for (std::set<str> states_set : states_sets)
    {
        str state{ to_string(states_set) };
        for (char letter : m_alphabet)
        {
            str new_state{};
            for (const str& temp_state : states_set) 
            {
                new_state = temp_state;
                break;
            }
            
            // cautam in ce multime se afla starea in care ajungem
            str new_next_state{ m_paths.at(new_state).at(letter).back() };
            for (std::set<str> s : states_sets)
            {
                bool found{ std::any_of(s.begin(), s.end(), [&](const str& ss){ return ss == new_next_state; }) };
                if (found)
                {
                    paths_MinDFA[state][letter].push_back(to_string(s));
                    break;
                }
            }
        }

        // adaugare noua stare
        states_MinDFA.insert(state);

        // verificare daca nodul este
        // initial sau final
        for (str temp_state : states_set)
        {
            if (m_initial_state == temp_state)
            {
                initial_state_MinDFA = state;
                break;
            }
            if (m_final_states[temp_state])
            {
                final_states_MinDFA[state] = true;
                break;
            }
        }
    }
    Automata temp(m_alphabet, paths_MinDFA, states_MinDFA, initial_state_MinDFA, final_states_MinDFA);
    return DFA(temp);
}

std::ostream& operator <<(std::ostream& a_out, const DFA& a_DFA)
{
    std::map<str, bool> visited{};
    std::queue<str> states{};

    // plecam din starea initiala si o vizitam
    states.push(a_DFA.m_initial_state);
    visited[a_DFA.m_initial_state] = true;
    while (!states.empty())
    {
        str state = states.front();
        states.pop();
        for (char letter : a_DFA.m_alphabet)
        {
            str new_state = a_DFA.m_paths.at(state).at(letter)[0];
            a_out << "Graph[" << state << "][" << letter << "] = " << new_state << '\n';

            // dacă nu am vizitat starea curenta,
            // o vizităm și o adăugăm în coada
            if (!visited[new_state])
            {
                visited[new_state] = true;
                states.push(new_state);
            }
        }
        a_out << '\n';
    }
    return a_out;
}