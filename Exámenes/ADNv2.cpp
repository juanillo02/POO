/*
Se desea implementar en C++ una clase para almacenar fragmentos de ADN. Esta clase se denomina ADN y su representacion interna esta basada en dos
atributos: un puntero, c, y un tamano, n. El atributo c apuntara a una zona de memoria dinamica creada con new que sera destruida con delete tan
pronto como deje de ser necesaria. Dicha zona contendra la secuencia de nucleotidos de una de las helices. El atributo n representara la longitud
de la secuencia y se permitira la existencia de secuencias vacıas, que tendran longitud 0. Los nucleotidos se definen mediante un tipo enumerado,
Nucleotido, formado por las constantes enumeradas A (adenina), C (citosina), G (guanina) y T (timina), en dicho orden.
a) Defina externamente el constructor predeterminado para crear objetos ADN vacıos. No emplee asignaciones.
b) Defina externamente un constructor que cree un objeto ADN a partir de una secuencia de nucleotidos, ya creada con new, representada por dos
parametros: un puntero y un tamano. Utilice para los parametros identicos nombres a los indicados para los atributos.
No emplee asignaciones. Este constructor sera privado.
c) Defina externamente un constructor que cree un objeto ADN con la secuencia de nucleotidos correspondiente a una cadena de bajo nivel
de caracteres constantes, que recibira como unico parametro y que solo contendra caracteres ’A’, ’C’, ’G’ y ’T’.
d) ¿Es necesario definir un constructor de copia si queremos copiar objetos ADN con la semantica habitual que poseen los tipos primitivos?
¿Por que?
Si es necesario ya que el objeto que se copiaría acabaría apuntando a la misma zona de memoria, por lo que a la hora de modificar uno,
se modificaría el otro, al igual que al eliminar.
e) Sobrecargue externamente el operador de suma para devolver la concatenacion de dos objetos ADN. Suponga que ha sido declarado como amigo.
Utilice el constructor mas apropiado para crear el objeto temporal que devolvera como resultado, ası como la funcion memcpy() de la biblioteca
estandar (recuerde que posee tres par ́ametros: destino, origen y numero de bytes). No empleee bucles.
f) Reescriba el siguiente fragmento de codigo colocando explıcitamente las llamadas a los constructores implicados:
*/
#include <iostream>
#include <cstring>

class ADN
{
    public:
        enum Nucleotido {A, C, G, T};
        ADN();                                                  //A
        ADN(Nucleotido* c, size_t n);                           //B
        ADN(const char* c);                                     //C
        friend ADN operator +(const ADN& A1, const ADN& A2);    //D
    private:
        Nucleotido* c_;
        size_t n_;
};

ADN::ADN(): c_{nullptr}, n_{0} {}

ADN::ADN(Nucleotido* c, size_t n): c_{c}, n_{n} {}

ADN::ADN(const char* c): n_{strlen(c)}
{
    c_ = new Nucleotido[n_];
    for (size_t i = 0; i < n_; ++i)
    {
        switch (c[i])
        {
            case 'A': c_[i] = A; break;
            case 'C': c_[i] = C; break;
            case 'G': c_[i] = G; break;
            case 'T': c_[i] = T; break;
        }
    }
}

ADN operator +(const ADN& A1, const ADN& A2)
{
    ADN aux;
    aux.n_ = A1.n_ + A2.n_;
    aux.c_ = new ADN::Nucleotido[aux.n_];
    memcpy(aux.c_, A1.c_, A1.n_ * sizeof(ADN::Nucleotido));
    memcpy(aux.c_ + A1.n_, A2.c_, A2.n_ * sizeof(ADN::Nucleotido));
    return aux;
}

// F
const char* const s = "GA";
ADN a = ADN(s), b = ADN(a), C;
b[0] = C;
ADN(ADN(a + ADN("TTA")) + b).mostrar();