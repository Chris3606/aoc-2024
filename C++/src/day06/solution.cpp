#include "day06/solution.hpp"
#include "grid/direction.hpp"
#include <unordered_map>
#include <vector>

namespace aoc
{
    int num_positions_until_exit(const aoc::grid::Point &guard_start,
                                 const std::unordered_set<size_t> &obstacles,
                                 const aoc::grid::Point &map_size)
    {
        aoc::grid::Point cur_guard_pos = guard_start;
        aoc::grid::Direction guard_dir = aoc::grid::Direction::UP;

        std::unordered_map<size_t, std::vector<aoc::grid::Direction>> visited;

        while (cur_guard_pos.x >= 0 && cur_guard_pos.y >= 0 &&
               cur_guard_pos.x < map_size.x && cur_guard_pos.y < map_size.y)
        {
            // If the guard has already visited this position, we've created a loop and will never exit
            // TODO: Check vector
            if (visited.find(cur_guard_pos.to_index(map_size.x)) !=
                visited.end())
                return -1;

            // Record this position
            visited.insert(cur_guard_pos.to_index(map_size.x));

            // Turn 90 degrees until no obstacle
            while (obstacles.find(
                       (cur_guard_pos + guard_dir).to_index(map_size.x)) !=
                   obstacles.end())
                guard_dir = guard_dir + 2;

            // Proceed
            cur_guard_pos += guard_dir;
        }

        return static_cast<int>(visited.size());
    }

    Day06::Day06() : Day(6)
    {
    }

    Day06::InputType Day06::parse_input(std::ifstream &input_file)
    {
        size_t width = 0;
        int y = 0;
        std::string line;

        // Want to use unordered set of point but haven't implemented hashing yet...
        std::unordered_set<size_t> obstacles;
        aoc::grid::Point guard_start;

        while (std::getline(input_file, line))
        {
            width = line.size();
            for (size_t x = 0; x < line.size(); ++x)
            {
                switch (line[x])
                {
                case '#':
                    obstacles.insert(
                        aoc::grid::Point(x, y).to_index(line.size()));
                    break;
                case '^':
                    guard_start = aoc::grid::Point(x, y);
                    break;
                }
            }
            ++y;
        }

        return InputType(std::move(guard_start),
                         std::move(obstacles),
                         aoc::grid::Point(static_cast<int>(width), y));
    }

    Day06::Solution1Type Day06::part1(const InputType &input)
    {
        return num_positions_until_exit(std::get<0>(input),
                                        std::get<1>(input),
                                        std::get<2>(input));
    }

    Day06::Solution2Type Day06::part2([[maybe_unused]] const InputType &input)
    {
        return "Not yet solved.";
    }
} // namespace aoc
