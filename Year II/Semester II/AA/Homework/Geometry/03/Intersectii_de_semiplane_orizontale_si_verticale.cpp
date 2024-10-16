#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

inline void IO(const std::string& a_file_name = "")
{
    if (a_file_name != "")
    {
        if (freopen((a_file_name + ".in").c_str(), "r", stdin))
        {
            return;
        }
        if (freopen((a_file_name + ".out").c_str(), "w", stdout))
        {
            return;
        }
    }
    else 
    {
        std::cin.tie(0)->sync_with_stdio(0);
    }
}

template <typename T>
inline T read(std::istream& a_in = std::cin)
{
    T temp{};
    a_in >> temp;
    return temp;
}

class HalfPlane 
{
    int m_a{};
    int m_b{};
    bool m_is_vertical{ false };

public:
    HalfPlane() = default;

    explicit HalfPlane(int a_x, int a_y, int a_b)
    {
        if (a_x == 0)
        {
            m_is_vertical = true;
            m_a = a_y;
        }
        else
        {
            m_a = a_x;
        }
        m_b = a_b;
    }

    double get_a() const
    {
        return m_a;
    }

    double get_b() const
    {
        return m_b;
    }

    bool is_vertical() const
    {
        return m_is_vertical;
    }
};

std::string get_intersection(const std::vector<HalfPlane>& a_planes)
{
    int x_min{ -INT_MAX }, y_min{ -INT_MAX };
    int x_max{ INT_MAX }, y_max{ INT_MAX };

    for (const HalfPlane& p : a_planes)
    {
        int current_min{ -INT_MAX };
        int current_max{ INT_MAX };

        if (p.get_a() > 0)
        {
            current_max = -p.get_b() / p.get_a();
        }
        else
        {
            current_min = -p.get_b() / p.get_a();
        }

        if (p.is_vertical())
        {
            y_min = std::max(y_min, current_min);
            y_max = std::min(y_max, current_max);
        }
        else
        {
            x_min = std::max(x_min, current_min);
            x_max = std::min(x_max, current_max);
        }
    }

    if (x_min > x_max || y_min > y_max)
    {
        return "VOID";
    }
    if (std::min(x_min, y_min) == -INT_MAX || std::max(x_max, y_max) == INT_MAX)
    {
        return "UNBOUNDED";
    }
    return "BOUNDED";
}

int main()
{
    IO();

    int n{ read<int>() };
    std::vector<HalfPlane> planes(n);
    for (HalfPlane& p : planes)
    {
        int x{ read<int>() };
        int y{ read<int>() };
        int b{ read<int>() };
        p = HalfPlane(x, y, b);
    }
    std::cout << get_intersection(planes) << '\n';
    return 0;
}

