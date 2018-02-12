template<int ... Types> struct IntList;

template<int H, int ... T> struct IntList<H, T...> {
    static int const Head = H;
    using Tail = IntList<T...>;
};

template<> struct IntList<> {};
