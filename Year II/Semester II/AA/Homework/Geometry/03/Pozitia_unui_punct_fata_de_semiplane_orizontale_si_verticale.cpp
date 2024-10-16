#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <iomanip>

const double epsilon = 1e-5;

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

class Point 
{
    double m_x{};
    double m_y{};

public:
    Point() = default;
    explicit Point(double a_x, double a_y) : m_x(a_x), m_y(a_y) {}

    friend std::istream& operator>>(std::istream& a_in, Point& a_point)
    {
        a_in >> a_point.m_x >> a_point.m_y;
        return a_in;
    }

    double get_x() const
    {
        return m_x;
    }

    double get_y() const
    {
        return m_y;
    }
};

class HalfPlane 
{
    double m_a{};
    double m_b{};
    bool m_is_vertical{ false };

public:
    HalfPlane() = default;

    explicit HalfPlane(double a_x, double a_y, double a_b)
    {
        if (std::abs(a_x) <= epsilon)
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

    double get_support_line() const
    {
        return -m_b / m_a;
    }

    bool contains_point(const Point& a_point) const
    {
        if (m_is_vertical)
        {
            return m_a * a_point.get_y() + m_b < 0;
        }
        return m_a * a_point.get_x() + m_b < 0;
    }
};

double solve(const std::vector<HalfPlane>& a_planes, const Point& a_point)
{
    double x_min{ -INT_MAX }, y_min{ -INT_MAX };
    double x_max{ INT_MAX }, y_max{ INT_MAX };

    for (const HalfPlane& p : a_planes)
    {
        if (!p.contains_point(a_point))
        {
            continue;
        }

        double line{ p.get_support_line() };

        if (p.is_vertical())
        {
            if (line < a_point.get_y())
            {
                y_min = std::max(y_min, line);
            }
            if (line > a_point.get_y())
            {
                y_max = std::min(y_max, line);
            }
        }
        else
        {
            if (line < a_point.get_x())
            {
                x_min = std::max(x_min, line);
            }
            if (line > a_point.get_x())
            {
                x_max = std::min(x_max, line);
            }
        }
    }
        
    if (std::min(x_min, y_min) == -INT_MAX || std::max(x_max, y_max) == INT_MAX)
    {
        return -1;
    }
    return (x_max - x_min) * (y_max - y_min);
}

int main()
{
    IO();

    int n{ read<int>() };
    std::vector<HalfPlane> planes(n);
    for (HalfPlane& p : planes)
    {
        double x{ read<double>() };
        double y{ read<double>() };
        double b{ read<double>() };
        p = HalfPlane(x, y, b);
    }

    int m{ read<int>() };
    while (m--)
    {
        Point Q{ read<Point>() };
        double result{ solve(planes, Q) };
        if (result < 0)
        {
            std::cout << "NO\n";
        }
        else
        {
            std::cout << "YES\n" << std::fixed << std::setprecision(6) << result << '\n';
        }
    }
    return 0;
}

