#ifndef CADENA_HPP_
#define CADENA_HPP_
#include<iostream>

class Cadena
{
    public:
        explicit Cadena(size_t tam = 0, char cad = ' ');
        Cadena(const char* cad);
        Cadena(const Cadena& C);
        Cadena(Cadena&& C);
        size_t length() const noexcept;
        char& operator [](size_t i);
        const char& operator [](size_t i) const;
        char& at(size_t i);
        const char& at(size_t i) const;
        Cadena substr(size_t i, size_t tam) const;
        Cadena& operator =(const Cadena& C);
        Cadena& operator =(const char* cad);
        Cadena& operator =(Cadena&& C);
        explicit operator const char*() const;
        Cadena& operator +=(const Cadena& C);
        ~Cadena();
    private:
        static char vacia[1];
        size_t tam_;
        char* s_;
};

bool operator ==(const Cadena& C1, const Cadena& C2);
bool operator !=(const Cadena& C1, const Cadena& C2);
bool operator <(const Cadena& C1, const Cadena& C2);
bool operator >(const Cadena& C1, const Cadena& C2);
bool operator <=(const Cadena& C1, const Cadena& C2);
bool operator >=(const Cadena& C1, const Cadena& C2);

Cadena operator + (const Cadena& C1, const Cadena& C2);

inline size_t Cadena::length() const noexcept {return tam_;}
inline char& Cadena::operator [](size_t i) {return s_[i];}
inline const char& Cadena::operator [](size_t i) const {return s_[i];}
inline Cadena::operator const char*() const {return s_;}

#endif //CADENA_HPP_