// Neculae Andrei-Fabian 152
// g++ (x86_64-win32-seh-rev2, Built by MinGW-W64 project) 12.2.0
// C++20 (flags: -O2, -Wall, -Weffc++, -Werror, -Wextra, -Wshadow, -Wnon-virtual-dtor, -Wno-int-in-bool-context, -pedantic)
// Micluta-Campeanu Marius

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using str = std::string;

class app_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class value_error : public app_error
{
    using app_error::app_error;
};

class Drum
{
    str denumire;
    float lungime;
    int nr_tronsoane;

protected:
    Drum(const Drum&) = default;
    Drum& operator=(const Drum&) = default;

    float get_tronson_len() const;

    virtual std::shared_ptr<Drum> clone() const = 0;
    virtual std::istream& read_drum(std::istream&) = 0;
    virtual std::ostream& print_drum(std::ostream&) const = 0;

public:
    Drum() : denumire(), lungime(), nr_tronsoane(1) {};
    Drum(const str& denumire_, float lungime_, int nr_tronsoane_) : denumire(denumire_), lungime(lungime_), nr_tronsoane(nr_tronsoane_)
    {
        if (nr_tronsoane < 1)
        {
            throw value_error("Numarul de tronsoane nu este corect!");
        }
    }

    virtual ~Drum() = default;

    virtual float get_cost() const = 0;

    friend std::istream& operator>>(std::istream&, Drum&);
    friend std::istream& operator>>(std::istream&, std::shared_ptr<Drum>&);
    friend std::ostream& operator<<(std::ostream&, const Drum&);

    int get_lungime() const;
    int get_nr_tronsoane() const;
};

float Drum::get_tronson_len() const
{
    return 1.0 * lungime / nr_tronsoane;
}

std::istream& operator>>(std::istream& is, Drum& ob)
{
    std::cout << "Denumirea drumului : ";
    is >> ob.denumire;
    std::cout << "Lungimea drumului : ";
    is >> ob.lungime;
    std::cout << "Nr tronsoane : ";
    is >> ob.nr_tronsoane;
    return ob.read_drum(is);
}

std::istream& operator>>(std::istream& is, std::shared_ptr<Drum>& ob)
{
    std::cout << "Denumirea drumului : ";
    is >> ob->denumire;
    std::cout << "Lungimea drumului : ";
    is >> ob->lungime;
    std::cout << "Nr tronsoane : ";
    is >> ob->nr_tronsoane;
    return ob->read_drum(is);
}

std::ostream& operator<<(std::ostream& os, const Drum& ob)
{
    os << "Denumirea drumului : ";
    os << ob.denumire << '\n';
    os << "Lungimea drumului : ";
    os << ob.lungime << '\n';
    os << "Nr tronsoane :";
    os << ob.nr_tronsoane << '\n';
    return ob.print_drum(os);
}


int Drum::get_nr_tronsoane() const
{
    return nr_tronsoane;
}

int Drum::get_lungime() const
{
    return lungime;
}

class DrumNational : public Drum
{
    int nr_judete;

    std::istream& read_drum(std::istream&) override;
    std::ostream& print_drum(std::ostream&) const override;

public:
    DrumNational() : Drum(), nr_judete() {};
    DrumNational(const str& denumire_, float lungime_, int nr_tronsoane_, int nr_judete_) : Drum(denumire_, lungime_, nr_tronsoane_), nr_judete(nr_judete_)
    {
        if (nr_judete < 1)
        {
            throw value_error("Numarul de judete nu este corect!");
        }
    }

    std::shared_ptr<Drum> clone() const override;

    float get_cost() const override;
};

std::shared_ptr<Drum> DrumNational::clone() const
{
    return std::make_shared<DrumNational>(*this);
}

float DrumNational::get_cost() const
{
    return get_tronson_len() * 3000;
}

std::istream& DrumNational::read_drum(std::istream& is)
{
    std::cout << "Numarul de judete : ";
    is >> nr_judete;
    return is;
}

std::ostream& DrumNational::print_drum(std::ostream& os) const
{
    os << "Numarul de judete : ";
    os << nr_judete << '\n';
    return os;
}

class DrumEuropean : virtual public Drum
{
    int nr_tari;

protected:
    int get_nr_tari() const;

