#pragma once
#include "day.hpp"
#include <string>
#include <tuple>
#include <vector>

namespace aoc
{
    class Day01
        : public Day<std::tuple<std::vector<int>, std::vector<int>>, int>
    {
    public:
        Day01();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc