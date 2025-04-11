/*
Una matriz dispersa es aquella en la que la mayoría de las posiciones están vacías o almacenan elementos nulos. En lugar de almacenar la matriz
en un espacio proporcional a su tamaño, se puede conseguir una reducción de espacio considerable almacenándola en un espacio proporcional al
número de valores no nulos.
Un objeto de la clase MatrizDispersa representa una matriz bidimensional dispersa de valores de tipo double, la mayoría de los cuales son 0.
Una matriz tiene tres atributos, las dos dimensiones (m y n) y un vector (val) en el que se guardan los valores que no son 0 junto a sus
coordenadas -en cada posición del vecrtor se encuentra una terna (f, c, v) donde v es el valor correspondiente a la fila f y columna c de la
matriz. Las ternas se almacenan en orden creciente de filas y columnas.
La clase MatrizDispersa deberá proporcionar métodos públicos para realizar al menos las siguientes operaciones:
- Crear una matriz nula de dimensiones dadas, por omision 1x1. No se permitirán conversiones implícitas.
- asignar(): asignar un nuevo valor en una posición dada de la matriz.
- valor(): leer el valor de una posición dada.
- filas(), columnas() y n_valores(): obtener las dimensiones de la matriz y el número de valores distintos de 0, respectivamente.
Se inluirá, así mismo, el siguiente método privado:
- buscar(): comprobar y devolver si una posición de la matriz contiene un valor distinto de 0 (true) o no (false). Si es distinto de 0, además
devuelve por parámetro de salida el índice de este elemento dentro del vector val; en caso contrario, devuelve por dicho parámetro el índice del
siguiente valor distinto de 0 o n_valores() si tal índice no existe.
1. Completa la siguiente definición de la clase MatrizDispersa escribiendo únicamente las declaraciones de los miembros requeridos según la
especificación anterior.
2. Define una sobrecarga del operador < para comparar dos objetos de tipo terna: t1 < t2 si y solo si t1 precede a t2 siguiendo el orden creciente
de filas y columnas. A continuación, utiliza este operador para implementar el método privado buscar.
3. Define en el exterior de la clase MatrizDispersa los metodos publicos declarados anteriormente, siguiendo estas pautas:
- En las funciones que lo requieran se debera validar que las coordenadas estan dentro del rango de las dimensiones de la matriz y lanzar una
excepcion del tipo out_of_range si no es asi.
- Utiliza los metodos insert y erase de la clase vector. El primero recibe dos parametros, una posicion dada por un iterador y el elemento a
insertar. El segundo solo recibe un iterador que indica la posicion del elemento a suprimir.
Ejemplos:
vector<int> v{1, 3, 5, 7, 9};
v.erase(v.begin());         // v = {3, 5, 7, 9}
v.erase(v.begin()+3);       // v = {3, 5, 7}
v.erase(v.end()-1);         // v = {3, 5}
v.insert(v.begin(), 2)      // v = {2, 3, 5}
v.insert(v.begin()+2, 4)    // v = {2, 3, 4, 5}
- Todo el codigo se debe escribir tan claro y conciso como sea posible, evitando el uso innecesario de variables, asignaciones u otras
instrucciones.
4. Incorpora a MatrizDispersa un metodo para construir una matriz a partir de una lista de inicializadores de tipo terna dados en cualquier orden,
la cual incluira al final el elemento de la fila y columna ultimas, tenga el valor 0 o no. Las dimensiones de la matriz se deduciran de esta
ultima terna de la lista, que no se almacenara si su valor es 0. Trata de reutilizar la operacion asignar. Por ejemplo, la matriz del ejemplo
inicial se podra construir como sigue:
MatrizDispersa A { {0, 1, 7.5}, {2, 0, 18.2}, {2, 2, 86.37}, {3, 3, 10.25}, {4, 2, 61.05}, {4, 3, 0.0} };
5. Escribe un fragmento de codigo en el que se intente crear la matriz dispersa A y seguidamente actualizar el valor A(8, 6) a 0. Se deben
capturar las posibles excepciones lanzadas e imprimir un mensaje explicativo por el flujo de salida estandar de error.
                0,0     7,5     0,0     0,0
                0,0     0,0     0,0     0,0
           A =  18,2    0,0     86,37   0,0
                0,0     0,0     0,0     10,25
                0,0     0,0     61,05   0,0
6. Implementa el destructor de la clase MatrizDispersa, salvo que pienses que no es necesario, en cuyo caso explica la causa.
7. Implementa una eficiente funcion no miembro para intercambiar dos matrices dispersas evitando las copias de objetos. Añade a la clase
MatrizDispersa cualquier metodo que consideres necesario y no este definido.
8. Escribe la declaracion de una sobrecarga del metodo valor que permita tanto leer como actualizar el valor de una posicion dada de la matriz.
Explica si podria causar algun problema incluir este metodo en la clase MatrizDispersa y, en tal caso, pon un ejemplo.
*/
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class MatrizDispersa
{
    public:
        struct terna{
            size_t f, c;
            double v;
        };
        MatrizDispersa(size_t m_ = 1, size_t n_ = 1);
        MatrizDispersa(std::initializer_list<terna> l);
        void asignar(size_t f, size_t c, double v);
        double valor(size_t f, size_t c) const;
        double& valor(size_t f, size_t c);
        size_t filas() const noexcept;
        size_t columnas() const noexcept;
        size_t n_valores() const noexcept;
        friend void intercambiar(MatrizDispersa& A, MatrizDispersa& B);
    private:
        
        size_t m, n;
        std::vector<terna> val;
        bool buscar(size_t f, size_t c, size_t& i) const;
};

