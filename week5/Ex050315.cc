#include <iostream>
#include <functional>

using namespace std;

template<int a, int b>
struct Plus
{
    static int const value = a + b;    
};

template<int ... Types> struct IntList;

template<int H, int ... T> struct IntList<H, T...> {
    static int const Head = H;
    using Tail = IntList<T...>;
};

template<> struct IntList<> {};

// cons
template<int H, typename Ints> struct IntCons;

template<typename IL1, typename IL2, template <int, int> class BF> struct Zip;

template<int H1, int ... T1, int H2, int ... T2, template <int, int> class BF> 
struct Zip<IntList<H1, T1...>, IntList<H2, T2...>, BF> {
    using type = typename IntCons<BF<H1, H2>::value, typename Zip<IntList<T1...>, IntList<T2...>, BF>::type>::type;    
};

template<template <int, int> class BF> 
struct Zip<IntList<>, IntList<>, BF> {
    using type = IntList<>;    
};

template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

template<typename D> class Quantity;

template<int ... Ints> class Quantity<IntList<Ints...>> {
    
    public:
        Quantity() { _val = 0; }
        explicit Quantity(double val) : _val(val) {}
        
        double value() const { return _val; }
        
        const Quantity<IntList<Ints...>> operator+(const Quantity<IntList<Ints...>>& rv) const {
            return Quantity<IntList<Ints...>>(_val + rv.value());        
        }
        
        const Quantity<IntList<Ints...>> operator-(const Quantity<IntList<Ints...>>& rv) const {
            return Quantity<IntList<Ints...>>(_val - rv.value());        
        }
        
        template<int ... IntsRV> auto operator* (const Quantity<IntList<IntsRV...>>& rv) const ->
        decltype (Quantity<typename Zip<IntList<Ints...>, IntList<IntsRV...>, Multiply>::type>(rv.value())) {
            return Quantity<typename Zip<IntList<Ints...>, IntList<IntsRV...>, Multiply>::type>(_val * rv.value());        
        }
        
        template<int ... IntsRV> auto operator/ (const Quantity<IntList<IntsRV...>>& rv) const ->
        decltype (Quantity<typename Zip<IntList<Ints...>, IntList<IntsRV...>, Divide>::type>(rv.value())) {
            return Quantity<typename Zip<IntList<Ints...>, IntList<IntsRV...>, Divide>::type>(_val / rv.value());        
        }
        
    private:
        double _val;
        
};

using NumberQ   = Quantity<Dimension<>>;          // число без размерности
using LengthQ   = Quantity<Dimension<1>>;          // метры
using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах
