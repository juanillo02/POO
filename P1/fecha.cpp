#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iomanip>
#include <locale>

Fecha::Fecha(int dia, int mes, int anno): dia_{dia}, mes_{mes}, anno_{anno}
{
    if(dia != 0 && mes != 0 && anno != 0)
    {
        valida();
    }
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if(dia == 0)
        {
            dia_ = tiempo_descompuesto->tm_mday;
        }
        if(mes == 0)
        {
            mes_ = tiempo_descompuesto->tm_mon + 1;
        }
        if(anno == 0)
        {
            anno_ = tiempo_descompuesto->tm_year + 1900;
        }
        valida();
    }
}

Fecha::Fecha(const char* fec)
{
    int fecha = sscanf(fec, "%d/%d/%d", &dia_, &mes_, &anno_);
    if(fecha != 3)
    {
        throw Fecha::Invalida("El formato de la fecha es incorrecto.");
    }
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if(dia_ == 0)
        {
            dia_ = tiempo_descompuesto->tm_mday;
        }
        if(mes_ == 0)
        {
            mes_ = tiempo_descompuesto->tm_mon + 1;
        }
        if(anno_ == 0)
        {
            anno_ = tiempo_descompuesto->tm_year + 1900;
        }
        valida();
    }
}

Fecha& Fecha::operator++()
{
    return *this += 1;
}

Fecha& Fecha::operator--()
{
    return *this -= 1;
}

Fecha Fecha::operator++(int)
{
    Fecha aux = Fecha(*this);
    *this += 1;
    return aux;
}

Fecha Fecha::operator--(int)
{
    Fecha aux = Fecha(*this);
    *this -= 1;
    return aux;
}

Fecha Fecha::operator +(int d) const
{
    Fecha suma(*this);
    return suma += d;
}

Fecha Fecha::operator -(int d) const
{
    Fecha resta(*this);
    return resta -= d;
}

Fecha& Fecha::operator +=(int d)
{
    std::tm  f{};
    f.tm_mday = dia_ + d;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_  - 1900;
    std::mktime(&f);
    dia_ = f.tm_mday;
    mes_ = f.tm_mon + 1;
    anno_ = f.tm_year + 1900;
    valida();
    return *this;
}

Fecha& Fecha::operator -=(int d)
{
    std::tm  f{};
    f.tm_mday = dia_ - d;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_  - 1900;
    std::mktime(&f);
    dia_ = f.tm_mday;
    mes_ = f.tm_mon + 1;
    anno_ = f.tm_year + 1900;
    valida();
    return *this;
}

const char* Fecha::cadena() const
{
    if(!actual)
    {
        std::locale::global(std::locale("es_ES.UTF-8"));
        std::tm  f{};
        f.tm_mday = dia_;
        f.tm_mon = mes_ - 1;
        f.tm_year = anno_  - 1900;
        std::time_t fe = mktime(&f);
        std::tm local = *std::localtime(&fe);
        actual = true;
        std::strftime(crep, 80, "%A %d de %B de %Y", &local);
    }
    return crep;
}

void Fecha::valida()
{
    if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
    {
        throw Fecha::Invalida("El año es incorrecto.");
    }
    else
    {
        if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_== 12)
        {
            if(dia_ < 1 || dia_ > 31)
            {
                throw Fecha::Invalida("El día es incorrecto.");
            }
        }
        else if(mes_ == 2)
        {
            if(((anno_ % 4 == 0 && anno_ % 100 != 0) || anno_ % 400 == 0))
            {
                if(dia_ < 0 || dia_ > 29)
                {
                    
                throw Fecha::Invalida("El día es incorrecto.");
                }
            }
            else
            {
                if(dia_ < 0 || dia_ > 28)
                {
                    throw Fecha::Invalida("El día es incorrecto.");
                }
            }
        }
        else if(mes_ == 4 || mes_ == 6 || mes_ == 9 ||  mes_ == 11)
        {
            if(dia_ < 0 || dia_ > 30)
            {
                throw Fecha::Invalida("El dia es incorrecto.");
            }
        }
        else
        {
            throw Fecha::Invalida("El mes es incorrecto.");
        }
    }
}

bool operator == (const Fecha& F1, const Fecha& F2)
{
    if(F1.anno() == F2.anno())
    {
        if(F1.mes() == F2.mes())
        {
            if(F1.dia() == F2.dia())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator != (const Fecha& F1, const Fecha& F2)
{
    return !(F1 == F2);
}

bool operator > (const Fecha& F1, const Fecha& F2)
{
    if(F1.anno() > F2.anno())
    {
        return true;
    }
    else if(F1.anno() == F2.anno())
    {
        if(F1.mes() > F2.mes())
        {
            return true;
        }
        else if(F1.mes() == F2.mes())
        {
            if(F1.dia() > F2.dia())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator < (const Fecha& F1, const Fecha& F2)
{
    return !(F1 == F2) && !(F1 > F2);
}

bool operator >= (const Fecha& F1, const Fecha& F2)
{
    return F1 == F2 || F1 > F2;
}

bool operator <= (const Fecha& F1, const Fecha& F2)
{
    return F1 == F2 || F1 < F2;
}

std::istream& operator >> (std::istream& is, Fecha& F)
{
    char lon[11];
    is.getline(lon, 11);
    try
    {
        Fecha aux(lon);
        F = aux;
    }
    catch(Fecha::Invalida& e)
    {
        is.setstate(std::ios::failbit);
        throw e;
    }
    return is;
}

std::ostream& operator <<  (std::ostream& os, const Fecha& F) noexcept
{
    os << F.cadena();
    return os;
}