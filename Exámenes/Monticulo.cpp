/*
Se quiere implementar en C++ una clase llamada “montículo” que represente un árbol binario parcialmente ordenado de mínimos de tipo double.
Su estructura consistirá en un único atributo privado no estático “m” que será un vector de la STL. A continuación, se le proporciona todas las
operaciones de la STL que deberá usar para manejar el montículo:
a. std::make_heap(): Recibe dos iteradores, principio y final, y construye un montículo.
b. std::insert(): Recibe dos iteradores, principio y final, y un elemento “x”, flotando el elemento hasta que el árbol quede reorganizado.
c. std::erase(): Recibe un elemento “x”, hundiendo el elemento hasta que el árbol quede reorganizado.
Entonces, realiza, definiendo externamente a la clase, los métodos siguientes:
a) Define la clase, incluyendo las cabeceras de los métodos posteriores.
b) Un constructor que construya un montículo vacío.
c) Un constructor que construya un montículo dado un vector.
d) Un método insertar, que inserte un elemento en el árbol.
e) Un método eliminar, que elimine un elemento.
f) Un método que devuelva una referencia constante al vector.
g) Sobrecargue el operador << para que imprima los elementos del montículo.
*/
#include <iostream>
#include <vector>
#include <algorithm>

class monticulo
{
    public:
        monticulo();
        monticulo(std::vector<double> m);
        void insertar(double x);
        void eliminar(double x);
        const std::vector<double>& getVector() const;
        friend std::ostream& operator << (std::ostream& os, const monticulo& m);
    private:
        std::vector<double> m_;
};

monticulo::monticulo(): m_{} {}

monticulo::monticulo(std::vector<double> m)
{
    std::make_heap(m.begin(), m.end());
}

void monticulo::insertar(double x)
{
    m_.insert(m_.begin(), x);
}

void monticulo::eliminar(double x)
{
    for (auto i = m_.begin(); i != m_.end(); ++i)
    {
        if (*i == x)
        {
            m_.erase(i);
            break;
        }
    }
}

const std::vector<double>& monticulo::getVector() const
{
    return m_;
}

std::ostream& operator << (std::ostream& os, const monticulo& m)
{
    for (double val : m.m_) {
        os << val << " ";
    }
    return os;
}

int main()
{
    // Creamos un montículo con algunos elementos
    monticulo m;
    m.insertar(10);
    m.insertar(20);
    m.insertar(5);
    m.insertar(15);

    std::cout << "Montículo: " << m << std::endl;

    // Eliminamos un elemento del montículo
    m.eliminar(10);
    std::cout << "Montículo después de eliminar 10: " << m << std::endl;

    return 0;
}