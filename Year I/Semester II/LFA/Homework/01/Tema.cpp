#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

typedef std::string str;
typedef std::map<std::pair<int, int>, bool> mpair;

int next_path(int a_q, std::map<int, int> a_states)
{
    for (const auto &i : a_states) 
    {
        if (i.second == a_q)
        {
            return i.first;
        }
    }
    return -1;
}

str upper(str a_str)
{
    for (size_t i = 0; i < a_str.size(); ++i)
    {
        a_str[i] = std::toupper(a_str[i]);
    }
    return a_str;
}

template<typename T>
T read(std::ifstream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

struct Automata
{
    size_t m_N{};
    std::map<int, int> m_states{};

    size_t m_M{};
    std::map<std::pair<int, char>, std::vector<int>> m_paths{};

    int m_S{};
    size_t m_nrF{};
    std::vector<bool> m_final_states{};

    std::vector<int> m_path{};

    friend std::ifstream& operator>>(std::ifstream& a_in, Automata& a_automata)
    {
        a_automata.m_N = read<size_t>(a_in);
        for (size_t i = 0; i < a_automata.m_N; ++i)
        {
            int temp{ read<int>(a_in) };
            a_automata.m_states.insert({ temp, (int)i });
        }

        a_automata.m_M = read<size_t>(a_in);
        for (size_t i = 0; i < a_automata.m_M; ++i)
        {
            int x{ read<int>(a_in) }, y{ read<int>(a_in) };
            char c{ read<char>(a_in) };
            a_automata.m_paths[{ a_automata.m_states[x], c }].push_back(a_automata.m_states[y]);
        }

        a_automata.m_S = read<int>(a_in);
        a_automata.m_S = a_automata.m_states[a_automata.m_S];

        a_automata.m_nrF = read<size_t>(a_in);
        a_automata.m_final_states.resize(a_automata.m_nrF);
        for (size_t i = 0; i < a_automata.m_N; ++i)
        {
            a_automata.m_final_states[i] = false;
        }
        for (size_t i = 0; i < a_automata.m_nrF; ++i)
        {
            int x{ read<int>(a_in) };
            a_automata.m_final_states[(size_t)a_automata.m_states[x]] = true;
        }

        return a_in;
    }

    bool dfa(int a_q, str a_word)
    {
        if (a_word.empty())
        {
            m_path.push_back(next_path(a_q, m_states));
            return m_final_states[(size_t)a_q];
        }
        else
        {
            auto it{ m_paths.find({ a_q, a_word[0] }) };

            if (it == m_paths.end())
            {
                return false;
            }
            else
            {
                m_path.push_back(next_path(a_q, m_states));
                return dfa(it->second[0], a_word.substr(1));
            }
        }
    }

    bool nfa(int a_q, str a_word, int a_step, mpair a_visited)
    {
        for (auto i : m_paths[{a_q, a_word[0]}])
        {
            if (!a_visited[{ i, a_step }])
            {
                a_visited[{ i, a_step }] = true;
                if (nfa(i, a_word.substr(1), a_step + 1, a_visited))
                {
                    m_path.push_back(next_path(a_q, m_states));
                    return true;
                }
            }
        }
        if (a_word.empty())
        {
            if (m_final_states[(size_t)a_q])
            {
                m_path.push_back(next_path(a_q, m_states));
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool lambda_nfa(int a_q, str a_word, int a_step, mpair a_visited)
    {
        for (auto i : m_paths[{a_q, a_word[0]}])
        {
            if (!a_visited[{ i, a_step }])
            {
                a_visited[{ i, a_step }] = true;
                if (lambda_nfa(i, a_word.substr(1), a_step + 1, a_visited))
                {
                    m_path.push_back(next_path(a_q, m_states));
                    return true;
                }
            }
        }
        for (auto i : m_paths[{a_q, 'L'}])
        {
            if (!a_visited[{ i, a_step }])
            {
                a_visited[{ i, a_step }] = true;
                if (lambda_nfa(i, a_word, a_step, a_visited))
                {
                    m_path.push_back(next_path(a_q, m_states));
                    return true;
                }
            }
        }
        if (a_word.empty())
        {
            if (m_final_states[(size_t)a_q])
            {
                m_path.push_back(next_path(a_q, m_states));
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }
};

void test_dfa(const str& a_number)
{
    std::ifstream in(("Input/DFA/input_dfa" + a_number + ".txt").c_str());
    std::ofstream out(("Output/DFA/output_dfa" + a_number + ".txt").c_str());

    Automata automata{};
    in >> automata;

    size_t nrCuv{ read<size_t>(in) };
    for (size_t i = 0; i < nrCuv; ++i)
    {
        automata.m_path.clear();
        str cuv{ read<str>(in) };
        out << cuv << " : ";
        if (automata.dfa(automata.m_S, cuv))
        {
            out << "DA\n";
            for (size_t j = 0; j < automata.m_path.size(); ++j)
            {
                out << automata.m_path[j] << ' ';
            }
            out << '\n';
        }
        else
        {
            out << "NU\n";
        }
    }
    in.close();
    out.close();
}


void test_nfa(const str& a_type, const char a_number, bool (Automata::*a_function)(int, str, int, mpair))
{
    const str upper_type{ upper(a_type) };
    std::ifstream in(("Input/" + upper_type + "/input_" + a_type + a_number + ".txt").c_str());
    std::ofstream out(("Output/" + upper_type + "/output_" + a_type + a_number + ".txt").c_str());

    Automata automata{};
    in >> automata;

    size_t nrCuv{ read<size_t>(in) };
    for (size_t i = 0; i < nrCuv; ++i)
    {
        automata.m_path.clear();
        str cuv{ read<str>(in) };
        int step{0};
        mpair visited{};
        out << cuv << " : ";
        if ((automata.*a_function)(automata.m_S, cuv, step, visited))
        {
            out << "DA\n";
            if (a_type == "nfa" || a_type == "lambda_nfa")
            {
                std::reverse(automata.m_path.begin(), automata.m_path.end());
            }
            for (size_t j = 0; j < automata.m_path.size(); ++j)
            {
                out << automata.m_path[j] << ' ';
            }
            out << '\n';
        }
        else
        {
            out << "NU\n";
        }
    }
    in.close();
    out.close();
}


int main()
{
    system("rmdir /s /q Output");
    system("mkdir Output");

    Automata A{};

    // Cerinta a)
    system("cd Output & mkdir DFA");
    test_dfa("1");
    test_dfa("2");
    test_dfa("3");
    test_dfa("4");

    // Cerinta b)
    system("cd Output & mkdir NFA");
    test_nfa("nfa", '1', A.nfa);
    test_nfa("nfa", '2', A.nfa);
    test_nfa("nfa", '3', A.nfa);
    test_nfa("nfa", '4', A.nfa);
    test_nfa("nfa", '5', A.nfa);

    // Cerinta c)
    system("cd Output & mkdir Lambda_NFA");
    test_nfa("lambda_nfa", '1', A.lambda_nfa);
    test_nfa("lambda_nfa", '2', A.lambda_nfa);

    return 0;
}
