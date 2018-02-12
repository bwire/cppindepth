#include <tuple>

template <std::size_t I1, std::size_t I2, class... Types> auto to_pair(std::tuple<Types...>& t) -> 
decltype(std::make_pair(std::get<I1>(t), std::get<I2>(t)))
{
    return std::make_pair(std::get<I1>(t), std::get<I2>(t));
}