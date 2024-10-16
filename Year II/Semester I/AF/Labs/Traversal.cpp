#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset> 
#include <queue>

void IO(const std::string& s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

class Graph
{
   std::bitset<105> m_visited{};
   std::vector<int> m_adj[105]{}; 

public:
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

    void dfs(int a_v)
    {
        m_visited[a_v] = true;
        std::cout << a_v << ' ';
        for (auto i : m_adj[a_v])
        {
            if (!m_visited[i])
            {
                dfs(i);
            }
        }
    }

    void bfs(int a_v)
    {
        std::queue<int> q{};
        q.push(a_v);
        m_visited[a_v] = true;
        while (!q.empty())
        {
            int v{ q.front() };
            std::cout << v << ' ';
            q.pop();
            for (auto i : m_adj[v])
            {
                if (!m_visited[i])
                {
                    m_visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);
    IO("BFS");

    int n{}, m{}, x{};
    std::cin >> n >> m >> x;
    Graph g;
    for (int i = 0; i < m; ++i)
    {
        int a{}, b{};
        std::cin >> a >> b;
        g.add_edge(a, b);
    }
    g.sort(n);
    g.bfs(x);
    return 0;
}