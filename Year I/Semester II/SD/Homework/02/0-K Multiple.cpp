#include <algorithm>
#include <iostream>
#include <queue>

typedef std::pair<int, int> pair;

template<typename T>
T read_input()
{
    T temp{};
    std::cin >> temp;
    return temp;
}

int main()
{
    int n{ read_input<int>() };
    int k{ read_input<int>() };
    std::vector<pair> father((size_t)n, {-1, -1});
    std::queue<int> q{};
    q.push(k % n);
    father[(size_t)(k % n)] = {-1, k};
    bool found{ false };
    while (!found && !q.empty())
    {
        int node{ q.front() };
        q.pop();
        if (!node)
        {
            found = true;
        }
        else 
        {
            int next{ (node * 10) % n };
            if (father[(size_t)next].second == -1)
            {
                father[(size_t)next] = {node, 0};
                q.push(next);
            }
            next = (next + k) % n;
            if (father[(size_t)next].second == -1)
            {
                father[(size_t)next] = {node, k};
                q.push(next);
            }
        }
    }
    int aux{0};
    std::vector<int> sol{};
    while (aux != -1)
    {
        sol.push_back(father[(size_t)aux].second);
        aux = father[(size_t)aux].first;
    }
    std::reverse(sol.begin(), sol.end());
    for (const auto& i : sol)
    {
        std::cout << i;
    }
    return 0;
}

// https://csacademy.com/submission/4020708/
