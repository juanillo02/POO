#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstring>
#include <iostream>

class Cadena
{
    public:
        //Constructores
        explicit Cadena(size_t tama = 0, char car = ' ');
        Cadena(const Cadena& C);
        Cadena(const char* cad);
        Cadena(Cadena&& cad);
        //Operadores
        Cadena& operator = (const Cadena& C);
        Cadena& operator = (const char* cad);
        Cadena& operator = (Cadena&& cad);
        explicit operator const char*() const;
        Cadena& operator += (const Cadena& C);
        //Metodos observadores
        size_t length() const noexcept;
        //Devolver caracter
        char& operator [] (size_t i);
        const char& operator[] (size_t i) const;
        char& at(size_t i);
        const char& at(size_t) const;
        //Excepción
        Cadena substr(size_t i, size_t taman) const;
        //Iteradores
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        //Funciones iteradores
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;
        //Destructor
        ~Cadena();
    private:
        static char vacia[1];
        size_t tam_;
        char* s_;
};

//Operador
Cadena operator + (const Cadena& C, const Cadena& B);

//Funciones inline
inline size_t Cadena::length() const noexcept {return tam_;}
inline Cadena::operator const char *() const {return s_;}
inline char& Cadena::operator [] (size_t i){return s_[i];}
inline const char& Cadena::operator [] (size_t i) const {return s_[i];}

//Operadores lógicos
bool operator == (const Cadena& C, const Cadena& B);
bool operator != (const Cadena& C, const Cadena& B);
bool operator >= (const Cadena& C, const Cadena& B);
bool operator <= (const Cadena& C, const Cadena& B);
bool operator > (const Cadena& C, const Cadena& B);
bool operator < (const Cadena& C, const Cadena& B);

//Operadores de insercion y extracion
std::istream& operator >> (std::istream& is, Cadena& C);
std::ostream& operator << (std::ostream& os, const Cadena& C) noexcept;

//Funciones iteradoras
inline Cadena::iterator Cadena::begin() noexcept {return s_;}
inline Cadena::iterator Cadena::end() noexcept {return s_ + tam_;}
inline Cadena::const_iterator Cadena::begin() const noexcept {return const_iterator(s_);}
inline Cadena::const_iterator Cadena::end() const noexcept {return const_iterator(s_ + tam_);}
inline Cadena::const_iterator Cadena::cbegin() const noexcept {return const_iterator(begin());}
inline Cadena::const_iterator Cadena::cend() const noexcept {return const_iterator(end());}
inline Cadena::reverse_iterator Cadena::rbegin() noexcept {return reverse_iterator(end());}
inline Cadena::reverse_iterator Cadena::rend() noexcept {return reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept {return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept {return const_reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept {return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept {return const_reverse_iterator(begin());}

#endif //CADENA_HPP