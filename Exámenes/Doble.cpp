/*
Defina una clase de nombre doble con un unico atributo, privado y no estatico, de tipo double para que el siguiente programa se compile y se
ejecute sin errores. Para resolver el ejercicio no esta permitida la sobrecarga de operadores aritmeticos, de asignacion ni de insercion en flujo
de salida, asi como tampoco el uso de funciones amigas.
*/
#include <iostream>

class doble
{
    public:
        doble(double num): d_(num) {}
        operator double() const { return d_; }
    private:
        double d_;
};
int main()
{
    double a = 1.5, b = 10.5;
    doble c = 5.25,
          d = c;
    std::cout << c / d * b + b * c - c * c / b + b / c << std::endl; // 65
    d = a = b += c;
    std::cout << d << ' ' << a << ' ' << b << ' ' << c << std::endl; // 15,75 15,75 15,75 5,25
}