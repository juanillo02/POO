/*
Observe atentamente el siguiente programa: 
a) Escriba las lıneas que imprimirıa el programa.
b) Diga que anomalıa hay.
c) Corrıjala reescribiendo el metodo Objeto::lanzamiento() para que lance un objeto creado dinamicamente, o su direccion, y el capturador de
la excepcion en main().
*/
#include <iostream>
using namespace std;
class Objeto
{
    public:
    Objeto(char const *nombre): nombre (nombre)
    {
        cout << "Constructor de Objeto para " << nombre << endl;
    }
    ~Objeto()
    {
        cout << "Destructor de Objeto para " << nombre << endl;
    }
    void lanzamiento()
    {
        Objeto o("‘objeto local de lanzamiento()’");
        cout << "Metodo lanzamiento() para " << nombre << endl;
        throw &o;
    }
    void saludo()
    {
        cout << "Hola de parte de " << nombre << endl;
    }
    private:
        char const *nombre ;
};
int main()
{
    Objeto o("‘objeto de main()’");
    try {
        o.lanzamiento();
    }
    catch(Objeto *o) {
        cout << "Excepcion capturada" << endl;
        o->saludo();
    }
}

/*Apartado A
Constructor de objeto para 'objeto de main()'.
Constructor de objeto para 'objeto local de lanzamiento()'.
Metodo lanzamiento() para 'objeto de main()'.
Destructor de objeto para 'objeto local de lanzamiento()'.
Destructor de objeto para 'objeto de main()'.
Excepcion capturada
Apartado B
El problema está en la función lanzamiento que cuando termina el objeto local se destruye antes de ser
accedido al bloque catch produciendose un error.
Apartado C
void lanzamiento()
{
    Objeto o("‘objeto local de lanzamiento()’");
    cout << "Metodo lanzamiento() para " << nombre << endl;
    throw o;
}
*/