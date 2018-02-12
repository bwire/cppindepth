#include <iostream>
#include <functional>
#include <future>

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
    
    std::future<ret_type> ftrs[threads];
    
    ftrs[0] = std::async(std::launch::async, f, b, e, f1, f2);
    while (chunk != threads) {
        b = e;
        if (chunk == threads - 1)
            ftrs[chunk] = std::async(std::launch::async, f, b, q, f1, f2); 
        else {
            std::advance(e, chunk_size);
            ftrs[chunk] = std::async(std::launch::async, f, b, e, f1, f2); 
        }
        ++chunk;
    };
    
    for (size_t i = 0; i != threads; i++)
        ftrs[i].wait();
    
    auto result = ftrs[0].get();
    for (size_t i = 1; i != threads; i++)
        result = f2 (result, ftrs[i].get ());
    
    return result;
}
