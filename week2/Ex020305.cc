// определение структуры Point уже подключено
struct Point
{
    constexpr Point(double x, double y) 
        : x(x), y(y) 
    {}

    double x = 0;
    double y = 0;
};

// сложение
constexpr Point operator+(const Point& fst, const Point& snd)
{
    return Point(fst.x + snd.x, fst.y + snd.y);
}

// вычитание
constexpr Point operator-(const Point& fst, const Point& snd)
{
    return Point(fst.x - snd.x, fst.y - snd.y);
}

// скалярное произведение
constexpr Point operator*(const Point& fst, const Point& snd)
{
    return Point(fst.x * snd.x, fst.y * snd.y);
}