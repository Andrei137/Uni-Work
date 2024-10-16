#include <algorithm>
#include <iostream>
#include <vector>

struct Interval
{
    int x, y;
};

int main()
{
    size_t n;
    std::cin >> n;
    std::vector<Interval> I;
    I.resize(n);
    std::vector<int> M(1e6, 0);
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> I[i].x >> I[i].y;
        M[size_t(I[i].x)] = 1ULL;
        M[size_t(I[i].y) + 1] = -1;
    }
    size_t q;
    std::cin >> q;
    std::vector<int> t;
    t.resize(q);
    for (size_t i = 0; i < q; ++i)
    {
        std::cin >> t[i];
    }
    std::vector<int> smen(1e6);
    smen[0] = M[0];
    for (size_t i = 1; i < 1e6; ++i)
    {
        smen[i] = smen[i - 1] + M[i];
    }
    for (size_t i = 0; i < q; ++i)
    {
        std::cout << smen[size_t(t[i])] << '\n';
    }
    return 0;
}