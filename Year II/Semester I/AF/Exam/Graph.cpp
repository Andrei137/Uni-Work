#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::string str;

void IO(bool a_fstream = 0, const std::string& a_s = "")
{
    std::cin.tie(0)->sync_with_stdio(0);
    if (a_fstream)
    {
        freopen((a_s + "/Text.in").c_str(), "r", stdin);
        freopen((a_s + "/Text.out").c_str(), "w", stdout);
    }
}

template <typename T>
T read()
{
    T temp{};
    std::cin >> temp;
    return temp;
}

class Graph
{
    enum Color
    {
        WHITE = 0,
        GREY = 1,
        BLACK = 2
    };

    std::map<str, std::vector<str>> m_adj{};
    std::unordered_map<str, Color> m_color{};
    std::unordered_map<str, int> m_distance{};
    std::unordered_map<str, str> m_parent{};
    std::unordered_map<str, int> m_start{};
    std::unordered_map<str, int> m_finish{};
    std::unordered_map<str, int> m_component{};
    std::unordered_map<str, int> m_indegree{};
    std::unordered_map<str, int> m_outdegree{};
    std::unordered_map<str, int> m_level{};
    std::unordered_map<str, int> m_min_level{};
    std::queue<std::pair<str, str>> m_critical_edges{};
    std::unordered_set<str> m_critical_nodes{};
    std::queue<str> m_path{};
    bool m_has_cycle{};
    int m_choice{};


    void init(int a_m, bool a_oriented)
    {
        for (int i = 0; i < a_m; ++i)
        {
            str x{ read<str>() };
            str y{ read<str>() };

            m_adj[x].push_back(y);
            ++m_outdegree[x];
            ++m_indegree[y];
            if (!a_oriented)
            {
                m_adj[y].push_back(x);
                ++m_outdegree[y];
                ++m_indegree[x];
            }

        }
        
        for (const auto& [key, _] : m_adj)
        {
            m_color[key] = WHITE;
            m_distance[key] = -1;
            m_parent[key] = "NIL";
            m_start[key] = m_finish[key] = 0;
            m_level[key] = 1;
            std::sort(m_adj[key].begin(), m_adj[key].end());
        }
    }

    void reset()
    {
        m_color = std::unordered_map<str, Color>{};
        m_critical_edges = std::queue<std::pair<str, str>>{};
        m_critical_nodes = std::unordered_set<str>{};
        m_path = std::queue<str>{};
        m_has_cycle = false;
        for (const auto& [key, _] : m_adj)
        {
            m_color[key] = WHITE;
            m_distance[key] = -1;
            m_parent[key] = "NIL";
            m_start[key] = m_finish[key] = 0;
            m_min_level[key] = 0;
            m_level[key] = 1;
        }

        m_indegree.clear();
        m_outdegree.clear();

        for (const auto& [key, _] : m_adj)
        {
            for (const str& v : m_adj[key])
            {
                ++m_outdegree[key];
                ++m_indegree[v];
            }
        }
    }


    // BFS
    void bfs(str a_u)
    {
        m_color[a_u] = GREY;
        m_distance[a_u] = 0;
        m_parent[a_u] = "NIL";
        m_path.push(a_u);
        
        std::queue<str> q{};
        q.push(a_u);

        while (!q.empty())
        {
            str u{ q.front() };
            q.pop();

            for (const str& v : m_adj[u])
            {
                if (m_color[v] == WHITE)
                {
                    m_color[v] = GREY;
                    m_distance[v] = m_distance[u] + 1;
                    m_parent[v] = u;
                    m_path.push(v);
                    q.push(v);
                }
            }

            m_color[u] = BLACK;
        }
    }

    void print_bfs()
    {
        std::cout << "Order of traversal:\n";
        int index{ 1 };
        while (!m_path.empty())
        {
            str curr_node{ m_path.front() };
            std::cout << index++ << ". " << curr_node << '\n';
            std::cout << "Distance: " << m_distance[curr_node] << " Parent: " << m_parent[curr_node] << '\n';
            m_path.pop();
        }
    }


    // DFS
    void dfs_(str a_u, int& a_time, int& a_component)
    {
        m_color[a_u] = GREY;
        m_start[a_u] = ++a_time;
        m_component[a_u] = a_component;
        m_min_level[a_u] = m_level[a_u];
        
        for (const str& v : m_adj[a_u])
        {
            if (m_color[v] == WHITE)
            {
                m_parent[v] = a_u;
                m_level[v] = m_level[a_u] + 1;
                dfs_(v, a_time, a_component);
                m_min_level[a_u] = std::min(m_min_level[a_u], m_min_level[v]);
                if (m_min_level[v] > m_level[a_u])
                {
                    m_critical_edges.push({ a_u, v });
                }
            }
            else if (m_color[v] == GREY)
            {
                m_has_cycle = true;
                if (m_level[v] < m_level[a_u] - 1)
                {
                    m_min_level[a_u] = std::min(m_min_level[a_u], m_level[v]);
                }
            }
        }
        m_color[a_u] = BLACK;
        m_finish[a_u] = ++a_time;
    }

    void dfs()
    {
        int time{ 0 };
        int component{ 1 };
        for (const auto& [key, _] : m_adj)
        {
            if (m_color[key] == WHITE)
            {
                dfs_(key, time, component);

                int nr_of_children{ 0 };
                for (const auto& node : m_adj[key])
                {
                    if (m_parent[node] == key)
                    {
                        ++nr_of_children;
                    }
                }
                if (nr_of_children > 1)
                {
                    m_critical_nodes.insert(key);
                }

                ++component;
            }
        }
    }

