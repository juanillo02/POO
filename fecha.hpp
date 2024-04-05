#ifndef FECHA_HPP
#define FECHA_HPP
#include <iostream>
#include <ctime>
#include <cstdio>
#include <iomanip>
#include <locale>

class Fecha
{
    public:
        //Constructores
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        Fecha(const Fecha& F) = default;
        Fecha(const char* cadena);
        //Metodos observadores
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
        int dia() const noexcept;
        int mes() const noexcept;
        int anno() const noexcept;
        //Operadores
        //Fecha& operator = (const Fecha& F) = default;
        Fecha& operator ++ ();
        Fecha& operator -- ();
        Fecha operator ++ (int);
        Fecha operator -- (int);
        Fecha operator + (int d) const;
        Fecha operator - (int d) const;
        Fecha& operator += (int d);
        Fecha& operator -= (int d);
        const char* cadena() const;
        //Destructor
        ~Fecha() = default;
        //Clase
        class Invalida
        {
            public:
                Invalida(const char* cad): inv(cad) {}
                const char* por_que() const;
            private:
                const char* inv;
        };
    private:
        int dia_, mes_, anno_;
        void valida() const;
        mutable char crep[35];
        mutable bool actual = false;
};
//Operadores logicos
bool operator == (const Fecha& F1, const Fecha& F2);
bool operator != (const Fecha& F1, const Fecha& F2);
bool operator > (const Fecha& F1, const Fecha& F2);
bool operator < (const Fecha& F1, const Fecha& F2);
bool operator >= (const Fecha& F1, const Fecha& F2);
bool operator <= (const Fecha& F1, const Fecha& F2);
//Operadores inline
inline const char* Fecha::Invalida::por_que() const {return inv;}
inline int Fecha::dia() const noexcept {return dia_;}
inline int Fecha::mes() const noexcept {return mes_;}
inline int Fecha::anno() const noexcept {return anno_;}
//Operadores de extraccion y de insercion
std::istream& operator >> (std::istream& is, Fecha& F);
std::ostream& operator << (std::ostream& os, const Fecha& F) noexcept;

#endif //FECHA_HPP