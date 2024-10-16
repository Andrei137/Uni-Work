#include <climits>
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
    std::ifstream in("knumere.in");
    size_t n{ read_input<size_t>(in) };
    size_t k{ n - 1 - read_input<size_t>(in) };
    int x{ read_input<int>(in) };
    std::vector<int> diff{};
    while (--n)
    {
        int y{ read_input<int>(in) };
        diff.push_back(y - x);
        x = y;
    }
    in.close();
    std::deque<size_t> dq{};
    long long min_diff{ INT_MAX };
    size_t size{ diff.size() };
    for (size_t i = 0; i < size; ++i)
    {
        while (!dq.empty() && diff[i] >= diff[dq.back()])
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
            min_diff = std::min(min_diff, (long long)diff[dq.front()]);
        }
    }
    std::ofstream out("knumere.out");
    out << min_diff;
    out.close();
    return 0;
}

// https://infoarena.ro/job_detail/3031696
