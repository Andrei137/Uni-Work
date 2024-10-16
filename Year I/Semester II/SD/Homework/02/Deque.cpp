#include <fstream>
#include <queue>
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
    std::ifstream in("deque.in");
    size_t n{ read_input<size_t>(in) };
    size_t k{ read_input<size_t>(in) };
    std::vector<int> v{};
    for (size_t i = 0; i < n; ++i)
    {
        v.push_back(read_input<int>(in));
    }
    in.close();
    std::deque<size_t> dq{};
    long long s{0};
    for (size_t i = 0; i < n; ++i)
    {
        while (!dq.empty() && v[i] <= v[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        if (dq.front() == i - k)
        {
            dq.pop_front();
        }
        if (i >= k - 1)
        {
            s += v[dq.front()];
        }
    }
    std::ofstream out("deque.out");
    out << s;
    out.close();
    return 0;
}

// https://infoarena.ro/job_detail/3031691