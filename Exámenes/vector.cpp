/*
Sea una case vector para almacenar secuencias de numeros de coma flotante y doble precision. La longitud de un objeto Vector se establecerá en
el momento de la construccion y permanecer· fija hasta el momento de su destruccion.
*/
#include<iostream>

class Vector
{
    public:
        Vector(size_t tam = 0, double val = 0.0);
        Vector(std::initializer_list<double> l);
        Vector(const Vector& V);
        Vector(Vector&& V);
        double& at(size_t posicion);
        double at(size_t posicion) const;
        ~Vector();
    private:
        size_t n;
        double* datos;
};

Vector::Vector( size_t tam, double val): n{tam}
{
    datos = new double[n];
    for(size_t i = 0; i < n; i++)
    {
        *(datos + i) = val;
    }
}

Vector::Vector(std::initializer_list<double> l): n{l.size()}
{
    datos = new double[n + 1];
    auto it = l.begin();
    for(size_t i = 0; i < n && it != l.end(); i++, it++)
    {
        *(datos + i) = *it;
    }
}

Vector::Vector(const Vector& V): n{V.n}
{
    datos = new double[n];
    for(size_t i = 0; i < n; i++)
    {
        *(datos + i) = *(V.datos + i);
    }
}

Vector::Vector(Vector&& V): n{V.n}
{
    datos = new double[n];
    for(size_t i = 0; i < n; i++)
    {
        *(datos + i) = *(V.datos + i);
    }
    V.n = 0;
    V.datos = nullptr;
}

double& Vector::at(size_t posicion)
{
    if(posicion < 0 || posicion >= n)
    {
        throw std::out_of_range("Indice fuera de rango");
    }
    else
    {
        return *(datos + posicion);
    }
}

double Vector::at(size_t posicion) const
{
    if(posicion < 0 || posicion >= n)
    {
        throw std::out_of_range("Indice fuera de rango");
    }
    else
    {
        return *(datos + posicion);
    }
}

Vector::~Vector()
{
    delete[] datos;
}

/*
Complete la clase Vector con la declaracion de los metodos necesarios para que las siguientes instrucciones proporcionen los resultados descritos
en los comentarios y explique por quÈ se producen los dos errores.
Defina los metodos declarados en el apartado anterior.
*/
int main()
{
    Vector v1(5, 1.2); //v1 = {1.2, 1.2, 1.2, 1.2, 1.2}
    Vector v2(4); //v2={0, 0, 0, 0}
    Vector v3; //error de compilacion
    Vector v4=3; //error de compilacion
    Vector v5={1,2.5,3}; //v5={1,2.5,3}
}

/*
¿Es Valido el comportamiento del destructor por defecto? En caso afirmativo explique por que, en caso contrario 
implemente el metodo.
No es valido, ya que debemos destruir la memoria a la que apunta nuestro puntero a datos, para poder eliminar completamente nuestros objetos
debemos sobreescribir el destructor de nuestra clase.
*/
/*
Repita el apartado anterior para el constructor de Copia.
Ya que la clase trabaja con memoria dinámica y direcciones de memoria, para realizar una copia debemos de copiar las posiciones de memoria a las
que apunta nuestro puntero de datos al nuevo objeto, el constructor de copia predeterminado copiaría únicamente el puntero.
Repita el apartado anterior para el constructor de Movimiento
*/

/*
Implemente el metodo Vector::at( ) para que el siguiente fragmento de codigo se ejecute correctamente
*/
int main()
{
    const Vector v6={1,2,3,4,5,6};   
    Vector v7(6);   
    try{   
        v7.at(0)=v6.at(9);   
    }catch (std::out_of_range& e){   
        std::cout << e.what() << std::endl;   
    }
    return 0;
}