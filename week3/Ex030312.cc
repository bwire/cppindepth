#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>


template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    void addImpl(const std::type_info& t1, const std::type_info& t2,  std::function<Result(Base*, Base*)> f)
    {
        map.emplace(std::pair<std::type_index, std::type_index>(std::type_index(t1), std::type_index(t2)), f);
    }

    bool hasImpl(Base * a, Base * b) const
    {
        auto it1 = map.find(std::pair<std::type_index, std::type_index>(std::type_index(typeid(*a)), std::type_index(typeid(*b))));
        if (Commutative) {
            auto it2 = map.find(std::pair<std::type_index, std::type_index>(std::type_index(typeid(*b)), std::type_index(typeid(*a))));
            return it1 != map.end() || it2 != map.end();
        } else
            return it1 != map.end();
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        auto it1 = map.find(std::pair<std::type_index, std::type_index>(std::type_index(typeid(*a)), std::type_index(typeid(*b))));
        if (Commutative) {
            if (it1 != map.end())
                return (it1 -> second)(a, b);
            else {
                auto it2 = map.find(std::pair<std::type_index, std::type_index>(std::type_index(typeid(*b)), std::type_index(typeid(*a))));
                return (it2 -> second)(b, a);
            }
            
        } else
            return (it1 -> second)(a, b);
    }
    
    private:
        bool commutative;
        std::map<std::pair<std::type_index, std::type_index>, std::function<Result(Base*, Base*)>> map;
};