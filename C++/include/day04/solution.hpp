#pragma once
#include "day.hpp"
#include "grid/array_view.hpp"
#include <string>

namespace aoc
{
    class Day04 : public Day<aoc::grid::ArrayView<char>, int>
    {
    public:
        Day04();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc