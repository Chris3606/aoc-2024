#pragma once
#include "day.hpp"
#include <string>
#include <vector>

namespace aoc
{
    class Day02 : public Day<std::vector<std::vector<int>>, int>
    {
    public:
        Day02();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc