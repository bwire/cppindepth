#include <cstring>

struct String {
    String() = default;
    String(const char *str) {
        std::cout << "String(*)" << std::endl;
        size_ = strlen(str);
        data_ = new char[size_ + 1];
        strcpy(data_, str);
    }
    String(const String &other) : String(other.data_) {
        std::cout << "String(&)" << std::endl;
    }

    void swap(String &other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    String(String &&other) {
        std::cout << "String(&&)" << std::endl;
        swap(other);
    }

    String& operator=(String &&other) {
        std::cout << "operator=(&&)" << std::endl;
        swap(other);
        return *this;
    }

    String& operator=(const String &other) {
        std::cout << "operator=(&)" << std::endl;
        *this = String(other.data_);
        return *this;
    }

    String operator+(const String &other) const {
        std::cout << "operator+(&)" << std::endl;
        String s;
        s.size_ = size_ + other.size_ + 1;
        s.data_ = new char[s.size_];
        strcpy(s.data_, data_);
        strcpy(s.data_ + size_, other.data_);
        return s;
    }

    private:
        char *data_;
        size_t size_;
};
