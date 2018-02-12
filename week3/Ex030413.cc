#include <vector>
#include <list>
#include <iterator>
#include <iostream>

template <class T> class VectorList
{
    public:
        VectorList() = default;
        
        bool empty() const { return size() == 0; } 

        std::size_t size() const 
        {
            std::size_t sz = 0;
            for (auto it = data_.begin(); it != data_.end(); it++)  
                sz += (*it).size();
            return sz;
        }
        
        template <class It> void append(It p, It q) {
            if (p != q)
                data_.push_back(VectT(p, q));
        } 
        
        struct const_iterator : std::iterator<std::bidirectional_iterator_tag, T const> {
            using ptr = const std::list<std::vector<T>>*;
            using lit = typename std::list<std::vector<T>>::const_iterator;
            using vit = typename std::vector<T>::const_iterator;
            
            ptr ptr_;
            lit l_it;
            vit v_it;
      
            const_iterator() = default;
            const_iterator(const const_iterator&) = default;
            const_iterator(ptr pt, lit li, vit vi) : ptr_(pt), l_it(li), v_it(vi) {}
            const_iterator& operator=(const const_iterator&) = default;
            ~const_iterator() = default;
            const T& operator*() const { return *v_it; }
            const T* operator->() const { return &(*v_it); }
            const_iterator& operator++() { 
                increment();
                return *this;
            }
            const_iterator operator++(int) { 
                auto t = *this;
                increment();
                return t;
            }
            const_iterator& operator--() { 
                decrement();
                return *this;
            }
            const_iterator operator--(int) { 
                auto t = *this;
                decrement();
                return t;
            }
            bool operator == (const_iterator &it) const { 
                return (l_it == it.l_it && v_it == it.v_it); 
            }
            
            bool operator != (const const_iterator &it) const { 
                return (l_it != it.l_it && v_it != it.v_it); 
            }
                
            private:
                void increment() {
                    if (l_it != (*ptr_).end()) {
                        if (v_it != (*l_it).end())
                            ++v_it;
                            if (v_it == (*l_it).end()) {
                                ++l_it;
                                if (l_it != (*ptr_).end()) 
                                    v_it = (*l_it).begin();    
                            }
                    }
                }
                void decrement() {
                    if (l_it == (*ptr_).end()) {
                        --l_it;
                        v_it = (*l_it).end();
                        --v_it;
                    } else
                        if (v_it != (*l_it).begin()) 
                            --v_it;
                        else {
                            if (l_it != (*ptr_).begin()) {
                                --l_it;
                                v_it = (*l_it).end();
                                --v_it;
                            }
                        }
                }
        };
    
        const_iterator begin() const { 
            return const_iterator(&data_, data_.begin(), (*data_.begin()).begin());
        }
        const_iterator end() const {
            auto lit = data_.end();
            --lit;
            auto vit = (*lit).end();
            return const_iterator(&data_, lit, vit);
        }
        
    struct const_reverse_iterator : std::iterator<std::bidirectional_iterator_tag, T const> {
            using ptr = const std::list<std::vector<T>>*;
            using lit = typename std::list<std::vector<T>>::const_reverse_iterator;
            using vit = typename std::vector<T>::const_reverse_iterator;
            using it = typename const_iterator::const_iterator;
        
            ptr ptr_;
            lit l_it;
            vit v_it;
        
            const_reverse_iterator() = default;
            const_reverse_iterator(const const_iterator& ci) : ptr_(ci.ptr_), l_it(ci.l_it), v_it(ci.v_it) {};
            const_reverse_iterator(ptr pt, lit li, vit vi) : ptr_(pt), l_it(li), v_it(vi) {}
            const_reverse_iterator& operator=(const const_reverse_iterator&) = default;
            ~const_reverse_iterator() = default;
            const T& operator*() const { return *v_it; }
            const T* operator->() const { return &(*v_it); }
            const_reverse_iterator& operator++() { 
                increment();
                return *this;
            }
            const_reverse_iterator operator++(int) { 
                auto t = *this;
                increment();
                return t;
            }
            const_reverse_iterator& operator--() { 
                decrement();
                return *this;
            }
            const_reverse_iterator operator--(int) { 
                auto t = *this;
                decrement();
                return t;
            }
            bool operator == (const_reverse_iterator &it) const { 
                return (l_it == it.l_it && v_it == it.v_it); 
            }
            
            bool operator != (const const_reverse_iterator &it) const { 
                return (l_it != it.l_it && v_it != it.v_it); 
            }
            
            const_iterator base() const {
                return const_iterator(ptr_, l_it.base(), v_it.base());
            }
        
            private:
                void increment() {
                    if (!(l_it == (*ptr_).rend() && v_it == (*l_it).rend())) {
                        if (v_it == (*l_it).rend()) {
                            ++l_it;
                            v_it = (*l_it).rbegin();
                        } else
                            ++v_it;
                    }    
                }
                void decrement() {
                    if (!(l_it == (*ptr_).rbegin() && v_it == (*l_it).rbegin())) {
                        if (v_it == (*l_it).rbegin()) {
                            --l_it;
                            v_it = (*l_it).rend();
                        } else
                            --v_it;
                    }    
                }
        };
    
        const_reverse_iterator rbegin() const { 
            return const_reverse_iterator(&data_, data_.rbegin(), (*data_.rbegin()).rbegin());
        }
        const_reverse_iterator rend() const { 
            return const_reverse_iterator(&data_, data_.rend(), (*data_.rend()).rend());
        }
        
  
    private:
        using VectT  = std::vector<T>;
        using ListT = std::list<VectT>;
        using value_type = T;
        
        ListT data_;
};