#pragma once
#include "day.hpp"
#include <string>
#include <vector>

namespace aoc
{
    class Day03 : public Day<std::string, int>
    {
    public:
        Day03();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc