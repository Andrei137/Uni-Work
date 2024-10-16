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
    std::ifstream in("strabunica.in");
    size_t n{ read_input<size_t>(in) };
    std::vector<int> v(n + 2, 0);
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
        while (v[s.top()] >= v[i])
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
        while (v[s.top()] >= v[i])
        {
            s.pop();
        }
        right[i] = s.top();
        s.push(i);
    }
    long long maxx{0};
    for (size_t i = 1; i <= n; ++i)
    {
        maxx = std::max(maxx, v[i] * (long long)(right[i] - left[i] - 1));
    }
    std::ofstream out("strabunica.out");
    out << maxx;
    out.close();
    return 0;
}