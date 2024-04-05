#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a)
{
    if (d != 0 && m != 0 && a != 0)
    {
        valida();
    }
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        int dia = tiempo_descompuesto->tm_mday;
        int mes = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
        int anno = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900
        if (a == 0)
        {
            anno_ = anno;
        }
        if (m == 0)
        {
            mes_ = mes;
        }
        if (d == 0)
        {
            dia_ = dia;
        }
        valida();
    }
}

Fecha::Fecha(const char* cadena)
{
    int fecha = sscanf(cadena, "%d/%d/%d", &dia_, &mes_, &anno_);
    if (fecha != 3)
    {
        throw Fecha::Invalida("El formato de conversion no es correcto.");
    }
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if(dia_ == 0){
            dia_ = tiempo_descompuesto->tm_mday;
        }
        if(mes_ == 0){
            mes_ = tiempo_descompuesto->tm_mon + 1;
        }
        if(anno_ == 0){
            anno_ = tiempo_descompuesto->tm_year + 1900;
        }
        valida(); 
    }
}

Fecha& Fecha::operator ++ ()
{
    return *this += 1;
}

Fecha& Fecha::operator -- ()
{
    return *this += -1;
}

Fecha Fecha::operator ++ (int)
{
    Fecha f = Fecha(*this);
    *this += 1;
    return f;
}

Fecha Fecha::operator -- (int)
{
    Fecha f = Fecha(*this);
    *this += -1;
    return f;
}

Fecha Fecha::operator + (int d) const
{
    Fecha f(*this);
    return f += d;
}

Fecha Fecha::operator - (int d) const
{
    Fecha f(*this);
    return f += -d;
}

Fecha& Fecha::operator += (int d)
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

Fecha& Fecha::operator -= (int d)
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

bool operator == (const Fecha& F1, const Fecha& F2)
{
    if (F1.dia() == F2.dia() && F1.mes() == F2.mes() && F1.anno() == F2.anno())
    {
        return true;
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
    else
    {
        if(F1.anno() == F2.anno())
        {
            if(F1.mes() > F2.mes())
            {
                return true;
            }
            else
            {
                if(F1.mes() == F2.mes())
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
        }
        else
        {
            return false;
        }
    }
}

bool operator < (const Fecha& F1, const Fecha& F2)
{
    if(F1.anno() < F2.anno())
    {
        return true;
    }
    else
    {
        if(F1.anno() == F2.anno())
        {
            if(F1.mes() < F2.mes())
            {
                return true;
            }
            else
            {
                if(F1.mes() == F2.mes())
                {
                    if(F1.dia() < F2.dia())
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
        }
        else
        {
            return false;
        }
    }
}

bool operator >= (const Fecha& F1, const Fecha& F2)
{
    return !(F1 < F2);
}

bool operator <= (const Fecha& F1, const Fecha& F2)
{
    return !(F1 > F2);
}

void Fecha::valida() const
{
    if (anno_ > AnnoMinimo && anno_ < AnnoMaximo)
    {
        if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
        {
            if (dia_ < 1 || dia_ > 31)
            {
                throw Fecha::Invalida("El dia es incorrecto");
            }
        }
        else
        {
            if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
            {
                if (dia_ < 1 || dia_ > 30)
                {
                    throw Fecha::Invalida("El dia es incorrecto");
                }
            }
            else
            {
                if (mes_ == 2)
                {
                    if ((anno_ % 4 == 0 && anno_ % 100 != 0) || anno_ % 400 == 0)
                    {
                        if (dia_ < 1 || dia_ > 29)
                        {
                            throw Fecha::Invalida("El dia es incorrecto");
                        }
                    }
                    else
                    {
                        if (dia_ < 1 || dia_ > 28)
                        {
                            throw Fecha::Invalida("El dia es incorrecto");
                        }
                    }
                }
                else
                {
                    throw Fecha::Invalida("El mes es incorrecto");
                }
            }
            
        }
    }
    else
    {
        throw Fecha::Invalida("El anno es incorrecto");
    }
}

const char* Fecha::cadena() const
{
    if (!actual)
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

std::istream& operator >> (std::istream& is, Fecha& F)
{
    char lon[11];
    is.getline(lon, 11);
    try
    {
        Fecha aux(lon);
        F = aux;
    }
    catch(Fecha::Invalida e)
    {
        is.setstate(std::ios::failbit);
        throw e;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Fecha& F) noexcept
{
    os << F.cadena();
    return os;
}
