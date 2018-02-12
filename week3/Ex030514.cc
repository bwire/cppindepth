#include <algorithm>
#include <map>
#include <iostream>

template<class Iterator> size_t count_permutations(Iterator p, Iterator q) {
    
    std::size_t res = 0;
    std::map<Iterator, int> m;
    std::size_t idx = 1;
    
    for (Iterator ptr = p; ptr != q; ptr++) {
        bool found = false;
        for (auto it = m.begin(); it != m.end(); it++) {
            if (*(it->first) == *ptr) {
                found = true;
                m[ptr] = it->second;
                break;
            }             
        }
        if (!found) {
            m[ptr] = idx++;
        }
    }
    std::vector<int> v;
    for (auto it = m.begin(); it != m.end(); it++)
        v.push_back(it->second);
    
    std::cout << v.size() << std::endl;
    
    do {
        if (std::adjacent_find(v.begin(), v.end()) == v.end())
            ++res;    
    } while (std::next_permutation(v.begin(), v.end()));
        
    return res;
}