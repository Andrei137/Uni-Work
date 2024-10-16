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

    long long get_calcul() const
    {
        return m_x * m_x + m_y * m_y;
    }
};

long long get_determinant(const Point& a_A, const Point& a_B, const Point& a_C)
{
    return 
        a_A.get_x() * a_B.get_y() * a_C.get_calcul() +
        a_B.get_x() * a_C.get_y() * a_A.get_calcul() +
        a_C.get_x() * a_A.get_y() * a_B.get_calcul() -
        a_C.get_x() * a_B.get_y() * a_A.get_calcul() -
        a_B.get_x() * a_A.get_y() * a_C.get_calcul() -
        a_A.get_x() * a_C.get_y() * a_B.get_calcul();
}

long long test(const Point& a_A, const Point& a_B, const Point& a_C, const Point& a_D) 
{
    return
        get_determinant(a_A, a_B, a_C) -
        get_determinant(a_A, a_B, a_D) +
        get_determinant(a_A, a_C, a_D) -
        get_determinant(a_B, a_C, a_D);
}

int main() 
{
    IO();

    Point A{ read<Point>() };
    Point B{ read<Point>() };
    Point C{ read<Point>() };
    Point D{ read<Point>() };

    long long AC{ test(A, B, C, D) };
    std::cout << "AC: ";
    if (AC > 0)
    {
        std::cout << "IL";
    }
    std::cout << "LEGAL\n";

    long long BD{ test(B, C, D, A) };
    std::cout << "BD: ";
    if (BD > 0)
    {
        std::cout << "IL";
    }
    std::cout << "LEGAL\n";

    return 0;
}