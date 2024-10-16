#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

void IO(const std::string& s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

class Graph
{
private:
    std::vector<std::vector<int>> m_adj{};

public:
    Graph() : m_adj(105) {};

    void add_edge(int a_v, int a_w)
    {
        m_adj[a_v].push_back(a_w);
        m_adj[a_w].push_back(a_v);
    }

    void sort(int a_n)
    {
        for (int i = 0; i < a_n; ++i)
        {
            std::sort(m_adj[i].begin(), m_adj[i].end());
        }
    }

    void dfs(int a_v, std::bitset<105>& a_visited)
    {
        a_visited[a_v] = true;
        for (int v : m_adj[a_v])
        {
            if (!a_visited[v])
            {
                dfs(v, a_visited);
            }
        }
    }
};

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);
    IO("dfs");

}