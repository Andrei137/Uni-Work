#include <algorithm>
#include <cmath>
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
    long long m_x, m_y;

public:
    Point() : m_x(0), m_y(0) {}
    explicit Point(long long a_x, long long a_y) : m_x(a_x), m_y(a_y) {}

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
    std::vector<Point> m_sequence;
    Point m_translation;
    int m_size;

    int sgn(long long a_value)
    {
        return a_value > 0 ? 1 : (a_value == 0 ? 0 : -1);
    }

    bool lexical_cmp(const Point& a_point1, const Point& a_point2)
    {
        long long x1{ a_point1.get_x() }, x2{ a_point2.get_x() };
        if (x1 == x2)
        {
            return a_point1.get_y() < a_point2.get_y();
        }
        return x1 < x2;
    }

    long long position(Point a_P, Point a_Q, Point a_R) 
    {
        a_Q = a_Q - a_P;
        a_R = a_R - a_P;
        return 1LL * a_Q.get_x() * a_R.get_y() - 1LL * a_Q.get_y() * a_R.get_x();
    }

    void remove_collinear_points(std::vector<Point>& a_points)
    {
        std::vector<Point> new_sequence;
        new_sequence.push_back(a_points[0]);
        new_sequence.push_back(a_points[1]);
        int size{ static_cast<int>(a_points.size()) };
        for (int i = 2; i < size; ++i)
        {
            int new_size{ static_cast<int>(new_sequence.size()) };
            while (new_size >= 2 && position(new_sequence[new_size - 2], new_sequence[new_size - 1], a_points[i]) == 0)
            {
                new_sequence.pop_back();
                --new_size;
            }
            new_sequence.push_back(a_points[i]);
        }
        while (new_sequence.size() >= 3 && position(new_sequence[new_sequence.size() - 2], new_sequence[new_sequence.size() - 1], new_sequence[0]) == 0)
        {
            new_sequence.pop_back();
        }
        a_points = new_sequence;
    }

    bool point_on_segment(const Point& a_A, const Point& a_B, const Point& a_target)
    {
        return a_target.cross_product(a_A, a_B) == 0 &&
               a_target.dot_product(a_A, a_B) <= 0;
    }

    std::string point_in_triangle(const Point& a_A, const Point& a_B, const Point& a_C, const Point& a_target)
    {
        if (a_target.cross_product(a_A, a_B) == 0)
        {
            return (point_on_segment(a_A, a_B, a_target) ? "BOUNDARY" : "OUTSIDE");
        }

        long long s1{ std::abs(a_A.cross_product(a_B, a_C)) };
        long long s2{ std::abs(a_target.cross_product(a_A, a_B)) +
                      std::abs(a_target.cross_product(a_B, a_C)) +
                      std::abs(a_target.cross_product(a_C, a_A)) };
        return (s1 == s2 ? "INSIDE" : "OUTSIDE");
    }

    void prepare(std::vector<Point>& a_points)
    {
        m_size = a_points.size();
        int pos{ 0 };
        for (int i = 1; i < m_size; ++i)
        {
            if (lexical_cmp(a_points[i], a_points[pos]))
            {
                pos = i;
            }
        }
        std::rotate(a_points.begin(), a_points.begin() + pos, a_points.end());
        remove_collinear_points(a_points);

        m_size = a_points.size() - 1;
        m_sequence.resize(m_size);
        for (int i = 0; i < m_size; ++i)
        {
            m_sequence[i] = a_points[i + 1] - a_points[0];
        }
        m_translation = a_points[0];
    }

public:
    explicit Solution(std::vector<Point>& a_points) : m_sequence(), m_translation(), m_size(0)
    {
        prepare(a_points);
    }

    std::string point_in_convex_polygon(Point a_point)
    {
        Point O{ Point(0, 0) };
        a_point = a_point - m_translation;

        if (point_on_segment(m_sequence[0], O, a_point) ||
            point_on_segment(m_sequence[m_size - 1], O, a_point))
        {
            return "BOUNDARY";
        }

        if (sgn(m_sequence[0].cross_product(a_point)) != sgn(m_sequence[0].cross_product(m_sequence[m_size - 1])))
        {
            return "OUTSIDE";
        }
        if (sgn(m_sequence[m_size - 1].cross_product(a_point)) != sgn(m_sequence[m_size - 1].cross_product(m_sequence[0])))
        {
            return "OUTSIDE";
        }

        int left{ 0 }, right{ m_size - 1 };
        while (right - left > 1)
        {
            int middle{ left + (right - left) / 2 };
            if (m_sequence[middle].cross_product(a_point) >= 0)
            {
                left = middle;
            }
            else
            {
                right = middle;
            }
        }
        return point_in_triangle(m_sequence[left], m_sequence[left + 1], O, a_point);
    }
};

int main()
{
    IO();

    int n{ read<int>() };
    std::vector<Point> points(n);
    std::generate(points.begin(), points.end(), []() { return read<Point>(); });

    Solution solution(points);
    int m{ read<int>() };
    while (m--)
    {
        Point point = read<Point>();
        std::cout << solution.point_in_convex_polygon(point) << '\n';
    }
    return 0;
}