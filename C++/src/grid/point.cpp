#include "grid/point.hpp"
#include "grid/direction.hpp"

namespace aoc::grid
{
    Point::Point(int x, int y) : x(x), y(y)
    {
    }

    size_t Point::to_index(size_t width) const
    {
        return y * width + x;
    }


    Point &Point::operator+=(const Point &rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }

    Point aoc::grid::Point::operator+(const Point &rhs) const
    {
        return Point(x + rhs.x, y + rhs.y);
    }

    Point &Point::operator+=(const Direction &rhs)
    {
        this->x += rhs.dx();
        this->y += rhs.dy();

        return *this;
    }

    Point aoc::grid::Point::operator+(const Direction &rhs) const
    {
        return Point(x + rhs.dx(), y + rhs.dy());
    }

    Point &Point::operator-=(const Point &rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;

        return *this;
    }

    Point aoc::grid::Point::operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }

    Point Point::from_index(size_t index, size_t width)
    {
        return Point(static_cast<int>(index % width),
                     static_cast<int>(index / width));
    }
} // namespace aoc::grid