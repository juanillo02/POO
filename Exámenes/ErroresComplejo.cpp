/*
Determina los errores que produce el siguiente codigo, indicando el tipo (de compilacion o ejecucion), la lınea en la que esta, la causa por la
que se produce y una posible solucion.
#include <iostream>
#include <cmath>
using namespace std;
class Complejo
{
        double real, imag;
    public:
        explicit Complejo (double r = 0., double i = 0.): real(r), i(imag) {}
        Complejo (const Complejo& c) {this = c;}
        static void print() { cout << "(" << real << "," << imag << ")"; }
        operator double() const { return sqrt(real * real + imag * imag); }
};
Complejo operator +(const Complejo& c1, const Complejo& c2)
{
    c1.real += c2.real, c1.imag += c2.imag;
    return Complejo(c1.real, c1.imag);
}
Complejo& operator -(Complejo c1, Complejo c2)
{
    c1.real -= c2.real, c1.imag -= c2.imag;
    return Complejo(c1.real, c1.imag);
}
const Complejo operator *(Complejo& c1, Complejo& c2)
{
    return Complejo(c1.real * c2.real - c1.imag * c2.imag,
    c1.real * c2.imag + c2.real * c1.imag);
}
int main()
{
    Complejo a(3.), b(2., 2.), c = a + b, d = b + 3.;
    double e = 3. + b;
    cout << "a * b = ", (a * b).print();
}
*/
#include <iostream>
#include <cmath>
using namespace std;
class Complejo
{
        double real, imag;
    public:
        explicit Complejo (double r = 0., double i = 0.): real(r), imag(i) {} //error de compilacion i(imag)
        Complejo (const Complejo& c): real{c.real}, imag{c.imag} {} //error de compilacion this = c
        void print() const { cout << "(" << real << "," << imag << ")"; } //error de compilacion static
        operator double() const { return sqrt(real * real + imag * imag); }
        friend Complejo operator +(const Complejo& c1, const Complejo& c2);
        friend Complejo operator -(Complejo c1, Complejo c2);
        friend const Complejo operator *(const Complejo& c1, const Complejo& c2);
        friend Complejo operator+(const Complejo& c, double r);
};
Complejo operator +(const Complejo& c1, const Complejo& c2)     //Error de compilacion, no estaba declarado como clase amiga, por lo que no podrá
{                                                               //acceder a su parte privada
    return Complejo(c1.real + c2.real, c1.imag + c2.imag);      //Al ser c1 const no se puede modificar
}
Complejo operator -(Complejo c1, Complejo c2)                   //Error de compilacion y ejecucion, devuelve una referencia a un objeto temporal
{                                                               //Por lo que produce un comportamiento indefinido.
    c1.real -= c2.real, c1.imag -= c2.imag;
    return Complejo(c1.real, c1.imag);
}
const Complejo operator *(const Complejo& c1, const Complejo& c2)   //Error de complacion, los objetos no pueden ser referencias no constantes.
{
    return Complejo(c1.real * c2.real - c1.imag * c2.imag,
    c1.real * c2.imag + c2.real * c1.imag);
}

Complejo operator+(const Complejo& c, double r) {
    return Complejo(c.real + r, c.imag);
}
int main()
{
    Complejo a(3.), b(2., 2.), c = a + b, d = b + 3.;           //Error de compilacion, operator + esta para complejo + complejo, no double + complejo
    double e = 3. + b;
    cout << "a * b = "; (a * b).print();                        //Error de compilacion, hay que poner ; en vez de , al no ser un miembro estático
}