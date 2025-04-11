/*Se dispone de la clase Fecha siguiente: */
#include <iostream>
#include <ctime>
#include <locale>
class Fecha
{
    public:
        class Invalida { //clase de excepción
            public:
                Invalida (const char*);
                const char* por_que() const;
            private:
                const char* razón;
        };
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        Fecha(const char* c);
        int dia () const noexcept;
        int mes () const noexcept;
        int anno () const noexcept;
        // ...
    private:
        int dia_, mes_, anio_;
};
/*El constructor inicializa una Fecha tomando los parámetros en el orden día, mes, año. Si un parámetro es 0, se toma el valor correspondiente
de la fecha del sistema. En caso de que el valor de algún parámetro no sea válido el constructor lanza una excepción Fecha::Invalida,
cuya razón se puede obtener con el método fecha::Invalida::por_que().
a) Implementa un constructor de conversión desde cadena de caracteres en el formato ”dd/mm/aaaa”, siendo dd y mm el día y el mes,
respectivamente, expresados con 1 ó 2 dígitos, y aaaa los 4 dígitos del año. Se lanzara una excepción
Fecha::Invalida si la cadena nos se ajusta al formato correcto.*/
Fecha::Fecha(const char* c)
{
    int fecha = sscanf(c, "%d/%d/%d", &dia_, &mes_, &anio_);
    if(fecha != 3)
    {
        throw Invalida("Formato de fecha incorrecto.");
    }
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if(dia_ == 0)
        {
            dia_ = tiempo_descompuesto->tm_mday;
        }
        if(mes_ == 0)
        {
            mes_ = tiempo_descompuesto->tm_mon + 1;
        }
        if(anio_ == 0)
        {
            anio_ = tiempo_descompuesto->tm_year + 1900;
        }
    }
}