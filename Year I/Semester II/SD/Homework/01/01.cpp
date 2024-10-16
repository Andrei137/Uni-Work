#include <iostream>

int main()
{
    size_t n;
    int a[1001], aux[1001] = {1};
    std::cin >> n >> a[1];
    for (size_t i = 2; i <= n; ++i)
    {
        std::cin >> a[i];
        if (a[i] > a[i - 1])
        {
            aux[i] = aux[i - 1] + 1;
        }
        else
        {
            aux[i] = 1;
        }
    }
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        if (aux[r] - aux[l] >= r - l)
        {
            std::cout << "YES" << '\n';
        }
        else
        {
            std::cout << "NO" << '\n';
        }
    }
    return 0;
}