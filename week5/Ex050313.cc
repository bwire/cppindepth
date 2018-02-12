#include <tuple>
#include <utility>
#include <iostream>

// list
template<int ... Types> struct IntList;

template<int H, int ... T> struct IntList<H, T...> {
    static int const Head = H;
    using Tail = IntList<T...>;
};

template<> struct IntList<> {};

// cons
template<int H, typename Ints> struct IntCons;

template<int H, int ... Ints> struct IntCons<H, IntList<Ints...>> {
    using type = IntList<H, Ints...>;
};

// concat
template<typename Ints1, typename Ints2> struct IntConcat;

template<int ... Ints1, int ... Ints2> 
struct IntConcat<IntList<Ints1...>, IntList<Ints2...>> {
    using type = IntList<Ints1..., Ints2...>;
};

// generate
template<int N> struct Generate {
    using type = typename IntConcat<typename Generate<N-1>::type, typename IntCons<N-1, IntList<>>::type>::type;
};

template<> struct Generate<0>{
    using type = IntList<>;
};

template<class F, typename ... Args, int ... I> auto apply(F f, std::tuple<Args...> t, IntList<I...>) ->
decltype (f(std::get<I>(t) ...))
{
    return f(std::get<I>(t) ...);
}


template<class F, typename ... Args> auto apply(F f, std::tuple<Args...> t) -> 
decltype (apply(f, t, typename Generate<sizeof...(Args)>::type())) 
{
    return apply(f, t, typename Generate<sizeof...(Args)>::type());
}