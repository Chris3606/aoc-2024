#pragma once
#include "day.hpp"
#include "grid/array_view.hpp"
#include "grid/point.hpp"

namespace aoc
{
    class Day06
        : public Day<std::pair<aoc::grid::ArrayView<char>, aoc::grid::Point>,
                     size_t>
    {
    public:
        Day06();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc