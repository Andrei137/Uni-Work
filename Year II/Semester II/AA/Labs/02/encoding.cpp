#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

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

int get_l(int a_a, int a_b, int a_p)
{
    return static_cast<int>(std::ceil(std::log2((a_b - a_a) * std::pow(10, a_p))));
}

double get_d(int a_a, int a_b, int a_l)
{
    return 1.0 * (a_b - a_a) / (1 << a_l);
}

int main()
{
    IO();

    int a{ read<int>() };
    int b{ read<int>() };
    int p{ read<int>() };
    int l{ get_l(a, b, p) };
    double d{ get_d(a, b, l) };
    int m{ read<int>() };
    std::cout << std::fixed << std::setprecision(l);
    while (m--)
    {
        std::string query{ read<std::string>() };
        if (query == "TO")
        {
            double x{ read<double>() };
            int interval{ static_cast<int>((x - a) /  d) };
            std::vector<bool> bits;
            while (interval)
            {
                bits.push_back(interval & 1);
                interval >>= 1;
            }
            while (static_cast<int>(bits.size()) < l)
            {
                bits.push_back(0);
            }
            for (int i = static_cast<int>(bits.size()) - 1; i >= 0; --i)
            {
                std::cout << bits[i];
            }
        }
        else
        {
            std::string bits{ read<std::string>() };
            int number{ 0 };
            for (int i = 0; i < l; ++i)
            {
                number += (bits[i] - '0') * (1 << (l - i - 1));
            }
            std::cout << a + number * d;
        }
        std::cout << '\n';
    }
    return 0;
}