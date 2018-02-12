template<int ... Types> struct IntList;

template<int H, int ... T> struct IntList<H, T...> {
    static int const Head = H;
    using Tail = IntList<T...>;
};

template<> struct IntList<> {};


template<int H, typename Ints> struct IntCons;

template<int H, int ... Ints> struct IntCons<H, IntList<Ints...>> {
    using type = IntList<H, Ints...>;
};



template<typename Ints1, typename Ints2> struct IntConcat;

template<int ... Ints1, int ... Ints2> 
struct IntConcat<IntList<Ints1...>, IntList<Ints2...>> {
    using type = IntList<Ints1..., Ints2...>;
};


template<int N> struct Generate {
    using type = typename IntConcat<typename Generate<N-1>::type, typename IntCons<N-1, IntList<>>::type>::type;
};

template<> struct Generate<0>{
    using type = IntList<>;
};


