#include <fstream>
#include <queue>
#include <vector>

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
    std::ifstream in("proc2.in");
    int n{ read_input<int>(in) };
    int m{ read_input<int>(in) };
    std::priority_queue<int, std::vector<int>, std::greater<int>> unused{};
    while (n--)
    {
        unused.push(n + 1);
    }
    std::ofstream out("proc2.out");
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> used{};
    while (m--)
    {
        int s{ read_input<int>(in) };
        int d{ read_input<int>(in) };
        while (!used.empty() && used.top().first <= s)
        {
            unused.push(used.top().second);
            used.pop();
        }
        used.push({s + d, unused.top()});
        out << unused.top() << '\n';
        unused.pop();
    }
    in.close();
    out.close();
    return 0;
}

// https://infoarena.ro/job_detail/3031632