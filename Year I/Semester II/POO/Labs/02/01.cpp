#include <iostream>
#include <vector>

typedef std::string str;

class Profesor 
{
    str m_nume{};
    int m_vechime{0};
public:
    Profesor(const std::string &nume, int vechime) : m_nume(nume), m_vechime(vechime) 
    {
        this->m_nume.operator=(nume);
    }
    Profesor(const Profesor& other) : m_nume(other.m_nume), m_vechime(other.m_vechime) 
    {
        std::cout << "cc prof\n";
    }
    ~Profesor() 
    {
        std::cout << "destr prof\n";
    }
    Profesor& operator=(const Profesor& other) 
    {
        m_nume = other.m_nume;
        m_vechime = other.m_vechime;
        std::cout << "op= prof\n";
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Profesor& profesor) 
    {
        out << "nume: " << profesor.m_nume << " vechime: " << profesor.m_vechime;
        return out;
    }
};

class Facultate 
{
    std::vector<Profesor> m_profi;
//    Profesor prof{"a", 1};
public:
    explicit Facultate(const std::vector<Profesor>& profi) : m_profi(profi) {}

    friend std::ostream& operator<<(std::ostream& out, const Facultate& facultate) 
    {
        out << "profi:\n";
        for (const auto& prof : facultate.m_profi)
        {
            out << prof;
        }
        return out;
    }
};

int main() 
{
    std::vector<Facultate> facultati;
    facultati.push_back(Facultate{{}});
    std::cout << "Hello, world!\n";
    std::string nume;
    std::cin >> nume;
    std::cout << "am citit " << nume << "\n";
    return 0;
}
