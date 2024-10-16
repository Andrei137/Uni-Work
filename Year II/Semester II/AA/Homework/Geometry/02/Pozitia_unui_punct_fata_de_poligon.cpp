#include <iostream>
#include <vector>
#include <algorithm>

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
    long long m_x, m_y;

public:
    explicit Point(long long a_x = 0, long long a_y = 0) : m_x(a_x), m_y(a_y) {}

    friend std::istream& operator>>(std::istream& a_in, Point& a_point)
    {
        a_in >> a_point.m_x >> a_point.m_y;
        return a_in;
    }

    Point operator+(const Point& a_point) const
    {
        return Point(m_x + a_point.m_x, m_y + a_point.m_y);
    }

    Point operator-(const Point& a_point) const
    {
        return Point(m_x - a_point.m_x, m_y - a_point.m_y);
    }

    long long get_x() const 
    {
        return m_x;
    }

    long long get_y() const 
    {
        return m_y;
    }

    long long cross_product(const Point& a_point) const
    {
        return m_x * a_point.m_y - m_y * a_point.m_x;
    }

    long long cross_product(const Point& a_point1, const Point& a_point2) const
    {
        return (a_point1 - *this).cross_product(a_point2 - *this);
    }

    long long dot_product(const Point& a_point) const
    {
        return m_x * a_point.m_x + m_y * a_point.m_y;
    }

    long long dot_product(const Point& a_point1, const Point& a_point2) const
    {
        return (a_point1 - *this).dot_product(a_point2 - *this);
    }
};

class Solution
{
    std::vector<Point> m_points;

    void read_data()
    {
        int n{ read<int>() };
        m_points.resize(n);
        std::generate(m_points.begin(), m_points.end(), []() { return read<Point>(); });
    }

    long long position(Point a_P, Point a_Q, Point a_R) const
    {
        a_Q = a_Q - a_P;
        a_R = a_R - a_P;
        return 1LL * a_Q.get_x() * a_R.get_y() - 1LL * a_Q.get_y() * a_R.get_x();
    }

    bool point_on_segment(const Point& a_A, const Point& a_B, const Point& a_target) const
    {
        return a_target.cross_product(a_A, a_B) == 0 &&
               a_target.dot_product(a_A, a_B) <= 0;
    }

    bool hits_segment(const Point& a_A, const Point& a_B, const Point& a_target) const
    {
        if (a_A.get_x() > a_B.get_x())
        {
            return hits_segment(a_B, a_A, a_target);
        }

        long long min_y{ std::min(a_A.get_y(), a_B.get_y()) };
        long long max_y{ std::max(a_A.get_y(), a_B.get_y()) };

        if (a_target.get_y() <= min_y || a_target.get_y() > max_y)
        {
            return false;
        }

        long long min_x{ a_A.get_x() };
        long long max_x{ a_B.get_x() };

        if (a_target.get_x() < min_x)
        {
            return true;
        }
        if (a_target.get_x() > max_x)
        {
            return false;
        }

        if (a_A.get_y() < a_B.get_y())
        {
            return position(a_A, a_B, a_target) > 0;
        }
        return position(a_A, a_B, a_target) < 0;
    }

public:
    Solution() : m_points()
    {
        read_data();
    }

    std::string query(const Point& a_point) const
    {
        int size{ static_cast<int>(m_points.size()) };
        if (point_on_segment(m_points[size - 1], m_points[0], a_point))
        {
            return "BOUNDARY";
        }
        int count{ 0 };
        for (int i = 1; i < size; ++i)
        {
            if (point_on_segment(m_points[i - 1], m_points[i], a_point))
            {
                return "BOUNDARY";
            }
            count += hits_segment(m_points[i - 1], m_points[i], a_point);
        }
        count += hits_segment(m_points[size - 1], m_points[0], a_point);
        return count % 2 == 0 ? "OUTSIDE" : "INSIDE";
    }
};

int main()
{
    IO();

    Solution solution;
    int m{ read<int>() };
    while (m--)
    {
        Point point{ read<Point>() };
        std::cout << solution.query(point) << '\n';
    }
    return 0;
}