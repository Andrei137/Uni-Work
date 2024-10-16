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

void update(Point a_P, Point a_Q, Point a_R, std::tuple<int, int, int>& a_nr)
{
    long long pos{ position(a_P, a_Q, a_R) };
    if (pos > 0)
    {
        ++std::get<0>(a_nr);
    }
    else if (pos < 0)
    {
        ++std::get<1>(a_nr);
    }
    else
    {
        ++std::get<2>(a_nr);
    }
}

int main()
{
    IO();

    int n{ read<int>() };
    Point P1{ read<Point>() };
    Point P1_copy{ P1 };
    Point P2{ read<Point>() };
    std::tuple<int, int, int> nr{ 0, 0, 0 };
    for (int i = 2; i < n; ++i)
    {
        Point P{ read<Point>() };
        update(P1, P2, P, nr);
        P1 = P2;
        P2 = P;
    }
    update(P1, P2, P1_copy, nr);
    std::cout << std::get<0>(nr) << ' ' << std::get<1>(nr) << ' ' << std::get<2>(nr);
    return 0;
}