    std::istream& read_drum(std::istream&) override;
    std::ostream& print_drum(std::ostream&) const override;

public:
    DrumEuropean() : Drum(), nr_tari() {};
    DrumEuropean(const str& denumire_, float lungime_, int nr_tronsoane_, int nr_tari_) : Drum(denumire_, lungime_, nr_tronsoane_), nr_tari(nr_tari_)
    {
        if (nr_tari < 1)
        {
            throw value_error("Numarul de tari nu este corect!");
        }
    }

    std::shared_ptr<Drum> clone() const override;

    float get_cost() const override;
};

int DrumEuropean::get_nr_tari() const
{
    return nr_tari;
}

std::shared_ptr<Drum> DrumEuropean::clone() const
{
    return std::make_shared<DrumEuropean>(*this);
}

float DrumEuropean::get_cost() const
{
    return get_tronson_len() * 3000 + nr_tari * 500;
}

std::istream& DrumEuropean::read_drum(std::istream& is)
{
    std::cout << "Numarul de tari : ";
    is >> nr_tari;
    return is;
}

std::ostream& DrumEuropean::print_drum(std::ostream& os) const
{
    os << "Numarul de tari : ";
    os << nr_tari << '\n';
    return os;
}

class Autostrada : virtual public Drum
{
    int nr_benzi;

protected:
    int get_nr_benzi() const;

    std::istream& read_drum(std::istream&) override;
    std::ostream& print_drum(std::ostream&) const override;

public:
    Autostrada() : Drum(), nr_benzi() {};
    Autostrada(const str& denumire_, float lungime_, int nr_tronsoane_, int nr_benzi_) : Drum(denumire_, lungime_, nr_tronsoane_), nr_benzi(nr_benzi_)
    {
        if (nr_benzi < 2)
        {
            throw value_error("Numarul de tari nu este corect!");
        }
    }

    std::shared_ptr<Drum> clone() const override;

    float get_cost() const override;
};

int Autostrada::get_nr_benzi() const
{
    return nr_benzi;
}

std::shared_ptr<Drum> Autostrada::clone() const
{
    return std::make_shared<Autostrada>(*this);
}

float Autostrada::get_cost() const
{
    return get_tronson_len() * 2500 * nr_benzi;
}

std::istream& Autostrada::read_drum(std::istream& is)
{
    std::cout << "Numarul de benzi : ";
    is >> nr_benzi;
    return is;
}

std::ostream& Autostrada::print_drum(std::ostream& os) const
{
    os << "Numarul de benzi : ";
    os << nr_benzi << '\n';
    return os;
}

class AutostradaEuropeana : public DrumEuropean, public Autostrada
{
    std::istream& read_drum(std::istream&) override;
    std::ostream& print_drum(std::ostream&) const override;

public:
    AutostradaEuropeana() : DrumEuropean(), Autostrada() {};
    AutostradaEuropeana(const str& denumire_, float lungime_, int nr_tronsoane_, int nr_tari_, int nr_benzi_) : DrumEuropean(denumire_, lungime_, nr_tronsoane_, nr_tari_), Autostrada(denumire_, lungime_, nr_tronsoane_, nr_benzi_) {}

    std::shared_ptr<Drum> clone() const override;

    float get_cost() const override;
};

std::shared_ptr<Drum> AutostradaEuropeana::clone() const
{
    return std::make_shared<AutostradaEuropeana>(*this);
}

float AutostradaEuropeana::get_cost() const
{
    return get_tronson_len() * 2500 * get_nr_benzi() + 500 * get_nr_tari();
}

std::istream& AutostradaEuropeana::read_drum(std::istream& is)
{
    DrumEuropean::read_drum(is);
    Autostrada::read_drum(is);
    return is;
}

std::ostream& AutostradaEuropeana::print_drum(std::ostream& os) const
{
    DrumEuropean::print_drum(os);
    Autostrada::print_drum(os);
    return os;
}

class Contract
{
    static int id_max;
    const int id;
    str nume;
    str cif;

