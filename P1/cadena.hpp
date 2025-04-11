#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <string>

class Cadena
{
public:
    explicit Cadena(size_t tam = 0, char cad = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena &C);
    Cadena(Cadena &&C);
    size_t length() const noexcept;
    char &operator[](size_t i);
    const char &operator[](size_t i) const;
    char &at(size_t i);
    const char &at(size_t i) const;
    Cadena substr(size_t i, size_t tam) const;
    Cadena &operator=(const Cadena &C);
    Cadena &operator=(const char *cad);
    Cadena &operator=(Cadena &&C);
    explicit operator const char *() const;
    Cadena &operator+=(const Cadena &C);
    ~Cadena();
    typedef char *iterator;
    typedef const char *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

private:
    static char vacia[1];
    size_t tam_;
    char *s_;
};

bool operator==(const Cadena &C1, const Cadena &C2);
bool operator!=(const Cadena &C1, const Cadena &C2);
bool operator<(const Cadena &C1, const Cadena &C2);
bool operator>(const Cadena &C1, const Cadena &C2);
bool operator<=(const Cadena &C1, const Cadena &C2);
bool operator>=(const Cadena &C1, const Cadena &C2);

Cadena operator+(const Cadena &C1, const Cadena &C2);

inline size_t Cadena::length() const noexcept { return tam_; }
inline char &Cadena::operator[](size_t i) { return s_[i]; }
inline const char &Cadena::operator[](size_t i) const { return s_[i]; }
inline Cadena::operator const char *() const { return s_; }

std::istream &operator>>(std::istream &is, Cadena &C);
std::ostream &operator<<(std::ostream &os, const Cadena &C) noexcept;

inline Cadena::iterator Cadena::begin() noexcept { return s_; }
inline Cadena::iterator Cadena::end() noexcept { return s_ + tam_; }
inline Cadena::const_iterator Cadena::begin() const noexcept { return const_iterator(s_); }
inline Cadena::const_iterator Cadena::end() const noexcept { return const_iterator(s_ + tam_); }
inline Cadena::const_iterator Cadena::cbegin() const noexcept { return const_iterator(begin()); }
inline Cadena::const_iterator Cadena::cend() const noexcept { return const_iterator(end()); }
inline Cadena::reverse_iterator Cadena::rbegin() noexcept { return reverse_iterator(end()); }
inline Cadena::reverse_iterator Cadena::rend() noexcept { return reverse_iterator(begin()); }
inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept { return const_reverse_iterator(cend()); }
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept { return const_reverse_iterator(cbegin()); }
inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept { return const_reverse_iterator(cend()); }
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept { return const_reverse_iterator(cbegin()); }

namespace std
{               // Estaremos dentro del espacio de nombres std.
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash<Cadena>
    {                                              // Es una clase con solo un operador público.
        size_t operator()(const Cadena &cad) const // El operador función.
        {
            hash<string> hs;             // Creamos un objeto hash de string.
            auto p{(const char *)(cad)}; // Convertimos cad a cadena de bajo nivel.
            string s{p};                 // Creamos un string desde la cadena de b. nivel .
            size_t res{hs(s)};           // El hash del string . Como hs.operator()(s);
            return res;                  // Devolvemos el hash del string .
            // En forma abreviada:
            // return hash<string>{}((const char*)(cad));
        }
    };
}

#endif // CADENA_HPP__
