#include "day02/solution.hpp"
#include "utility.hpp"

namespace aoc
{

    bool is_safe(const std::vector<int> report)
    {
        int min_diff = 1;
        int max_diff = 3;

        if (report[1] < report[0])
        {
            min_diff = -3;
            max_diff = -1;
        }

        bool safe = true;
        for (size_t i = 1; i < report.size(); i++)
        {
            int diff = report[i] - report[i - 1];
            if (diff < min_diff || diff > max_diff)
            {
                safe = false;
                break;
            }
        }

        return safe;
    }

    int check_reports(const std::vector<std::vector<int>> &reports,
                      bool check_with_missing)
    {
        int safe_reports = 0;

        for (auto &report : reports)
        {
            if (is_safe(report))
                safe_reports++;
            else if (check_with_missing)
            {
                for (size_t i = 0; i < report.size(); i++)
                {
                    std::vector<int> report_removed = report;
                    report_removed.erase(report_removed.begin() + i);

                    if (is_safe(report_removed))
                    {
                        safe_reports++;
                        break;
                    }
                }
            }
        }

        return safe_reports;
    }

    Day02::Day02() : Day(2)
    {
    }

    Day02::InputType Day02::parse_input(std::ifstream &input_file)
    {
        std::string line;
        InputType result;

        while (std::getline(input_file, line, '\n'))
            result.push_back(parse_ints(line, ' '));

        return result;
    }

    Day02::Solution1Type Day02::part1(const InputType &input)
    {
        return check_reports(input, false);
    }

    Day02::Solution2Type Day02::part2(const InputType &input)
    {
        return check_reports(input, true);
    }
} // namespace aoc
