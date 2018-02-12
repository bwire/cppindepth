#include <cstddef>
#include <string>

using std::size_t;

struct Unit  
{
    public:
        explicit Unit(size_t id) : id_(id) {}
        size_t id() const { return id_; }

    private:
        size_t id_;
};

struct Animal : virtual Unit
{
    public: 
        Animal(std::string const & name, size_t id) : name_(name), Unit(id) {}
        std::string const& name() const { return name_; }
    
    private:
        std::string name_;
};


// класс для человека
struct Man : virtual Unit
{
    explicit Man(size_t id) : Unit(id) {}
};

// класс для медведя
struct Bear : Animal
{
    explicit Bear(size_t id) : Animal("bear", id), Unit(id) {}
};

// класс для свиньи
struct Pig : Animal
{
    explicit Pig(size_t id) : Animal("pig", id), Unit(id) {}
};


// класс для челмедведосвина
struct ManBearPig : Man, Bear, Pig
{
    ManBearPig(size_t id) : Unit(id), Man(id), Bear(id), Pig(id) {}
};