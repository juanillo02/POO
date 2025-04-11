/*
Se desea implementar en C++ una clase para almacenar fragmentos de ADN. Esta clase se denominara ADN y su representacion interna estara basada
en dos atributos, un puntero, c, y un tamano, n. El atributo c apuntara a una zona de memoria dinamica creada con new que sera destruida con
delete tan pronto como deje de ser necesaria. Dicha zona contendra la secuencia de nucleotidos de una de las helices. El atributo n representara
la longitud de la secuencia y se permitira la existencia de secuencias vacıas, que tendran longitud 0. La clase ADN contendra un tipo enumerado,
Nucleotido, accesible publicamente, que estara formado por las constantes enumeradas A (adenina), C (citosina), G (guanina) y T (timina).
a) Defina dos constructores: uno predeterminado que cree un objeto ADN vacıo y otro que cree un objeto ADN a partir de una secuencia de
nucleotidos representada por dos parametros (un puntero y un tamano).
b) ¿Es necesario definir un operador de asignacion si queremos asignar objetos ADN con la semantica habitual que poseen los tipos primitivos?
Si lo es, hagalo.
c) Sobrecargue el operador de ́ındice para poder acceder a nucleotidos individuales de un objeto ADN, tanto en lectura como en escritura
(si no es constante), pero siempre con comprobacion de rango. Si el ́ındice no esta en el rango correcto se lanzara una excepcion de tipo
AccesoIndebido (declarada como una clase vacıa). Asegurese de especificar que puede aparecer dicha excepcion.
d) Sobrecargue el operador de suma para devolver la concatenacion de dos objetos ADN. Suponga que ha sido declarado como amigo.
e) Sobrecargue el operador de insercion para escribir un objeto ADN en un flujo de salida de manera que aparezca la secuencia de
iniciales de sus nucleotidos. Suponga que ha sido declarado como amigo.
f) ¿Que efecto tendrıa sobrecargar el operador de insercion internamente?
No podríamos usarlo con ostream de forma natural (cout << adn), ya que cout es externo a la clase y no puede acceder a private.
Por eso es mejor declararlo friend
*/
#include <iostream>
#include <utility>
class ADN
{
    public:
        enum Nucleotido {A, C, G, T};
        ADN(): c(nullptr), n{0} {}
        ADN(Nucleotido* c_, size_t n_);
        ADN& operator =(const ADN& a);
        class AccesoIndebido {};
        const Nucleotido& operator [](size_t i) const noexcept;
        Nucleotido& operator [](size_t i);
        friend ADN operator + (const ADN& A1, const ADN& A2);
        friend std::ostream& operator << (std::ostream& os, const ADN& A);
        ~ADN() {delete[] c;}
    private:
        Nucleotido* c;
        size_t n;
};

ADN::ADN(Nucleotido* c_, size_t n_): n{n_}
{
    if(n > 0)
    {
        for(size_t i = 0; i < n; i++)
        {
            c[i] = c_[i];
        }
    }
}

ADN& ADN::operator =(const ADN& a)
{
    if (this != &a)
    {
        ADN aux(a);
        std::swap(n, aux.n);
        std::swap(c, aux.c);
    }
    return *this;
}

const ADN::Nucleotido& ADN::operator [](size_t i) const noexcept
{
    if(i >= n)
    {
        throw AccesoIndebido();
    }
    else
    {
        return c[i];
    }
}

ADN::Nucleotido& ADN::operator [](size_t i)
{
    if(i >= n)
    {
        throw AccesoIndebido();
    }
    else
    {
        return c[i];
    }
}
ADN operator + (const ADN& A1, const ADN& A2)
{
    ADN aux;
    aux.n = A1.n + A2.n;
    aux.c = new ADN::Nucleotido[aux.n];
    for (size_t i = 0; i < A1.n; i++)
    {
        aux.c[i] = A1.c[i];
    }
    for (size_t i = 0; i < A2.n; i++)
    {
        aux.c[A1.n + i] = A2.c[i];
    }
    return aux;
}

std::ostream& operator << (std::ostream& os, const ADN& A)
{
    for (size_t i = 0; i < A.n; i++)
    {
        os << A.c[i];
    }
    return os;
}