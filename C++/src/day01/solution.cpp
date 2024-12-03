#include "day01/solution.hpp"
#include "utility.hpp"
#include <assert.h>
#include <math.h>
#include <sstream>

namespace aoc
{
    Day01::Day01() : Day(1)
    {
    }

    Day01::InputType Day01::parse_input(std::ifstream &input_file)
    {
        InputType result;

        std::string line;
        while (std::getline(input_file, line))
        {
            std::string num_data;
            std::istringstream line_stream(line);

            std::getline(line_stream, num_data, ' ');
            int i1 = std::stoi(num_data);

            std::getline(line_stream, num_data, ' ');
            std::getline(line_stream, num_data, ' ');
            std::getline(line_stream, num_data, ' ');

            std::getline(line_stream, num_data, ' ');
            int i2 = std::stoi(num_data);

            std::get<0>(result).push_back(i1);
            std::get<1>(result).push_back(i2);
        }

        return result;
    }

    Day01::Solution1Type Day01::part1(const InputType &input)
    {
        int dist = 0;
        auto v1 = std::get<0>(input);
        auto v2 = std::get<1>(input);

        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        assert(v1.size() == v2.size());

        for (size_t i = 0; i < v1.size(); i++)
            dist += std::abs(v1[i] - v2[i]);

        return dist;
    }

    Day01::Solution2Type Day01::part2(const InputType &input)
    {
        int similarity_score = 0;
        auto v1 = std::get<0>(input);
        auto v2 = std::get<1>(input);

        auto h1 = to_histogram(v1);
        auto h2 = to_histogram(v2);

        for (auto &i : h1)
        {
            if (h2.find(i.first) == h2.end())
                continue;

            similarity_score += i.first * h2[i.first] * i.second;
        }

        return similarity_score;
    }
} // namespace aoc
