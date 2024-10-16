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

    friend std::ostream& operator<<(std::ostream& a_out, const Point& a_point)
    {
        a_out << a_point.m_x << ' ' << a_point.m_y;
        return a_out;
    }

    long long get_x() const
    {
        return m_x;
    }

    long long get_y() const
    {
        return m_y;
    }

    long long get_coordinate(char a_coordinate) const
    {
        return a_coordinate == 'x' ? m_x : m_y;
    }
};

class Solution
{
    std::vector<Point> m_points;
    int m_uppermost, m_lowermost;
    int m_leftmost, m_rightmost;

    void read_data()
    {
        int n{ read<int>() };
        m_points.resize(n);
        std::generate(m_points.begin(), m_points.end(), []() { return read<Point>(); });
    }

    bool goes_back(int a_start, int a_end, bool a_clockwise, int a_coordinate) const
    {
        if (a_clockwise)
        {
            for (int i = a_start - 1; i >= a_end; --i)
            {
                if (m_points[i].get_coordinate(a_coordinate) < m_points[i + 1].get_coordinate(a_coordinate))
                {
                    return true;
                }
            }
        }
        else
        {
            for (int i = a_start + 1; i <= a_end; ++i)
            {
                if (m_points[i].get_coordinate(a_coordinate) < m_points[i - 1].get_coordinate(a_coordinate))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_x_monotonic() const
    {
        if (goes_back(m_leftmost, m_rightmost, false, 'x'))
        {
            return false;
        }
        int clockwise_neighbor{ m_leftmost == 0 ? static_cast<int>(m_points.size()) - 1 : m_leftmost - 1 };
        if (m_points[clockwise_neighbor].get_x() == m_points[m_leftmost].get_x())
        {
            return false;
        }
        return !goes_back(clockwise_neighbor, m_rightmost, true, 'x');
    }

    bool is_y_monotonic() const
    {
        if (goes_back(m_lowermost, m_uppermost, false, 'y'))
        {
            return false;
        }
        int clockwise_neighbor{ m_lowermost == 0 ? static_cast<int>(m_points.size()) - 1 : m_lowermost - 1 };
        if (m_points[clockwise_neighbor].get_y() == m_points[m_lowermost].get_y())
        {
            return false;
        }
        return !goes_back(clockwise_neighbor, m_uppermost, true, 'y');
    }

    void get_extremes()
    {
        int size{ static_cast<int>(m_points.size()) };
        for (int i = 1; i < size; ++i)
        {
            if (m_points[i].get_x() < m_points[m_leftmost].get_x())
            {
                m_leftmost = i;
            }
            if (m_points[i].get_x() > m_points[m_rightmost].get_x())
            {
                m_rightmost = i;
            }
            if (m_points[i].get_y() < m_points[m_lowermost].get_y())
            {
                m_lowermost = i;
            }
            if (m_points[i].get_y() > m_points[m_uppermost].get_y())
            {
                m_uppermost = i;
            }
        }
    }

public:
    Solution() : m_points(), m_uppermost(0), m_lowermost(0), m_leftmost(0), m_rightmost(0) 
    {
        read_data();
        get_extremes();
    }

    void solve() const
    {
        std::cout << (is_x_monotonic() ? "YES" : "NO") << '\n';
        std::cout << (is_y_monotonic() ? "YES" : "NO") << '\n';
    }
};

int main()
{
    IO();

    Solution solution;
    solution.solve();
    return 0;
}