#include <functional>

template<class F> bool find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return true;
    return false;
}
