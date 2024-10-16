#include <algorithm>
#include <fstream>
#include <queue>

typedef std::pair<int, int> pair;

template<typename T>
T read_input(std::ifstream& in)
{
    T temp{};
    in >> temp;
    return temp;
}

int main()
{
    std::ifstream in("cifre4.in");
    std::ofstream out("cifre4.out");
    int t{ read_input<int>(in) };
    while (t--)
    {
        const int k[] = { 2, 3, 5, 7 };
        int n{ read_input<int>(in) };
        int p{ read_input<int>(in) };
        std::vector<pair> father((size_t)p, {-1, -1});
        std::queue<int> q{};
        q.push(2 % p);
        father[(size_t)(2 % p)] = {-1, 2};
        q.push(3 % p);
        father[(size_t)(3 % p)] = {-1, 3};
        q.push(5 % p);
        father[(size_t)(5 % p)] = {-1, 5};
        q.push(7 % p);
        father[(size_t)(7 % p)] = {-1, 7};
        bool found{ false };
        while (!found && !q.empty())
        {
            int node{ q.front() };
            q.pop();
            if (node == n)
            {
                found = true;
            }
            else 
            {
                for (int i = 0; i < 4; ++i)
                {
                    int next{ (node * 10 + k[i]) % p };
                    if (father[(size_t)next].second == -1)
                    {
                        father[(size_t)next] = {node, k[i]};
                        q.push(next);
                    }
                }
            }
        }
        if (q.empty())
        {
            out << -1;
        }
        else
        {
            int aux{n};
            std::vector<int> sol{};
            while (aux != -1)
            {
                sol.push_back(father[(size_t)aux].second);
                aux = father[(size_t)aux].first;
            }
            std::reverse(sol.begin(), sol.end());
            for (const auto& i : sol)
            {
                out << i;
            }
        }
        out << '\n';
    }
    in.close();
    out.close();
    return 0;
}