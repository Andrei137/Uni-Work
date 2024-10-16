#include <algorithm>
#include <iostream>
#include <vector>

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
    int m_x{};
    int m_y{};

public:
    Point() = default;
    explicit Point(int a_x, int a_y) : m_x(a_x), m_y(a_y) {}

    Point(const Point& a_point)
    {
        m_x = a_point.m_x;
        m_y = a_point.m_y;
    }

    Point& operator=(const Point& a_point)
    {
        m_x = a_point.m_x;
        m_y = a_point.m_y;
        return *this;
    }

    Point& operator-=(const Point& a_point)
    {
        m_x -= a_point.m_x;
        m_y -= a_point.m_y;
        return *this;
    }

    bool operator<(const Point& a_point) const
    {
        if (m_x == a_point.m_x)
        {
            return m_y < a_point.m_y;
        }
        return m_x < a_point.m_x;
    }

    friend std::istream& operator>>(std::istream& a_in, Point& a_point)
    {
        a_in >> a_point.m_x >> a_point.m_y;
        return a_in;
    }

    friend std::ostream& operator<<(std::ostream& a_out, const Point& a_point)
    {
        a_out << a_point.m_x << ' ' << a_point.m_y << '\n';
        return a_out;
    }

    int get_x() const
    {
        return m_x;
    }

    int get_y() const
    {
        return m_y;
    }
};

long long position(Point a_P, Point a_Q, Point a_R) 
{
    a_Q -= a_P;
    a_R -= a_P;
    return 1LL * a_Q.get_x() * a_R.get_y() - 1LL * a_Q.get_y() * a_R.get_x();
}

std::vector<Point> graham_scan(std::vector<Point>& a_points)
{
    int size{ static_cast<int>(a_points.size()) };
    int min_idx{ 0 };
    for (int i = 1; i < size; ++i)
    {
        if (a_points[i] < a_points[min_idx])
        {
            min_idx = i;
        }
    }
    std::rotate(a_points.begin(), a_points.begin() + min_idx, a_points.end());

    std::vector<Point> hull{};
    for (const Point& point : a_points)
    {
        while (hull.size() > 1 && position(hull[hull.size() - 2], hull.back(), point) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    while (hull.size() > 2 && position(hull[hull.size() - 2], hull.back(), hull[0]) <= 0)
    {
        hull.pop_back();
    }

    return hull;
}

int main()
{
    int n{ read<int>() };
    std::vector<Point> points(n);
    for (Point& point : points)
    {
        point = read<Point>();
    }

    std::vector<Point> hull{ graham_scan(points) };
    std::cout << hull.size() << '\n';
    for (const Point& point : hull)
    {
        std::cout << point;
    }
    return 0;
}