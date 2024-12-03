#pragma once
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

namespace aoc
{
    template <typename T>
    std::unordered_map<T, int> to_histogram(const std::vector<T> &items)
    {
        std::unordered_map<T, int> map;

        for (auto &i : items)
        {
            if (map.find(i) != map.end())
                map[i] += 1;
            else
                map[i] = 1;
        }

        return map;
    }

    std::vector<std::smatch> get_matches(const std::string &input,
                                         const std::regex &regex);

    std::vector<int> to_ints(const std::string &space_delimited_ints);
    // class Token : std::string
    // {
    // public:
    //     Token(char sep);
    //     friend std::istream &operator>>(std::istream &is, Token &token);

    // private:
    //     char m_sep;
    // };
} // namespace aoc