/*
Observe el siguiente programa: Diga si funciona correctamente. En caso afirmativo indique lo que imprime. En caso negativo haga las
modificaciones necesarias para que funcione correctamente.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Libro
{
        char* titulo ;
        int paginas ;
    public:
        Libro() : titulo (new char[1]), paginas (0) { *titulo = 0; }
        Libro(const char* t, int p) : paginas (p)
        {
            titulo = new char[strlen(t) + 1];
            strcpy(titulo , t);
        }
        ~Libro() { delete [] titulo ; }
        void paginas(int p) { paginas = p; }
        int paginas_() const { return paginas ; }
        char* titulo_() const { return titulo ; }
};
void mostrar(const Libro& l)
{ cout << l.titulo_() << " tiene " << l.paginas_() << " p ́aginas" << endl; }
int main()
{
    Libro l1("Fundamentos de C++", 474),
    l2("Por Fin: C ISO", 224),
    l3;
    mostrar(l3);
    l3 = l1;
    mostrar(l1), mostrar(l2), mostrar(l3);
}

//L3 está vacío por lo que no mostrará nada, para que funcione correctamente hay que cambiar el nombre de la función