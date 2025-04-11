#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>

class Fecha
{
    public:
        explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
        Fecha(const Fecha& F) = default;
        Fecha(const char* fec);
        Fecha& operator = (const Fecha& F) = default;
        int dia() const noexcept;
        int mes() const noexcept;
        int anno() const noexcept;
        Fecha& operator++();
        Fecha& operator--();
        Fecha operator++(int);
        Fecha operator--(int);
        Fecha operator +(int d) const;
        Fecha operator -(int d) const;
        Fecha& operator +=(int d);
        Fecha& operator -=(int d);
        const char* cadena() const;
        static const int AnnoMaximo = 2037;
        static const int AnnoMinimo = 1902;
        class Invalida
        {
            public:
                Invalida(const char* inva): inv{inva} {}
                const char* por_que() const {return inv;}
            private:
                const char* inv;
        };
    private:
        int dia_, mes_, anno_;
        void valida();
        mutable char crep[35];
        mutable bool actual = false;
};

bool operator == (const Fecha& F1, const Fecha& F2);
bool operator != (const Fecha& F1, const Fecha& F2);
bool operator > (const Fecha& F1, const Fecha& F2);
bool operator < (const Fecha& F1, const Fecha& F2);
bool operator >= (const Fecha& F1, const Fecha& F2);
bool operator <= (const Fecha& F1, const Fecha& F2);

inline int Fecha::dia() const noexcept {return dia_;}
inline int Fecha::mes() const noexcept {return mes_;}
inline int Fecha::anno() const noexcept {return anno_;}

std::istream& operator >> (std::istream& is, Fecha& F);
std::ostream& operator <<  (std::ostream& os, const Fecha& F) noexcept;

#endif //FECHA_HPP_