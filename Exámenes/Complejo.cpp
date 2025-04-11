/* Supongamos una clase en C++ para operar con números complejos:*/
#include <iostream>
#include <utility>

using namespace std;
class Complejo
{
    public:
        Complejo(double real = 0, double imaginario = 0): r{real}, i{imaginario} {}
        Complejo(const Complejo& C): r{C.r}, i{C.i} {}
        Complejo& operator =(const Complejo& C);
        Complejo& operator =(double real);
        double real() const noexcept {return r;}
        double imag() const noexcept {return i;}
        double& real() {return r;}
        double& imag() {return i;}
        Complejo operator - ();
    private:
        double r, i; //parte real, parte imaginaria
};

Complejo& Complejo::operator =(const Complejo& C)
{
    if(this != &C)
    {
        Complejo aux(C);
        swap(r, aux.r);
        swap(i, aux.i);
    }
    return *this;
}

Complejo& Complejo::operator =(double real)
{
    if(this->r != real)
    {
        Complejo aux(real);
        swap(r, aux.r);
        swap(i, aux.i);
    }
    return *this;
}

Complejo operator * (const Complejo& C1, const Complejo& C2)
{
    return Complejo(C1.real() * C2.real() - C1.imag() * C2.imag(), C1.real() * C2.imag() + C1.imag() * C2.real());
}

Complejo Complejo::operator - ()
{
    return Complejo(-r, -i);
}


Complejo operator + (const Complejo& C1, const Complejo& C2)
{
    return Complejo(C1.real() + C2.real(), C1.imag() + C2.imag());
};

bool operator == (const Complejo& C1, const Complejo& C2)
{
    return (C1.real() == C2.real()) && (C1.imag() == C2.imag());
}

bool operator != (const Complejo& C1, const Complejo& C2)
{
    return !(C1 == C2);
}
/*No te lo pide el ejercicio, solo para comprobar*/
ostream& operator<<(ostream& os, const Complejo& C)
{
    os << "(" << C.real();
    if (C.imag() >= 0)
        os << " + " << C.imag() << "i)";
    else
        os << " - " << -C.imag() << "i)";
    
    return os;
}
/*a) Defina los mínimos miembros imprescindibles para que las siguientes líneas de código se compilen y ejecuten correctamente y
explique por qué no se necesitan otros.
b) Complete la clase complejo con las declaraciones y definiciones de las funciones mínimas necesarias, ya sea como miembros de la clase o
como funciones externas según convenga para que el siguiente programa se ejecute sin errores:*/
int main()
{
    Complejo v(1.); //Apartado a)
    Complejo w; //Apartado a)
    Complejo x(2, -1.2); //Apartado a)
    Complejo y(x); //Apartado a)
    Complejo z = y; //Apartado a)
    Complejo i1 = -1; //Apartado a)
    x = -3.5; //Apartado a)
    cout << v << ", " << w << ", " << x << ", " << y << ", " << z << ", " << i1 << endl; //Comprobar
    Complejo i, i2, z, y; //Apartado b)
    i.real() = 0; //Apartado b)
    i.imag() = 1; //Apartado b)
    cout << i << endl; //Comprobar
    i2 = i * i; //Apartado b)
    cout << i2 << endl; //Comprobar
    if ( i2 == Complejo(-1.0)) cout << "OK\n"; //Apartado b)
    if ( i2 != -1.0) cout << "MAL\n"; //Apartado b)
    z = y = Complejo(2.5, 1); //Apartado b)
    cout << z << ", " << y << endl; //Comprobar
    y.imag() = -y.imag(); //Apartado b)
    cout << y << endl; //Comprobar
    if ( z + y == 2 * z.real()) cout << "OK\n"; //Apartado b)
    else cout << "MAL\n"; //Apartado b)
    if ( z + -y != Complejo(0,2 * z.imag())) cout << "MAL\n"; //Apartado b)
    else cout << "OK\n"; //Apartado b)
    return 0;
}