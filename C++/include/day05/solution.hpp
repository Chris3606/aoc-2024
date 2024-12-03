#pragma once
#include "day.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc
{
    struct PrintingInput
    {
        PrintingInput(
            std::unordered_map<int, std::vector<int>> &&printing_rules,
            std::vector<std::vector<int>> &&safety_manuals);

        std::unordered_map<int, std::vector<int>> &printing_rules();
        const std::unordered_map<int, std::vector<int>> &printing_rules() const;

        std::vector<std::vector<int>> &safety_manuals();
        const std::vector<std::vector<int>> &safety_manuals() const;

    private:
        std::unordered_map<int, std::vector<int>> m_printing_rules;
        std::vector<std::vector<int>> m_safety_manuals;
    };

    class Day05 : public Day<PrintingInput, int>
    {
    public:
        Day05();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };
} // namespace aoc