    std::shared_ptr<Drum> drum;
    int tronson;

public:
    Contract() : id(id_max), nume(), cif(), drum(), tronson()
    {
        ++id_max;
    }
    Contract(const Contract& ob) : id(id_max), nume(ob.nume), cif(ob.cif), drum(ob.drum), tronson(ob.tronson)
    {
        ++id_max;
        if (tronson < 1 || tronson > drum->get_nr_tronsoane())
        {
            throw value_error("Numarul de tronsoane nu este corect!");
        }
    }
    Contract& operator=(Contract ob)
    {
        if (&ob != this)
        {
            std::swap(nume, ob.nume);
            std::swap(cif, ob.cif);
            std::swap(drum, ob.drum);
            std::swap(tronson, ob.tronson);
        }
        return *this;
    }
    ~Contract() = default;

    float get_cost();

    friend std::istream& operator>>(std::istream&, Contract&);
    friend std::ostream& operator<<(std::ostream&, const Contract&);
};

int Contract::id_max = 1;

float Contract::get_cost()
{
    return drum->get_cost() / 1000;
}

std::istream& operator>>(std::istream& is, Contract& ob)
{
    std::cout << "Nume : ";
    is >> ob.nume;
    std::cout << "Cif : ";
    is >> ob.cif;
    std::cout << "Drumul ales :\n";
    is >> ob.drum;
    std::cout << "Tronsonul ales : ";
    is >> ob.tronson;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Contract& ob)
{
    os << "Nume : ";
    os << ob.nume << '\n';
    os << "Cif : " << '\n';
    os << ob.cif << '\n';
    os << "Drumul ales :\n";
    os << ob.drum << '\n';
    os << "Tronsonul ales : ";
    os << ob.tronson << '\n';
    return os;
}

class Aplicatie
{
    std::vector<std::shared_ptr<Drum>> drumuri;
    std::vector<Contract> contracte;

public:
    Aplicatie() : drumuri(), contracte() {};
    Aplicatie(const Aplicatie&) = delete;
    Aplicatie& operator=(const Aplicatie&) = delete;
    ~Aplicatie() = default;

    int get_total_len();
    int get_total_len_autostrada();

    friend std::istream& operator>>(std::istream&, Aplicatie&);
    friend std::ostream& operator<<(std::ostream&, const Aplicatie&);
};

int Aplicatie::get_total_len()
{
    int len{ 0 };
    for (const std::shared_ptr<Drum>& drum : drumuri)
    {
        len += drum->get_lungime();
    }
    return len;
}

int Aplicatie::get_total_len_autostrada()
{
    int len{ 0 };
    for (const std::shared_ptr<Drum>& drum : drumuri)
    {
        const Autostrada* ptr = dynamic_cast<Autostrada*>(drum.get());
        if (ptr != nullptr)
        {
            len += drum->get_lungime();
        }
    }
    return len;
}

std::istream& operator>>(std::istream& is, Aplicatie& ob)
{
    std::cout << "Numar drumuri : ";
    int nr_drumuri;
    is >> nr_drumuri;
    while (nr_drumuri--)
    {
        std::shared_ptr<Drum> drum;
        std::cout << "Tipul drumului : ";
        str type;
        is >> type;
        if (type == "Drum national")
        {
            drum = std::make_shared<DrumNational>();
        }
        else if (type == "Drum european")
        {
            drum = std::make_shared<DrumEuropean>();
        }
        else if (type == "Autostrada")
        {
            drum = std::make_shared<Autostrada>();
        }
        else if (type == "Autostrada europeana")
        {
            drum = std::make_shared<AutostradaEuropeana>();
        }
        else
        {
            throw value_error("Nu exista acest tip de drum!");
        }
        is >> *drum;
        ob.drumuri.push_back(drum);
    }
    std::cout << "Numar contracte : ";
    int nr_contracte;
    is >> nr_contracte;
    while (nr_contracte--)
    {
        Contract contract;
        is >> contract;
        ob.contracte.push_back(contract);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Aplicatie& ob)
{
    for (const std::shared_ptr<Drum>& drum : ob.drumuri)
    {
        os << drum << '\n';
    }
    os << '\n';
    for (const Contract& contract : ob.contracte)
    {
        os << contract << '\n';
    }
    return os;
}

int main()
{
    try
    {
        Aplicatie app;
        std::cin >> app;
        std::cout << app;
    }
    catch (value_error& err)
    {
        std::cerr << err.what();
    }
    return 0;
}