#include "Includes/NFA.h"
#include "Includes/DFA.h"

int main()
{
    std::ifstream in_1("Txt Files/input_nfa.in");
    std::ofstream out_1("Txt Files/output_nfa.out");
    NFA nfa{};
    in_1 >> nfa;
    DFA dfa{ nfa.transform_to_DFA() };
    out_1 << dfa;

    std::ifstream in_2("Txt Files/input_dfa1.in");
    std::ofstream out_2("Txt Files/output_df1.out");
    DFA dfa_2{};
    in_2 >> dfa_2;
    DFA min_dfa{ dfa_2.minimize(out_2) };
    out_2 << min_dfa;


    std::ifstream in_3("Txt Files/input_dfa2.in");
    std::ofstream out_3("Txt Files/output_df2.out");
    DFA dfa_3{};
    in_3 >> dfa_3;
    DFA min_dfa_3{ dfa_3.minimize(out_3) };
    out_3 << min_dfa_3;

    return 0;
}