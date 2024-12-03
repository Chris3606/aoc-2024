#include "day05/solution.hpp"
#include "utility.hpp"
#include <unordered_set>

namespace aoc
{
    bool check_manual(const std::vector<int> &manual,
                      const std::unordered_map<int, std::vector<int>> &rules)
    {
        std::unordered_map<int, bool> found_values;
        for (auto &val : manual)
            found_values[val] = false;

        bool correct = true;
        for (auto &val : manual)
        {
            // If there are dependencies for this page specified in the rules, then there are potential
            // dependencies to worry about, so we'll need to check them.
            if (rules.find(val) != rules.end())
            {
                // For each applicable rule, iff the dependency is part of this set at all, make sure
                // we've seen its dependency before in the list
                for (auto &dependency : rules.at(val))
                {
                    // Dependency is not part of the set at all
                    if (found_values.find(dependency) == found_values.end())
                        continue;

                    // Dependency is part of the set but not seen before; this is a failure
                    if (!found_values.at(dependency))
                    {
                        correct = false;
                        break;
                    }
                }
            }

            if (!correct)
                break;

            found_values[val] = true;
        }

        return correct;
    }

    void add_dependencies(
        const std::vector<int> &orig_list,
        std::vector<int> &cur_list,
        int dependency,
        const std::unordered_map<int, std::vector<int>> &rules)
    {
        // Only packages actually in the original list matter.
        if (std::find(orig_list.begin(), orig_list.end(), dependency) ==
            orig_list.end())
            return;

        // There are dependencies; resolve them locally.
        if (rules.find(dependency) != rules.end())
        {
            // There are deps, so resolve all of those recursively.
            for (auto &dep : rules.at(dependency))
                add_dependencies(orig_list, cur_list, dep, rules);
        }

        // If there aren't dependencies, this is a base case so we'll just add it.
        // Otherwise, we've resolved all our other dependencies, so add if it doesn't
        // exist.
        if (std::find(cur_list.begin(), cur_list.end(), dependency) ==
            cur_list.end())
            cur_list.push_back(dependency);
    }

    std::vector<int> resolve_print_order(
        const std::vector<int> &manual,
        const std::unordered_map<int, std::vector<int>> &rules)
    {
        std::vector<int> correct_list;
        for (auto &item : manual)
            add_dependencies(manual, correct_list, item, rules);

        return correct_list;
    }

    PrintingInput::PrintingInput(
        std::unordered_map<int, std::vector<int>> &&printing_rules,
        std::vector<std::vector<int>> &&safety_manuals)
        : m_printing_rules(std::move(printing_rules)),
          m_safety_manuals(std::move(safety_manuals))
    {
    }

    std::unordered_map<int, std::vector<int>> &PrintingInput::printing_rules()
    {
        return m_printing_rules;
    }

    const std::unordered_map<int, std::vector<int>> &PrintingInput::
        printing_rules() const
    {
        return m_printing_rules;
    }

    std::vector<std::vector<int>> &PrintingInput::safety_manuals()
    {
        return m_safety_manuals;
    }

    const std::vector<std::vector<int>> &PrintingInput::safety_manuals() const
    {
        return m_safety_manuals;
    }

    Day05::Day05() : Day(5)
    {
    }

    Day05::InputType Day05::parse_input(std::ifstream &input_file)
    {
        std::unordered_map<int, std::vector<int>> printing_rules;
        std::vector<std::vector<int>> safety_manuals;

        bool parsing_manuals = false;
        std::string line;
        while (std::getline(input_file, line))
        {
            if (line.size() == 0)
            {
                parsing_manuals = true;
                continue;
            }

            if (parsing_manuals)
                safety_manuals.push_back(parse_ints(line, ','));
            else
            {
                auto parts = parse_ints(line, '|');
                if (parts.size() != 2)
                    throw std::runtime_error(
                        "Read printing rule that didn't have 2 integers.");

                if (printing_rules.find(parts[1]) == printing_rules.end())
                    printing_rules[parts[1]] = std::vector<int>();

                printing_rules[parts[1]].push_back(parts[0]);
            }
        }

        return PrintingInput(std::move(printing_rules),
                             std::move(safety_manuals));
    }

    Day05::Solution1Type Day05::part1(const InputType &input)
    {
        int sum_middle_correct = 0;

        for (auto &manual : input.safety_manuals())
        {
            if (check_manual(manual, input.printing_rules()))
                sum_middle_correct += manual[manual.size() / 2];
        }
        return sum_middle_correct;
    }

    Day05::Solution2Type Day05::part2(const InputType &input)
    {
        int sum_middle_incorrect = 0;

        for (auto &manual : input.safety_manuals())
        {
            if (check_manual(manual, input.printing_rules()))
                continue;

            auto correct_order =
                resolve_print_order(manual, input.printing_rules());
            sum_middle_incorrect += correct_order[correct_order.size() / 2];
        }
        return sum_middle_incorrect;
    }
} // namespace aoc
