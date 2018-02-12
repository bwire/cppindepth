template<int ... Types> struct IntList;

template<int H, int ... T> struct IntList<H, T...> {
    static int const Head = H;
    using Tail = IntList<T...>;
};

template<> struct IntList<> {};

template<typename IL> struct Length {
    static int const value = 1 + Length<typename IL::Tail>::value;
};

template<> struct Length<IntList<>> {
    static int const value = 0;    
};