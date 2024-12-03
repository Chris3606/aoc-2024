#include "day03/solution.hpp"
#include "utility.hpp"
#include <regex>
#include <sstream>

namespace aoc
{
    const std::regex mul_regex("mul\\((\\d+),(\\d+)\\)");
    const std::regex conditional_regex("(do|don't)\\(\\)");

    int simulate(const std::vector<std::smatch> &muls,
                 const std::vector<std::smatch> &conditionals)
    {
        int sum = 0;
        size_t c_idx = 0;
        bool enabled = true;

        for (auto &mul : muls)
        {
            auto pos = mul.position();

            // Simulate conditionals up to this position
            while (c_idx < conditionals.size() &&
                   conditionals[c_idx].position() < pos)
            {
                auto cond_match = conditionals[c_idx];
                enabled = cond_match[1].str() == "do";
                c_idx++;
            }

            // Add if needed
            if (!enabled)
                continue;

            sum += std::stoi(mul[1].str()) * std::stoi(mul[2]);
        }

        return sum;
    }

    Day03::Day03() : Day(3)
    {
    }

    Day03::InputType Day03::parse_input(std::ifstream &input_file)
    {
        std::stringstream ss;

        ss << input_file.rdbuf();

        return ss.str();
    }

    Day03::Solution1Type Day03::part1(const InputType &input)
    {
        auto muls = get_matches(input, mul_regex);
        return simulate(muls, {});
    }

    Day03::Solution2Type Day03::part2(const InputType &input)
    {
        auto muls = get_matches(input, mul_regex);
        auto conditionals = get_matches(input, conditional_regex);
        return simulate(muls, conditionals);
    }
} // namespace aoc
