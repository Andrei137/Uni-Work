// Produs(denumire, pret, cantitate)
// Magazin(vector de produse v[20], nr produse)
// Demo
// Produs p1, p2("apa", 3.5, 1)
// cin >> p1
// cout << p1 << p2;
// p2 = p2 - 1.2 -> scad pretul
// p1++, ++p1
// if (p1 == p2) cout << "aceleasi"
// else cout << "nimic"
// Magazin m
// cin >> m
// cout << m
// m += p1
// m = m + p2
// cout << m[1] << endl
// m["apa"] -> afisare
// cout << -m -> preturile sunt negative

#include <iostream>

class Produs
{
    std::string m_denumire{};
    float m_pret{};
    int m_cantitate{};

public:
    Produs(const std::string& denumire = "", float pret = 0, int cantitate = 0)
        : m_denumire{denumire}, m_pret{pret}, m_cantitate{cantitate} {}
    friend std::istream& operator>>(std::istream&, Produs&);
    friend std::ostream& operator<<(std::ostream&, Produs&);
    void afisare();
    Produs operator-(float);
    Produs& operator++();
    Produs operator++(int);
    bool operator==(const Produs&);
    operator float() { return m_pret; }
};

class Magazin
{
    Produs m_produse[20];
    int m_nr_produse{};

public:
    Magazin(){}
    friend std::istream& operator>>(std::istream& in, Magazin& m)
    {
        in >> m.m_nr_produse;
        for (int i = 0; i < m.m_nr_produse; ++i)
            in >> m.m_produse[i];
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Magazin& m)
    {
        for (int i = 0; i < m.m_nr_produse; ++i)
            out << m.m_produse[i];
        return out;
    }
    Magazin& operator+=(const Produs& p)
    {
        if (m_nr_produse < 20)
        {
            m_produse[m_nr_produse++] = p;
        }
        return *this;
    }
    Magazin operator+(const Produs& p)
    {
        Magazin m{*this};
        m += p;
        return m;
    }
    Produs& operator[](int k)
    {
        if (!(k > 0 && k < 20))
        {
           throw -1; 
        }
        return m_produse[k];
    }
    Produs* operator[](const std::string& s)
    {
        for (int i = 0; i < m_nr_produse; ++i)
        {
            if (m_produse[i] == s)
            {
                return &m_produse[i]; // m_produse + i
            }
        }
        return 0;
    }
};

std::istream& operator>>(std::istream& in, Produs& p)
{
    return in >> p.m_denumire >> p.m_pret >> p.m_cantitate;
}

std::ostream& operator<<(std::ostream& out, Produs& p)
{
    return out << p.m_denumire << ' ' << p.m_pret << ' ' << p.m_cantitate << '\n';
}

void Produs::afisare()
{
    std::cout << m_denumire << ' ' << m_pret << ' ' << m_cantitate << '\n';
}

Produs Produs::operator-(float x)
{
    return Produs(m_denumire, m_pret - x, m_cantitate);
}

Produs& Produs::operator++()
{
    ++m_cantitate;
    return *this;
}

Produs Produs::operator++(int)
{
    return Produs{m_denumire, m_pret, m_cantitate++};
}

bool Produs::operator==(const Produs& produs)
{
    return m_pret == produs.m_pret && m_cantitate == produs.m_cantitate && m_denumire == produs.m_denumire;
}

int main()
{
    Produs p1;
    std::cin >> p1;
    std::cout << p1;
    Produs p2{"apa", 3.5, 1};
    std::cout << p2;
    float x{1.2};
    p2 = p2 - x;
    std::cout << p2;
    p2++;
    ++p2;
    std::cout << p2;
    if (p1 == p2)
        std::cout << "aceleasi\n";
    else
        std::cout << "nimic\n";
    Magazin m;
    try
    {
        std::cout << m[0];
    }
    catch (int)
    {
        std::cout << "Ai dat-o in bara!\n";
    }
    return 0;
}