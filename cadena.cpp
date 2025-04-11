#include "cadena.hpp"
#include <cstring>
#include <utility>

char Cadena::vacia[1] = {'\0'};

Cadena::Cadena(size_t tam, char cad): tam_{tam}
{
    if(tam > 0)
    {
        s_ = new char[tam+1];
        for(size_t i = 0; i < tam_; i++)
        {
            s_[i] = cad;
        }
        s_[tam_] = '\0';
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(const char* cad): tam_{strlen(cad)}
{
    if(tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        strcpy(s_, cad);
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(const Cadena& C): tam_{C.tam_}
{
    if(tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        strcpy(s_, C.s_);
    }
    else
    {
        s_ = vacia;
    }
}

Cadena::Cadena(Cadena&& C): tam_{C.tam_}, s_{C.s_}
{
    C.tam_ = 1;
    C.s_ = new char[1];
    C.s_[0] = '\0';
}

char& Cadena::at(size_t i)
{
    if(i >= this->tam_)
    {
        throw std::out_of_range("Fuera del rango");
    }
    else
    {
        return this->s_[i];
    }
}

const char& Cadena::at(size_t i) const
{
    if(i >= tam_)
    {
        throw std::out_of_range("Fuera del rango");
    }
    else
    {
        return s_[i];
    }
}

Cadena Cadena::substr(size_t i, size_t tam) const
{
    if(i >= tam_ || tam_ - i < tam)
    {
        throw std::out_of_range("Fuera de rango");
    }
    else
    {
        Cadena devolver(tam);
        strncpy(devolver.s_, s_ + i, tam);
        devolver.s_[tam] = '\0';
        return devolver;
    }
}

Cadena& Cadena::operator =(const Cadena& C)
{
    if(*this != C)
    {
        Cadena copia(C);
        std::swap(tam_, copia.tam_);
        std::swap(s_, copia.s_);
    }
    return *this;
}

Cadena& Cadena::operator =(const char* cad)
{
    if(*this != cad)
    {
        Cadena copia(cad);
        std::swap(tam_, copia.tam_);
        std::swap(s_, copia.s_);
    }
    return *this;
}

Cadena& Cadena::operator =(Cadena&& C)
{
    if(*this != C)
    {
        Cadena copia(std::move(C));
        std::swap(tam_, copia.tam_);
        std::swap(s_, copia.s_);
    }
    C.tam_ = 1;
    C.s_ = new char[1];
    C.s_[0] = '\0';
    return *this;
}

Cadena& Cadena::operator +=(const Cadena& C)
{
    char* aux = new char[tam_ + C.tam_ + 1];
    std::strcpy(aux, s_);  
    std::strcat(aux, C.s_); 
    delete[] s_;
    s_ = aux;
    tam_ += C.tam_;
    return *this;
}

Cadena::~Cadena()
{
    if(tam_ > 0)
    {
        tam_ = 0;
        delete[] s_;
    }
}
        
bool operator ==(const Cadena& C1, const Cadena& C2)
{
    return (strcmp((const char*) C1, (const char*)C2) == 0);
}

bool operator !=(const Cadena& C1, const Cadena& C2)
{
    return !(C1 == C2);
}

bool operator <(const Cadena& C1, const Cadena& C2)
{
    return (strcmp((const char*) C1, (const char*) C2) < 0);
}

bool operator >(const Cadena& C1, const Cadena& C2)
{
    return !(C1 < C2) && !(C1 == C2);
}

bool operator <=(const Cadena& C1, const Cadena& C2)
{
    return C1 < C2 || C1 == C2;
}

bool operator >=(const Cadena& C1, const Cadena& C2)
{
    return C1 > C2 || C1 == C2;
}

Cadena operator + (const Cadena& C1, const Cadena& C2)
{
    Cadena aux(C1);
    return aux += C2;
}