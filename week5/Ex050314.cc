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
