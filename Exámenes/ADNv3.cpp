/*
Dado el siguiente esqueleto de una clase en C++ que representa una cadena de ADN:
Teniendo en cuenta de que es admisible la cadena vacía y haciendo siempre uso de los métodos std::copy_n() y std::fill_n(), sabiendo que:
- copy_n(): recibe iterador al origen del rango del que copiar, número de elementos a copiar e iterador al destino
- fill_n(): recibe iterador al origen del rango a rellenar, número de elementos a rellenar y valor a ser asignado.
Realiza:
a) Defina e implemente el constructor por defecto de la clase
b) Defina e implemente el constructor a partir de una única base con 4 elementos.
c) ¿Es necesario constructor de copia? Si es así defínelo e impleméntelo, si no, explica el por qué.
d) ¿Es necesario constructor por movimiento? Si es así defínelo e impleméntelo, si no, explica el por qué.
NOTA: TODOS LOS MÉTODOS SERÁN DEFINIDOS INTERNAMENTE E IMPLEMENTADOS EXTERNAMENTE A LA CLASE PROPORCIONADA.
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>

class ADN
{
    public:
        enum Base {G, A, C, T};
        ADN();
        ADN(Base* base);
        ADN(const ADN& a);
        ADN& operator=(const ADN& a);
        ADN(ADN&& a);
        ADN& operator=(ADN&& a);
        ~ADN();
        ADN operator +(const ADN& A);
        const Base& operator [](size_t i) const noexcept;
        Base& operator [](size_t i);
    private:
        size_t n;
        Base* b;
};

ADN::ADN(): n{0}, b{nullptr} {}

ADN::ADN(Base* base): n{1}, b{new Base[1]}
{
    std::fill_n(b, n, base);
}

// Si porque se utiliza memoria dinánima
ADN::ADN(const ADN& a): n{a.n}, b{new Base[a.n]}
{
    std::copy_n(a.b, a.n, b);
}

ADN& ADN::operator=(const ADN& a)
{
    if (this != &a)
    {
        std::swap(n, a.n);
        std::swap(b, a.b);
    }
    return *this;
}

ADN::ADN(ADN&& a): n{a.n}, b{a.b}
{
    a.n = 0;
    a.b = nullptr;
}

ADN& ADN::operator=(ADN&& a)
{
    if(this != &a)
    {
        std::swap(n, a.n);
        std::swap(b, a.b);
        if(a.n == 0)
        {
            delete[] a.b;
            a.b = nullptr;
            a.n = 0;
        }
    }
    return *this;
}

ADN::~ADN()
{
    delete[] b;
}

/*
Dada la clase ADN del ejercicio anterior:
a) Sobrecarga el operador + para que permita la concatenación de varias bases.
b) Sobrecarga el operador [] tanto const como no-const para que permita acceder al elemento de una base concreta dado un índice.
c) Sobrecarga el operador << para imprimir todos los componentes de un ADN, para ello haz uso de un objeto a función.
d) Lo mismo que el anterior, pero usando una función lambda o anónima.
*/

ADN ADN::operator +(const ADN& A)
{
    ADN aux;
    aux.n = A.n + n;
    aux.b = new Base[aux.n];
    std::copy_n(b, n, aux.b);
    std::copy_n(A.b, A.n, aux.b + n);
    return aux;
}

const ADN::Base& ADN::operator [](size_t i) const noexcept
{
    if(i < n)
    {
        return b[i];
    }
    else
    {
        throw std::out_of_range("Indice fuera de rango");
    }
}

ADN::Base& ADN::operator [](size_t i)
{
    if(i < n)
    {
        return b[i];
    }
    else
    {
        throw std::out_of_range("Indice fuera de rango");
    }
}

struct BaseToChar
{
    char operator()(ADN:: Base base) const
    {
        switch (base)
        {
        case ADN::G: return 'G';    break;
        case ADN::A: return 'A';    break;
        case ADN::C: return 'C';    break;
        case ADN::T: return 'T';    break;
        default: return '?';        break;
        }
    }
};

std::ostream& operator << (std::ostream& os, const ADN& A)
{
    BaseToChar Convertir;
    for(size_t i = 0; i < strlen(A); i++)
    {
        os << Convertir(A[i]);
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const ADN& A)
{
    auto Convertir = [](ADN::Base base)
    {
        switch (base)
        {
        case ADN::G: return 'G';    break;
        case ADN::A: return 'A';    break;
        case ADN::C: return 'C';    break;
        case ADN::T: return 'T';    break;
        default: return '?';        break;
        }
    };
    for(size_t i = 0; i < strlen(A); i++)
    {
        os << Convertir(A[i]);
    }
    return os;
}