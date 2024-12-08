#pragma once
#include "day.hpp"
#include "grid/point.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc
{
    class Day08
        : public Day<
              std::pair<std::unordered_map<char, std::vector<aoc::grid::Point>>,
                        aoc::grid::Point>,
              size_t>
    {
    public:
        Day08();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc