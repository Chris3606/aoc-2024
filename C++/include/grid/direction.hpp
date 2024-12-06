#pragma once
#include "grid/point.hpp"
#include <array>

namespace aoc::grid
{
    struct Direction
    {

    public:
        enum class Type
        {
            NONE = 0,
            UP,
            UP_RIGHT,
            RIGHT,
            DOWN_RIGHT,
            DOWN,
            DOWN_LEFT,
            LEFT,
            UP_LEFT,
        };

        static const Direction UP;
        static const Direction UP_RIGHT;
        static const Direction RIGHT;
        static const Direction DOWN_RIGHT;
        static const Direction DOWN;
        static const Direction DOWN_LEFT;
        static const Direction LEFT;
        static const Direction UP_LEFT;
        static const Direction NONE;

        static const std::array<Direction, 4> CARDINALS;
        static const std::array<Direction, 4> DIAGONALS;
        static const std::array<Direction, 8> EIGHT_WAY;

        int dx() const;
        int dy() const;
        Type type() const;

        bool operator==(const Direction &rhs) const;
        Direction operator+(int rhs) const;
        Direction operator-(int rhs) const;
        Point operator*(int rhs) const;

        Direction opposite() const;

        static const Direction &from_type(Type type);

    private:
        Direction(Type type, int dx, int dy);
        Direction();

        Type m_type;
        int m_dx;
        int m_dy;
    };
} // namespace aoc::grid