#include "day08/solution.hpp"
#include "utility.hpp"
#include <unordered_set>

namespace aoc
{
    Day08::Day08() : Day(8)
    {
    }

    Day08::InputType Day08::parse_input(std::ifstream &input_file)
    {
        auto grid = get_grid(input_file);
        std::unordered_map<char, std::vector<aoc::grid::Point>> antennas;

        for (size_t y = 0; y < grid.height(); ++y)
        {
            for (size_t x = 0; x < grid.width(); ++x)
            {
                aoc::grid::Point p(static_cast<int>(x), static_cast<int>(y));
                if (grid[p] == '.')
                    continue;

                if (antennas.find(grid[p]) == antennas.end())
                    antennas[grid[p]] = std::vector<aoc::grid::Point>();

                antennas[grid[p]].push_back(p);
            }
        }

        return InputType(std::move(antennas),
                         aoc::grid::Point(static_cast<int>(grid.width()),
                                          static_cast<int>(grid.height())));
    }

    Day08::Solution1Type Day08::part1(const InputType &input)
    {
        std::unordered_set<size_t> antinode_positions;
        for (auto &antenna_pair : input.first)
        {
            for (size_t i = 0; i < antenna_pair.second.size(); ++i)
                for (size_t j = i + 1; j < antenna_pair.second.size(); ++j)
                {
                    // Calculate slope between pair
                    aoc::grid::Point slope(
                        antenna_pair.second[j].x - antenna_pair.second[i].x,
                        antenna_pair.second[j].y - antenna_pair.second[i].y);

                    // An antinode would appear at either end of the line between them, basically along both the slope and the
                    // inverse
                    aoc::grid::Point antinode = antenna_pair.second[j] + slope;
                    if (antinode.x >= 0 && antinode.y >= 0 &&
                        antinode.x < input.second.x &&
                        antinode.y < input.second.y)
                        antinode_positions.insert(
                            antinode.to_index(input.second.x));

                    antinode = antenna_pair.second[i] - slope;
                    if (antinode.x >= 0 && antinode.y >= 0 &&
                        antinode.x < input.second.x &&
                        antinode.y < input.second.y)
                        antinode_positions.insert(
                            antinode.to_index(input.second.x));
                }
        }
        return antinode_positions.size();
    }

    Day08::Solution2Type Day08::part2(const InputType &input)
    {
        std::unordered_set<size_t> antinode_positions;
        for (auto &antenna_pair : input.first)
        {
            for (size_t i = 0; i < antenna_pair.second.size(); ++i)
                for (size_t j = i + 1; j < antenna_pair.second.size(); ++j)
                {
                    // Calculate slope between pair
                    aoc::grid::Point slope(
                        antenna_pair.second[j].x - antenna_pair.second[i].x,
                        antenna_pair.second[j].y - antenna_pair.second[i].y);

                    // An antinode would appear on anything which is on the line between them for part 2 (including the starts)
                    aoc::grid::Point antinode = antenna_pair.second[j];
                    while (antinode.x >= 0 && antinode.y >= 0 &&
                           antinode.x < input.second.x &&
                           antinode.y < input.second.y)
                    {
                        antinode_positions.insert(
                            antinode.to_index(input.second.x));

                        antinode += slope;
                    }

                    antinode = antenna_pair.second[i];
                    while (antinode.x >= 0 && antinode.y >= 0 &&
                           antinode.x < input.second.x &&
                           antinode.y < input.second.y)
                    {
                        antinode_positions.insert(
                            antinode.to_index(input.second.x));

                        antinode -= slope;
                    }
                }
        }
        return antinode_positions.size();
    }
} // namespace aoc
