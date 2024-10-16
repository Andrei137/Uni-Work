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

void mutation(std::string& a_chromosome, const std::vector<int>& a_positions)
{
    for (int position : a_positions)
    {
        a_chromosome[position] ^= 1;
    }
}

int main()
{
    IO();

    [[maybe_unused]] int l{ read<int>() };
    int k{ read<int>() };
    std::string chromosome{ read<std::string>() };

    std::vector<int> positions(k);
    for (int& position : positions)
    {
        position = read<int>();
    }

    mutation(chromosome, positions);

    std::cout << chromosome;

    return 0;
}