    void print_dfs()
    {
        for (const auto& [key, _] : m_adj)
        {
            std::cout << key << " -> " << "Start: " << m_start[key] << " Finish: " << m_finish[key] << " Parent: " << m_parent[key] << " Component: " << m_component[key] << '\n';
        }
    }


    // Topological Sort
    bool has_cycle()
    {
        dfs();
        bool has_cycle{ m_has_cycle };
        reset();
        return has_cycle;
    }

    void topological_sort()
    {
        if (has_cycle())
        {
            std::cout << "The graph has a cycle!\n";
            return;
        }

        std::queue<str> q{};
        for (const auto& [key, _] : m_adj)
        {
            if (m_indegree[key] == 0)
            {
                q.push(key);
            }
        }

        while (!q.empty())
        {
            str u{ q.front() };
            q.pop();

            m_path.push(u);

            for (const str& v : m_adj[u])
            {
                --m_indegree[v];
                if (m_indegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
    }

    // Topological Sort with DFS
    void topological_sort_dfs()
    {
        if (has_cycle())
        {
            std::cout << "The graph has a cycle!\n";
            return;
        }

        dfs();
        std::vector<std::pair<str, int>> finish{};
        for (const auto& [key, _] : m_adj)
        {
            finish.push_back({ key, m_finish[key] });
        }
        std::sort(finish.begin(), finish.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
        for (const auto& [key, _] : finish)
        {
            m_path.push(key);
        }
    }

    void print_topological_sort()
    {
        if (!m_path.empty())
        {
            std::cout << "Topological sort:\n";
            int index{ 1 };
            while (!m_path.empty())
            {
                std::cout << index++ << ". " << m_path.front() << '\n';
                m_path.pop();
            }
        }
    }


    // Critical Edges
    void print_critical_edges()
    {
        if (!m_critical_edges.empty())
        {
            std::cout << "Critical edges:\n";
            int index{ 1 };
            while (!m_critical_edges.empty())
            {
                std::cout << index++ << ". " << m_critical_edges.front().first << " -> " << m_critical_edges.front().second << '\n';
                m_critical_edges.pop();
            }
        }
        else
        {
            std::cout << "No critical edges!\n";
        }
    }


    // Critical Nodes
    void critical_nodes()
    {
        dfs();
        for (const auto& [key, _] : m_adj)
        {
            for (const auto& node : m_adj[key])
            {
                if (m_min_level[node] >= m_level[key])
                {
                    m_critical_nodes.insert(key);
                }
            }
        }
    }

    void print_critical_nodes()
    {
        if (!m_critical_nodes.empty())
        {
            std::cout << "Critical nodes:\n";
            int index{ 1 };
            while (!m_critical_nodes.empty())
            {
                std::cout << index++ << ". " << m_critical_nodes.begin()->c_str() << '\n';
                m_critical_nodes.erase(m_critical_nodes.begin());
            }
        }
        else
        {
            std::cout << "No critical nodes!\n";
        }
    }

public:
    explicit Graph(int a_n, int a_m, bool a_oriented, int a_choice) : m_color(a_n), m_distance(a_n), m_parent(a_n), m_start(a_n), m_finish(a_n), m_component(a_n), m_indegree(a_n), m_outdegree(a_n), m_level(a_n), m_min_level(a_n), m_has_cycle(false), m_choice(a_choice)
    {
        init(a_m, a_oriented);
    }

    friend std::ostream& operator<<(std::ostream& out, Graph& a_g)
    {
        if (a_g.m_choice == 1)
        {
            a_g.bfs(a_g.m_adj.begin()->first);
            a_g.print_bfs();
        }
        else if (a_g.m_choice == 2)
        {
            a_g.dfs();
            a_g.print_dfs();
        }
        else if (a_g.m_choice == 3)
        {
            a_g.topological_sort();
            a_g.print_topological_sort();
        }
        else if (a_g.m_choice == 4)
        {
            a_g.topological_sort_dfs();
            a_g.print_topological_sort();
        }
        else if (a_g.m_choice == 5)
        {
            a_g.dfs();
            a_g.print_critical_edges();
        }
        else if (a_g.m_choice == 6)
        {
            a_g.critical_nodes();
            a_g.print_critical_nodes();
        }
        a_g.reset();
        return out;
    }
};

int main()
{
    std::unordered_map<int, str> choice_map
    { 
        {1, "BFS"}, 
        {2, "DFS"}, 
        {3, "TopSort"}, 
        {4, "TopSortDFS"},
        {5, "CriticalEdges"},
        {6, "CriticalNodes"}
    };

    int choice{};
    std::cout << "[1] BFS\n";
    std::cout << "[2] DFS\n";
    std::cout << "[3] Topological Sort\n";
    std::cout << "[4] Topological Sort with DFS\n";
    std::cout << "[5] Critical Edges\n";
    std::cout << "[6] Critical Nodes\n";
    std::cout << "-> ";
    std::cin >> choice;

    IO(1, choice_map[choice]);

    int n{ read<int>() };
    int m{ read<int>() };
    bool oriented{ read<bool>() };

    Graph g{ n, m, oriented, choice };
    std::cout << g << '\n';

    return 0;
}