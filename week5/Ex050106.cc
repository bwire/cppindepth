#include <iostream>
#include <functional>
#include <thread>

template <typename I, class U, class B> auto map_reduce(I p, I q, U f1, B f2, size_t threads) -> decltype(f1(*p)) {
    
    using ret_type = decltype(f1(*p));
    
    auto dist = std::distance(p, q);
    size_t chunk_size = dist / threads;
    
    size_t chunk = 1; 
    I b = p, e = p;
    std::advance(e, chunk_size);
    
    auto f = [] (I b, I e, U f1, B f2) {
        auto res = f1(*b);
        while(++b != e)
            res = f2(res, f1(*b));
        return res;    
    };
    
    ret_type result, resTemp;
    std::thread t([&result, f, b, e, f1, f2]() { result = f(b, e, f1, f2); });
    t.join();
    
    while (chunk != threads) {
        b = e;
        if (chunk == threads - 1) {
            std::thread ta([&resTemp, f, b, q, f1, f2] { resTemp = f(b, q, f1, f2); });
            ta.join();
        }
        else {
            std::advance(e, chunk_size);
            std::thread ta([&resTemp, f, b, e, f1, f2] { resTemp = f(b, e, f1, f2); });
            ta.join();
        }
        result = f2 (result, resTemp);
        ++chunk;
    };

    return result;
}