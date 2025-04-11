/*Dadas las siguientes clases, responda si es posible realizar las siguientes operaciones.*/
#include <iostream>
/*
class A{};   
class B{
    B (int a, char* m = "", int n = 0);
    B& operator = (const B& x);
    operator A()const;
};
*/

class A {};

class B {
    public:
        // Constructor por defecto
        B() : a_(0), m_(""), n_(0) {}
        // Constructor con parámetros
        B(int a, const char* m = "", int n = 0) : a_(a), m_(m), n_(n) {}
        // Constructor de copia
        B(const B& x) : a_(x.a_), m_(x.m_), n_(x.n_) {}
        // Constructor desde A
        B(const A&) : a_(0), m_("from A"), n_(0) {}
        // Operador de asignación
        B& operator=(const B& x) {
            if (this != &x) {
                a_ = x.a_;
                m_ = x.m_;
                n_ = x.n_;
            }
            return *this;
        }
        // Conversión implícita a A
        operator A() const {return A();}
    private:
        int a_;
        const char* m_;
        int n_;
};

int main()
{
    A a1;               //Si, ya que la clase A no tiene ningún constructor definidor por el usuario, se llamará al constructor predefinido.
    B b1(5);            //Si, se llamará al constructor de conversión int -> B, equivalente a B (5,””,0).
    B* p = new B[10];   //No, la clase B no tiene operador por defecto. O bien se implementa este, o se les asigna un valor a cada elemento con {}.
    B* p = new B(10);   //Si, se genera un objeto B mediante memoria dinámica.
    B b2 = b1;          //No, ya que al utilizar memoria dinámica no se copiaría solo el valor de la memoria, no se copiaría el puntero.
    b2 = b1;            //Si, ya que está definido el operador de asignación
    A(b2);              //Si, Conversión implícita B → A vía operator A().
    B(a1);              //No, No hay constructor en B que acepte un A.
}