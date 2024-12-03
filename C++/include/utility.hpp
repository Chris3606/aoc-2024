#pragma once
#include "grid/array_view.hpp"
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

    std::vector<int> parse_ints(const std::string &delimeted_ints,
                                char delimeter);

    /**
     * @brief Gets a array view from a grid in the following format:
     * 
     * ABCDE
     * EFGHI
     */
    aoc::grid::ArrayView<char> get_grid(std::istream &grid_data);
    int wrap_around(int num, int wrap_to);

    // class Token : std::string
    // {
    // public:
    //     Token(char sep);
    //     friend std::istream &operator>>(std::istream &is, Token &token);

    // private:
    //     char m_sep;
    // };
} // namespace aoc