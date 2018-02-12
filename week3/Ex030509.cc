// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    for (; p != q; p++)
    {
        if (n == 0) {
            return std::remove(p, q, *p);    
        }
        else 
            n--;
    }    
    return q;
}