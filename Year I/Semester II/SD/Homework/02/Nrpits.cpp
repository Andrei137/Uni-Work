#include <climits>
#include <fstream>
#include <stack>
#include <vector>

template<typename T>
T read_input(std::ifstream& in)
{
    T temp{};
    in >> temp;
    return temp;
}

int main()
{
    std::ifstream in("nrpits.in");
    size_t n{ read_input<size_t>(in) };
    std::vector<int> v(n + 2, INT_MAX);
    for (size_t i = 1; i <= n; ++i)
    {
        v[i] = read_input<int>(in);
    }
    in.close();
    std::stack<size_t> s{};
    s.push(0);
    std::vector<size_t> left(n + 1);
    for (size_t i = 1; i <= n; ++i)
    {
        while (v[s.top()] <= v[i])
        {
            s.pop();
        }
        left[i] = s.top();
        s.push(i);
    }
    while (!s.empty())
    {
        s.pop();
    }
    s.push(n + 1);
    std::vector<size_t> right(n + 1);
    for (size_t i = n; i >= 1; --i)
    {
        while (v[s.top()] <= v[i])
        {
            s.pop();
        }
        right[i] = s.top();
        s.push(i);
    }
    long long nr{0};
    for (size_t i = 1; i <= n; ++i)
    {
        if (v[right[i]] != INT_MAX && v[left[i]] != INT_MAX)
        {
            ++nr;
        }
    }
    std::ofstream out("nrpits.out");
    out << nr;
    out.close();
    return 0;
}

// https://www.infoarena.ro/job_detail/3031714