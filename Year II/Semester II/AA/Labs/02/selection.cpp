#include <iostream>
#include <iomanip>
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

double fitness(double a_x, int a_a, int a_b, int a_c)
{
    return a_a * a_x * a_x + a_b * a_x + a_c; 
}

int main()
{
    IO();

    int a{ read<int>() };
    int b{ read<int>() };
    int c{ read<int>() };

    int n{ read<int>() };
    std::vector<double> v(n);
    std::vector<double> sp(n + 1);

    for (int i = 0; i < n; ++i)
    {
        v[i] = read<double>();
        sp[i + 1] = sp[i] + fitness(v[i], a, b, c);
    }

    std::cout << std::fixed;
    for (int i = 0; i <= n; ++i)
    {
        std::cout << sp[i] / sp[n] << '\n';
    }
    return 0;
}
