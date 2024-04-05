#include "cadena.hpp"

char Cadena::vacia[1] = {'\0'};

Cadena::Cadena(size_t tama, char car): tam_(tama)
{
    if (tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        for(size_t i = 0; i < tam_; i++)
        {
            s_[i] = car;
        }
        s_[tam_] = '\0';
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(const Cadena& C): tam_(C.tam_)
{
    if (C.tam_ > 0)
    {
        s_ = new char[C.tam_ + 1];
        strcpy(s_, C.s_);
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(const char* cad): tam_(strlen(cad))
{
    if (tam_ > 0)
    {
        s_ = new char[strlen(cad) + 1];
        strcpy(s_, cad);
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(Cadena&& cad): tam_(cad.tam_), s_(cad.s_)
{
    cad.tam_ = 0;
    cad.s_ = new char[1];
    cad.s_ = vacia;
}

Cadena& Cadena::operator = (const Cadena& C)
{
    if(this  != &C)
    {
        if (tam_ > 0)
        {
            delete[] s_;
        }
        tam_ = C.tam_;
        if (tam_ > 0)
        {
            s_ = new char[C.tam_ + 1];
            strcpy(s_, C.s_);
        }
        else
        {
            s_ = vacia;
        }
    }
    return *this;
}


Cadena& Cadena::operator = (Cadena&& cad)
{
    if(this != &cad)
    {
        if (tam_ > 0)
        {
            delete[] s_;
        }
        tam_ = cad.tam_;
        if (tam_ > 0)
        {
            s_ = cad.s_;
            cad.tam_ = 0;
            cad.s_ = new char[1];
            cad.s_ = vacia;
        }
        else
        {
            s_ = vacia;
        }
    }
    return *this;
}

Cadena& Cadena::operator = (const char* cad)
{
    if(this->s_ != cad)
    {
        if (tam_ > 0)
        {
            delete[] s_;
        }
        tam_ = strlen(cad);
        if (tam_ > 0)
        {
            s_ = new char[tam_ + 1];
            strcpy(s_, cad);
        }
        else
        {
            s_ = vacia;
        }
    }
    return *this;
}

Cadena& Cadena::operator += (const Cadena& C)
{
    char* aux;
    if (tam_ > 0)
    {
        aux = new char[tam_ + 1];
        strcpy(aux, s_);
        delete[] s_;
    }
    tam_ = tam_ + C.tam_;
    if (tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        strcpy(s_, aux);
        strcat(s_, C.s_);
        delete[] aux;
    }
    else
    {
        strcat(s_, vacia);
        delete[] aux;
    } 
    
    return *this;
}

Cadena operator+(const Cadena& C, const Cadena& B)
{
    Cadena aux(C);
    return aux += B;
}


bool operator == (const Cadena& C, const Cadena& B)
{
    return (strcmp( (const char*) C, (const char*) B) == 0);
}

bool operator != (const Cadena& C, const Cadena& B)
{
    return !(C == B);
}

bool operator >= (const Cadena& C, const Cadena& B)
{
    return (C == B || C > B);
    
}

bool operator <= (const Cadena& C, const Cadena& B)
{
    return (C < B || C == B);
}

bool operator > (const Cadena& C, const Cadena& B)
{
    return !(C <= B);
}

bool operator < (const Cadena& C, const Cadena& B)
{
    if(strcmp( (const char*) C, (const char*) B) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char& Cadena::at(size_t i)
{
    if (i < this->tam_)
    {
        return this->s_[i];
    }
    else
    {
        throw std::out_of_range("Indice fuera de rango");
    }
}

const char& Cadena::at(size_t n) const
{
    if(n < tam_)
    {
        return s_[n];
    }else{
        throw std::out_of_range("En la función at el valor introducido es incorrecto");
    }
}

Cadena Cadena::substr(size_t i, size_t taman) const
{
    if (i <= tam_ && tam_ - i >= taman)
    {
        Cadena devolver(taman);
        strncpy(devolver.s_, s_ + i, taman);
        devolver.s_[taman] = '\0';
        return devolver;
    }
    else
    {
        throw std::out_of_range("Indice fuera de rango");
    }
}

Cadena::~Cadena()
{
    if(tam_ > 0)
    {
        tam_ = 0;
        delete[] s_;
    }
}

std::istream& operator >> (std::istream& is, Cadena& C)
{
    char lon[33] = "";
    is.width(33);
    is >> lon;
    C = lon;
    return is;
}

std::ostream& operator << (std::ostream& os, const Cadena& C) noexcept
{
    os << (const char*) C;
    return os;
}
