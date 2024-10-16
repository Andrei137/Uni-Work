#include <iostream>

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

int main()
{
    IO();

    int t{ read<int>() };
    while (t--)
    {
        Point P{ read<Point>() };
        Point Q{ read<Point>() };
        Point R{ read<Point>() };

        long long pos{ position(P, Q, R) };
        if (pos == 0)
        {
            std::cout << "TOUCH\n";
        }
        else if (pos < 0)
        {
            std::cout << "RIGHT\n";
        }
        else
        {
            std::cout << "LEFT\n";
        }
    }
    return 0;
}
