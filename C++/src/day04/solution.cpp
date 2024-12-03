#include "day04/solution.hpp"
#include "grid/direction.hpp"
#include "utility.hpp"

namespace aoc
{
    std::string get_string_from(const aoc::grid::ArrayView<char> &input,
                                const aoc::grid::Point &start,
                                const aoc::grid::Direction &dir,
                                size_t len)
    {
        std::string result;

        aoc::grid::Point cur(start);
        while (input.contains(cur) && result.size() < len)
        {
            result.push_back(input[cur]);
            cur += dir;
        }

        return result.size() == len ? result : "";
    }

    bool check_for_string_from(const aoc::grid::ArrayView<char> &input,
                               const aoc::grid::Point &start,
                               const aoc::grid::Direction &dir,
                               std::string to_find)
    {
        std::string str = get_string_from(input, start, dir, to_find.size());
        return str == to_find;
    }

    int count_occurences_in_grid(const aoc::grid::ArrayView<char> &input,
                                 const std::string &to_find)
    {
        int count = 0;

        // Find potential starts of string
        for (size_t i = 0; i < input.width() * input.height(); ++i)
        {
            if (input[i] != to_find[0])
                continue;

            auto location = aoc::grid::Point::from_index(i, input.width());

            for (auto &dir : aoc::grid::Direction::EIGHT_WAY)
            {
                if (check_for_string_from(input, location, dir, to_find))
                    ++count;
            }
        }

        return count;
    }

    int count_x_patterns_in_grid(const aoc::grid::ArrayView<char> &input,
                                 const std::string &to_find)
    {
        if (to_find.size() == 0 || to_find.size() % 2 == 0)
            throw std::runtime_error("X patterns can only occur with "
                                     "non-empty, odd-length strings.");

        int count = 0;
        size_t half_size = to_find.size() / 2;

        // Find potential centers of x-patterns
        for (size_t i = 0; i < input.width() * input.height(); ++i)
        {
            if (input[i] != to_find[half_size])
                continue;

            auto location = aoc::grid::Point::from_index(i, input.width());

            int find_count = 0;
            for (auto &dir : aoc::grid::Direction::DIAGONALS)
            {
                auto start = location + (dir.opposite() * half_size);
                auto str = get_string_from(input, start, dir, to_find.size());
                if (str == to_find)
                    ++find_count;
            }

            if (find_count >= 2)
                ++count;
        }

        return count;
    }

    Day04::Day04() : Day(4)
    {
    }

    Day04::InputType Day04::parse_input(std::ifstream &input_file)
    {
        return get_grid(input_file);
    }

    Day04::Solution1Type Day04::part1(const InputType &input)
    {
        return count_occurences_in_grid(input, "XMAS");
    }

    Day04::Solution2Type Day04::part2([[maybe_unused]] const InputType &input)
    {
        return count_x_patterns_in_grid(input, "MAS");
    }
} // namespace aoc
