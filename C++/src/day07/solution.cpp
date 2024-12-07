#include "day07/solution.hpp"
#include "utility.hpp"
#include <span>
#include <sstream>

namespace aoc
{
    bool evaluate(int64_t test_value,
                  int64_t aggregate,
                  std::span<const int64_t> remaining_operands,
                  bool concat_op)
    {
        if (aggregate > test_value)
            return false;

        if (aggregate == test_value && remaining_operands.empty())
            return true;

        if (remaining_operands.empty())
            return false;

        bool is_possible = evaluate(test_value,
                                    aggregate + remaining_operands[0],
                                    remaining_operands.subspan(1),
                                    concat_op) ||
                           evaluate(test_value,
                                    aggregate * remaining_operands[0],
                                    remaining_operands.subspan(1),
                                    concat_op);

        if (!is_possible && concat_op)
        {
            is_possible =
                evaluate(test_value,
                         std::stoll(std::to_string(aggregate) +
                                    std::to_string(remaining_operands[0])),
                         remaining_operands.subspan(1),
                         concat_op);
        }

        return is_possible;
    }

    int64_t sum_equations(
        const std::vector<std::pair<int64_t, std::vector<int64_t>>> &equations,
        bool allow_concat_op)
    {
        int64_t sum = 0;
        for (auto &equation : equations)
        {
            if (evaluate(equation.first,
                         0,
                         std::span<const int64_t>(equation.second),
                         allow_concat_op))
                sum += equation.first;
        }
        return sum;
    }

    Day07::Day07() : Day(7)
    {
    }

    Day07::InputType Day07::parse_input(std::ifstream &input_file)
    {
        std::vector<std::pair<int64_t, std::vector<int64_t>>> input;
        std::string line;
        while (std::getline(input_file, line))
        {
            std::string test_value_data;
            std::stringstream ss(line);
            std::getline(ss, test_value_data, ':');
            std::string operand_data =
                ss.str().substr(test_value_data.size() + 2);

            int64_t test_data = std::stoll(test_value_data);
            auto operands_ints = aoc::parse_ints(operand_data, ' ');
            std::vector<int64_t> operands;
            for (auto &i : operands_ints)
                operands.push_back(static_cast<int64_t>(i));
            input.push_back(
                std::pair<int64_t, std::vector<int64_t>>(test_data,
                                                         std::move(operands)));
        }

        return input;
    }

    Day07::Solution1Type Day07::part1(const InputType &input)
    {
        return sum_equations(input, false);
    }

    Day07::Solution2Type Day07::part2([[maybe_unused]] const InputType &input)
    {
        return sum_equations(input, true);
    }
} // namespace aoc
