#include <iostream>
#include <vector>

void IO(bool a_fstream = 0, const std::string& a_s = "")
{
    std::cin.tie(0)->sync_with_stdio(0);
    if (a_fstream)
    {
        freopen((a_s + ".in").c_str(), "r", stdin);
        freopen((a_s + ".out").c_str(), "w", stdout);
    }
}

template <typename T>
T read()
{
    T temp{};
    std::cin >> temp;
    return temp;
}

void crossover(std::string& a_chromosome1, std::string& a_chromosome2, int a_l, int a_i)
{
    for (int i = a_i; i < a_l; ++i)
    {
        std::swap(a_chromosome1[i], a_chromosome2[i]);
    }
}

int main()
{
    IO();

    int l{ read<int>() };
    std::string chromosome1{ read<std::string>() };
    std::string chromosome2{ read<std::string>() };
    int i{ read<int>() };

    crossover(chromosome1, chromosome2, l, i);
    std::cout << chromosome1 << '\n' << chromosome2;

    return 0;
}