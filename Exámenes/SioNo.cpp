/*Considere las siguientes declaraciones, independientes de las definiciones asociadas:*/
class A {
    public:
        A& operator = (const B& b); //Línea 7
};
class B
{
    public:
        B(int i, const char* s = "", int j = 0);
        B() : B(0, "", 0) {} //Línea 4
        B(const char* c); //Línea 5
        B& operator = (const B& b);
        B& operator = (const A& a);
        operator A() const;
};
/*Diga si cada línea del siguiente fragmento de código es o no correcta (con un SI o un NO) y explica en una única frase el porque.
Simplemente debe decir que se ejecuta de cada clase, si es correcto, o qué le faltaría a las clases A y B para que se pudiera
ejecutar, en caso contrario. Suponga que en cada línea se han ejecutado correctamente las anteriores.*/
A a1, a2; //Si, ya que se crea con el constructor por defecto.
B b1 = 0; //Si, ya que utiliza los valores por defecto siendo i = 0 (siendo este el unico sin ser por defecto que es pasado al constructor), s = "" y j = 0.
B* p = new B(10); //Si, ya que utiliza los valores por defecto siendo i = 10 (siendo este el unico sin ser por defecto que es pasado al constructor), s = "" y j = 0.
B* q = new B[10]; //No, ya que no hay un construcor B sin parámetros, habría que hacer un constructor sin parámetros o añadir B()/B{}.
B b2 = "examen"; //No, ya que no hay un constructor de conversión de B(const char*).
A a3(b1); //Se ejecuta B::operator A(), que se convierte en un objeto de la clase A, pudiendo hacer el constructor de copia por defecto de A.
a2 = a1 = *q; //No, ya que *q es un tipo B y no hay una operación de conversión, para que funcione hace falta un constructor de conversión de B a A o realizar un operator = (const B&).
B b3 = a2; //Si, ya que se utiliza la operación B& operator = (const A& a).