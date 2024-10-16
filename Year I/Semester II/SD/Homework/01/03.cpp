#include <iostream>

template<typename T>
T read()
{
    T x;
    std::cin >> x;
    return x;
}

void open_IO(std::string a_s)
{
    freopen((a_s + ".in").c_str(), "r", stdin);
    freopen((a_s + ".out").c_str(), "w", stdout);
}

int smen[1050][1050];

int main()
{
    open_IO("geamuri");
    int c = read<int>();
    size_t n = read<size_t>();
    for (size_t i = 0; i < n; i++)
    {
        int x0, y0, x1, y1;
        std::cin >> x0 >> y0 >> x1 >> y1;
        ++smen[x0][y0];
        --smen[x0][y1 + 1];
        --smen[x1 + 1][y0];
        ++smen[x1 + 1][y1 + 1];
    }

    int answer[50005] = {0};
    for(int i = 1; i <= c; ++i)
    {
        for (int j = 1; j <= c; ++j)
        {
            smen[i][j] += smen[i - 1][j] + smen[i][j - 1] - smen[i - 1][j - 1];
            ++answer[smen[i][j]];
        }
    }

    int m = read<int>();
    while (m--)
    {
        int x = read<int>();
        std::cout << answer[x] << "\n";
    }

    return 0;
}