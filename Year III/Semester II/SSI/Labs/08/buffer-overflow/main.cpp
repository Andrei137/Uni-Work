#include <iostream>
#include <cstring>

int main()
{
    char pass[7] = "fmiSSI";
    char input[7];
    int passLen = strlen(pass);
    std::cout << "Introduceti parola: ";
    std::cin >> input;
    std::cout << input << '\n' << pass << '\n' << passLen << '\n';
    if (strncmp(input, pass, passLen) == 0) {
        std::cout << "Parola introdusa este corecta!\n";
    }
    else {
        std::cout << "Ati introdus o parola gresita :(\n";
    }
    return 0;
}
