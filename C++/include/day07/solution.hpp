#pragma once
#include "day.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace aoc
{
    class Day07
        : public Day<std::vector<std::pair<int64_t, std::vector<int64_t>>>,
                     int64_t>
    {
    public:
        Day07();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc