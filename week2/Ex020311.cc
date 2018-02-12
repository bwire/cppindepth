template<class F>
void for_each_int(int* p, int* q, F f)
{
    for (; p != q; ++p )
        f(*p);
}