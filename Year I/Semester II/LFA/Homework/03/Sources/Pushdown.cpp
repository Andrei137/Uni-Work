#include "../Includes/Pushdown.h"

template<typename T>
T read(std::istream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

Pushdown::Pushdown()
{
    m_stack.push('Z');
}

std::istream& operator>>(std::istream& a_in, Pushdown& a_automata)
{
    a_automata.m_nr_states = read<size_t>(a_in);
    for (size_t i = 0; i < a_automata.m_nr_states; ++i)
    {
        int temp{ read<int>(a_in) };
        a_automata.m_states.insert({ temp, (int)i });
    }

    a_automata.m_nr_paths = read<size_t>(a_in);
    for (size_t i = 0; i < a_automata.m_nr_paths; ++i)
    {
        int x{ read<int>(a_in) }, y{ read<int>(a_in) };
        char c{ read<char>(a_in) }, z{ read<char>(a_in) };
        str s{ read<str>(a_in) };
        a_automata.m_paths[a_automata.m_states[x]][c][z] = { a_automata.m_states[y], s };
        a_automata.m_possible[a_automata.m_states[x]].insert({c, z});
    }

    a_automata.m_initial_state = read<int>(a_in);
    a_automata.m_initial_state = a_automata.m_states[a_automata.m_initial_state];

    a_automata.m_nr_final_states = read<size_t>(a_in);
    for (size_t i = 0; i < a_automata.m_nr_final_states; ++i)
    {
        int x{ read<int>(a_in) };
        a_automata.m_final_states[(size_t)a_automata.m_states[x]] = true;
    }

    a_automata.m_nr_words = read<size_t>(a_in);
    for (size_t i = 0; i < a_automata.m_nr_words; ++i)
    {
        str s{ read<str>(a_in) };
        a_automata.m_words.push_back(s);
    }

    return a_in;
}

int Pushdown::next_path(int a_q)
{
    for (const auto &i : m_states) 
    {
        if (i.second == a_q)
        {
            return i.first;
        }
    }
    return -1;
}

bool Pushdown::pushdown(int a_q, int a_step, str a_word)
{
    if (m_stack.empty())
    {
        return (a_word.empty());
    }
    if (m_possible[a_q].count({a_word[0], m_stack.top()}))
    {
        if (!m_visited[a_q][a_word[0]][m_stack.top()][a_step])
        {
            m_visited[a_q][a_word[0]][m_stack.top()][a_step] = true;
            char temp{ m_stack.top() };
            m_stack.pop();
            for (size_t i = m_paths[a_q][a_word[0]][temp].second.size(); i > 0; --i)
            {
                if (m_paths[a_q][a_word[0]][temp].second[i - 1] != 'e')
                {
                    m_stack.push(m_paths[a_q][a_word[0]][temp].second[i - 1]);
                }
            }
            if (pushdown(m_paths[a_q][a_word[0]][temp].first, a_step + 1, a_word.substr(1)))
            {
                m_path.push_back(next_path(a_q));
                return true;
            }
            for (auto ch : m_paths[a_q][a_word[0]][temp].second)
            {
                if (ch != 'e')
                {
                    m_stack.pop();
                }
            }
            m_stack.push(temp);
        }
    }
    if (m_possible[a_q].count({'L', m_stack.top()}))
    {
        if (!m_visited[a_q]['L'][m_stack.top()][a_step])
        {
            m_visited[a_q]['L'][m_stack.top()][a_step] = true;
            char temp{ m_stack.top() };
            m_stack.pop();
            for (size_t i = m_paths[a_q]['L'][temp].second.size(); i > 0; --i)
            {
                if (m_paths[a_q]['L'][temp].second[i - 1] != 'e')
                {
                    m_stack.push(m_paths[a_q]['L'][temp].second[i - 1]);
                }
            }
            if (pushdown(m_paths[a_q]['L'][temp].first, a_step, a_word))
            {
                m_path.push_back(next_path(a_q));
                return true;
            }
            for (auto ch : m_paths[a_q]['L'][temp].second)
            {
                if (ch != 'e')
                {
                    m_stack.pop();
                }
            }
            m_stack.push(temp);
        }
    }
    if (a_word.empty())
    {
        if (m_final_states[a_q] || m_stack.empty())
        {
            m_path.push_back(next_path(a_q));
            return true;
        }
        return false;
    }
    return false;
}

std::ostream& operator<<(std::ostream& a_out, Pushdown& a_automata)
{
    for (str s : a_automata.m_words)
    {
        if (a_automata.pushdown(a_automata.m_initial_state, 0, s))
        {
            a_out << "DA\n";
            std::reverse(a_automata.m_path.begin(), a_automata.m_path.end());
            for (auto i : a_automata.m_path)
            {
                a_out << i << ' ';
            }
        }
        else
        {
            a_out << "NU";
        }
        while (!a_automata.m_stack.empty())
        {
            a_automata.m_stack.pop();
        }
        a_automata.m_stack.push('Z');
        a_automata.m_path.clear();
        a_automata.m_visited.clear();
        a_out << '\n';
    }
    return a_out;
}