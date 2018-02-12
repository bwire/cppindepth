#include <utility> // для std::move и std::forward
#include <functional>

// реализация функции apply
template <typename F, typename ... Args> auto apply(F f, Args&&... args) ->
decltype (f(std::forward<Args>(args)...))
{
    
    return f(std::forward<Args>(args)...);
}