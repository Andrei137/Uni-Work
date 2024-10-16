#include "Includes/Cyk.h"
#include "Includes/Pushdown.h"

int main()
{
    // Ex 1

    std::ifstream in_cyk("Txt Files/test_cyk.in");
    std::ofstream out_cyk("Txt Files/test_cyk.out");

    Cyk cyk{};
    in_cyk >> cyk;
    out_cyk << cyk;

    in_cyk.close();
    out_cyk.close();


    // Ex 2

    std::ifstream in_pda("Txt Files/test_pda.in");
    std::ofstream out_pda("Txt Files/test_pda.out");

    Pushdown automata{};
    in_pda >> automata;
    out_pda << automata;

    in_pda.close();
    out_pda.close();

    return 0;

}