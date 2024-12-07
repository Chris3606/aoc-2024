#pragma once
#include <cstddef>

namespace aoc::grid
{
    struct Direction;

    struct Point
    {
    public:
        Point();
        Point(int x, int y);

        size_t to_index(size_t width) const;
        Point &operator+=(const Point &rhs);
        Point operator+(const Point &rhs) const;
        Point &operator+=(const Direction &rhs);
        Point operator+(const Direction &rhs) const;
        Point &operator-=(const Point &rhs);
        Point operator-(const Point &rhs) const;

        static Point from_index(size_t index, size_t width);

        int x;
        int y;
    };
} // namespace aoc::grid