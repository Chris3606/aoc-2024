#include "grid/direction.hpp"
#include "utility.hpp"

namespace aoc::grid
{
    const Direction Direction::UP = Direction(Direction::Type::UP, 0, -1);
    const Direction Direction::UP_RIGHT =
        Direction(Direction::Type::UP_RIGHT, 1, -1);
    const Direction Direction::RIGHT = Direction(Direction::Type::RIGHT, 1, 0);
    const Direction Direction::DOWN_RIGHT =
        Direction(Direction::Type::DOWN_RIGHT, 1, 1);
    const Direction Direction::DOWN = Direction(Direction::Type::DOWN, 0, 1);
    const Direction Direction::DOWN_LEFT =
        Direction(Direction::Type::DOWN_LEFT, -1, 1);
    const Direction Direction::LEFT = Direction(Direction::Type::LEFT, -1, 0);
    const Direction Direction::UP_LEFT =
        Direction(Direction::Type::UP_LEFT, -1, -1);
    const Direction Direction::NONE = Direction(Direction::Type::NONE, 0, 0);

    static std::array<Direction::Type, 8> valid_dirs{
        Direction::Type::UP,
        Direction::Type::UP_RIGHT,
        Direction::Type::RIGHT,
        Direction::Type::DOWN_RIGHT,
        Direction::Type::DOWN,
        Direction::Type::DOWN_LEFT,
        Direction::Type::LEFT,
        Direction::Type::UP_LEFT,
    };

    const std::array<Direction, 4> Direction::CARDINALS{UP, RIGHT, DOWN, LEFT};
    const std::array<Direction, 4> Direction::DIAGONALS{UP_RIGHT,
                                                        DOWN_RIGHT,
                                                        DOWN_LEFT,
                                                        UP_LEFT};
    const std::array<Direction, 8> Direction::EIGHT_WAY{UP,
                                                        UP_RIGHT,
                                                        RIGHT,
                                                        DOWN_RIGHT,
                                                        DOWN,
                                                        DOWN_LEFT,
                                                        LEFT,
                                                        UP_LEFT};

    Direction::Direction(Type type, int dx, int dy)
        : m_type(type), m_dx(dx), m_dy(dy)
    {
    }

    int Direction::dx() const
    {
        return m_dx;
    }

    int Direction::dy() const
    {
        return m_dy;
    }

    Direction::Type Direction::type() const
    {
        return m_type;
    }

    bool Direction::operator==(const Direction &rhs) const
    {
        return type() == rhs.type();
    }

    Direction Direction::operator+(int rhs) const
    {
        if (*this == NONE)
            return NONE;

        return from_type(
            valid_dirs[aoc::wrap_around((int)type() + rhs - 1,
                                        static_cast<int>(valid_dirs.size()))]);
    }

    Direction Direction::operator-(int rhs) const
    {
        if (*this == NONE)
            return NONE;

        return from_type(
            valid_dirs[aoc::wrap_around((int)type() - rhs - 1,
                                        static_cast<int>(valid_dirs.size()))]);
    }

    Point Direction::operator*(int rhs) const
    {
        return Point(dx() * rhs, dy() * rhs);
    }

    Direction Direction::opposite() const
    {
        return *this + 4;
    }

    const Direction &Direction::from_type(Type type)
    {
        switch (type)
        {
        case Direction::Type::NONE:
            return Direction::NONE;
        case Direction::Type::UP:
            return Direction::UP;
        case Direction::Type::UP_RIGHT:
            return Direction::UP_RIGHT;
        case Direction::Type::RIGHT:
            return Direction::RIGHT;
        case Direction::Type::DOWN_RIGHT:
            return Direction::DOWN_RIGHT;
        case Direction::Type::DOWN:
            return Direction::DOWN;
        case Direction::Type::DOWN_LEFT:
            return Direction::DOWN_LEFT;
        case Direction::Type::LEFT:
            return Direction::LEFT;
        case Direction::Type::UP_LEFT:
            return Direction::UP_LEFT;
        }
    }
} // namespace aoc::grid