#include <string>
#include <sstream>
#include <exception>
#include <iostream>

class bad_from_string : public std::exception {
    public:
        bad_from_string() = default;
        bad_from_string(const char* msg) {};
};

template<class T> T from_string(std::string const& s)
{
    T result;
    std::istringstream iss(s);
    
    try {
        iss >> std::noskipws >> result;
    }
    catch (...) {
        throw bad_from_string();    
    }
    
    bool isError = false;
    
    if (iss.fail()) 
        isError = true;
    else {
        iss.get();
        if (!iss.eof())
            isError = true;
    }
    
    if (isError)    
        throw bad_from_string();
        
    return result;
}