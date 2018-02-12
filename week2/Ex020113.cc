#include <iostream>
#include <typeinfo>

void print_values(std::ostream & os) {}

// принимает произвольное число аргументов
template <typename T, typename... Args> void print_values(std::ostream& os, T val, Args... args) 
{
    os << typeid(val).name() << ": " << val << std::endl;
    print_values(os, args...);
}