MatrizDispersa::MatrizDispersa(size_t m_ = 1, size_t n_ = 1): m{m_}, n{n_} {}

MatrizDispersa::MatrizDispersa(std::initializer_list<terna> l)
{
    for (const auto& t : l)
    {
        asignar(t.f, t.c, t.v);
    }
}
void MatrizDispersa::asignar(size_t f, size_t c, double v)
{
    if(f > m || c > n)
    {
        throw std::out_of_range("Fuera de rango");
    }
    else
    {
        size_t i;
        if(buscar(f, c, i))
        {
            val[i].v = v;
        }
        else
        {
            val.insert(val.begin() + i, {f, c, v});
        }
    }
}

double MatrizDispersa::valor(size_t f, size_t c) const
{
    if(f > m || c > n)
    {
        throw std::out_of_range("Fuera de rango");
    }
    else
    {
        size_t i;
        if(buscar(f, c, i))
        {
            return val[i].v;
        }
        else
        {
            return 0;
        }
    }
}

double& MatrizDispersa::valor(size_t f, size_t c)
{
    if(f > m || c > n)
    {
        throw std::out_of_range("Fuera de rango");
    }
    else
    {
        size_t i;
        if(buscar(f, c, i))
        {
            return val[i].v;
        }
        else
        {
            auto it = val.insert(val.begin() + i, {f, c, 0.0});  // Inserta en la posición i
            return it->v;  // Accedemos al valor insertado usando el iterador
        }
    }
}

inline size_t MatrizDispersa::filas() const noexcept {return m;}
inline size_t MatrizDispersa::columnas() const noexcept {return n;}
inline size_t MatrizDispersa::n_valores() const noexcept {return val.size();}

bool MatrizDispersa::buscar(size_t f, size_t c, size_t& i) const
{
    for(i = 0; i != val.size(); ++i)
    {
        if(val[i].f == f && val[i].c == c)
        {
            if(val[i].v != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    i = val.size();
    return false;
}

bool operator < (const MatrizDispersa::terna& t1, const MatrizDispersa::terna& t2)
{
    if(t1.f == t2.f)
    {
        return t1.c < t2.c;
    }
    else
    {
        return t1.f < t2.f;
    }
}

void intercambiar(MatrizDispersa& A, MatrizDispersa& B)
{
    std::swap(A.m, B.m);
    std::swap(A.n, B.n);
    std::swap(A.val, B.val);
}

int main() {
    try {
        // Crear la matriz dispersa A con los valores iniciales
        MatrizDispersa A{
            {0, 0, 7.5}, 
            {2, 0, 18.2}, 
            {2, 2, 86.37}, 
            {3, 3, 10.25}, 
            {4, 2, 61.05}, 
            {4, 3, 0.0} // No se incluye la última terna con valor 0
        };

        // Intentar asignar un valor a una posición fuera de los límites de la matriz (8, 6)
        A.asignar(8, 6, 0);  // Esto debería lanzar una excepción

    } catch (const std::out_of_range& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }
}

/*No es necesario implementar el destructor, siendo gestionada la memoria automáticamente por std::vector*/