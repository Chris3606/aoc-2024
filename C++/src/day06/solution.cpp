#include "day06/solution.hpp"
#include "grid/direction.hpp"
#include "utility.hpp"
#include <optional>
#include <unordered_set>

namespace aoc
{
    std::optional<std::unordered_set<size_t>> get_path_to_exit(
        const aoc::grid::ArrayView<char> &grid,
        const aoc::grid::Point &guard_start)
    {
        aoc::grid::Point cur_guard_pos = guard_start;
        aoc::grid::Direction guard_dir = aoc::grid::Direction::UP;

        std::unordered_set<size_t> visited;
        size_t moves = 0;
        while (grid.contains(cur_guard_pos))
        {
            auto cur_guard_idx = cur_guard_pos.to_index(grid.width());

            // Record this position as visited
            visited.insert(cur_guard_idx);

            // Turn 90 degrees right until we are facing either a map edge (escape route) or a map
            // square with no obstacle.
            while (grid.contains(cur_guard_pos + guard_dir) &&
                   grid[cur_guard_pos + guard_dir] == '#')
                guard_dir = guard_dir + 2;

            // Proceed
            cur_guard_pos += guard_dir;

            // Cycle check (we could visit all cells from all directions in width * height * 4, so more than that
            // is a loop).
            ++moves;
            if (moves > grid.width() * grid.height() *
                            aoc::grid::Direction::CARDINALS.size())
                return std::nullopt;
        }

        return visited;
    }

    Day06::Day06() : Day(6)
    {
    }

    Day06::InputType Day06::parse_input(std::ifstream &input_file)
    {

        auto grid = aoc::get_grid(input_file);

        aoc::grid::Point guard_start(-1, -1);
        for (size_t i = 0; i < grid.width() * grid.height(); i++)
            if (grid[i] == '^')
            {
                grid[i] = '.';
                guard_start = aoc::grid::Point::from_index(i, grid.width());
                break;
            }

        if (guard_start.x == -1)
            throw std::runtime_error("Failed to find guard starting position.");

        return InputType(std::move(grid), guard_start);
    }

    Day06::Solution1Type Day06::part1(const InputType &input)
    {
        return get_path_to_exit(input.first, input.second)->size();
    }

    Day06::Solution2Type Day06::part2([[maybe_unused]] const InputType &input)
    {
        // Copy grid so we can modify later for checking cycles; one copy now saves us path.size()
        // copies later.
        auto grid = input.first;
        auto guard_start = input.second;

        // Find original path followed
        auto path = *get_path_to_exit(grid, guard_start);

        // Find all potential loop options by trying to place an obstacle everywhere the guard visits,
        // one square at a time, excluding the start. Then simply re-run the escape check.
        size_t loops_found = 0;
        for (auto &pos_idx : path)
        {
            if (pos_idx == guard_start.to_index(input.first.width()))
                continue;

            grid[pos_idx] = '#';
            if (!get_path_to_exit(grid, guard_start))
                ++loops_found;
            grid[pos_idx] = '.';
        }

        return loops_found;
    }
} // namespace aoc
