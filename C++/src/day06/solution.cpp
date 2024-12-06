#include "day06/solution.hpp"
#include "grid/direction.hpp"
#include <optional>
#include <unordered_map>
#include <vector>

namespace aoc
{
    std::optional<std::unordered_set<size_t>> num_positions_until_exit(
        const aoc::grid::Point &guard_start,
        const std::unordered_set<size_t> &obstacles,
        const aoc::grid::Point &map_size)
    {
        if (obstacles.find(guard_start.to_index(map_size.x)) != obstacles.end())
            throw std::runtime_error("Start :(");
        aoc::grid::Point cur_guard_pos = guard_start;
        aoc::grid::Direction guard_dir = aoc::grid::Direction::UP;

        std::unordered_set<size_t> visited;

        int moves = 0;
        while (cur_guard_pos.x >= 0 && cur_guard_pos.y >= 0 &&
               cur_guard_pos.x < map_size.x && cur_guard_pos.y < map_size.y)
        {
            auto pos_index = cur_guard_pos.to_index(map_size.x);

            // Record this position
            visited.insert(pos_index);

            // Turn 90 degrees until no obstacle
            while (obstacles.find(
                       (cur_guard_pos + guard_dir).to_index(map_size.x)) !=
                   obstacles.end())
                guard_dir = guard_dir + 2;

            // Proceed
            cur_guard_pos += guard_dir;

            // Cycle check (we could visit all cells from all directions in width * height * 4, so more than that
            // is a loop).
            ++moves;
            if (moves >
                map_size.x * map_size.y *
                    static_cast<int>(aoc::grid::Direction::CARDINALS.size()))
                return std::nullopt;
        }

        if (visited.size() == 0)
            throw std::runtime_error("Can't happen.");

        return visited;
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
                                        std::get<2>(input))
            ->size();
    }

    Day06::Solution2Type Day06::part2(const InputType &input)
    {
        auto guard_start = std::get<0>(input);
        auto obstacles = std::get<1>(input);
        size_t s = obstacles.size();
        auto size = std::get<2>(input);
        auto path = *num_positions_until_exit(guard_start, obstacles, size);

        std::unordered_set<size_t> visited;
        size_t loops_found = 0;
        for (auto &pos_idx : path)
        {
            if (visited.find(pos_idx) != visited.end())
                throw std::runtime_error("Broke hash set.");

            visited.insert(pos_idx);

            if (pos_idx == guard_start.to_index(size.x))
                continue;

            if (obstacles.find(pos_idx) != obstacles.end())
                throw std::runtime_error("Original path had obstacles...");

            obstacles.insert(pos_idx);
            if (!num_positions_until_exit(guard_start, obstacles, size))
                ++loops_found;

            obstacles.erase(pos_idx);
            if (obstacles.size() != s)
                throw std::runtime_error("foo.");
        }

        return loops_found;
    }
} // namespace aoc
