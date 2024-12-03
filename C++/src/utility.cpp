#include "utility.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace aoc
{
    std::vector<int> parse_ints(const std::string &delimited_ints,
                                char delimeter)
    {
        std::vector<int> result;
        std::stringstream ss(delimited_ints);

        std::string n_data;
        while (std::getline(ss, n_data, delimeter))
            result.push_back(std::stoi(n_data));

        return result;
    }

    std::vector<std::smatch> get_matches(const std::string &input,
                                         const std::regex &regex)
    {
        std::regex_iterator<std::string::const_iterator> it(input.begin(),
                                                            input.end(),
                                                            regex);
        std::regex_iterator<std::string::const_iterator> end;

        std::vector<std::smatch> matches;
        while (it != end)
            matches.push_back(*it++);

        return matches;
    }

    int wrap_around(int num, int wrap_to)
    {
        return (num % wrap_to + wrap_to) % wrap_to;
    }

    aoc::grid::ArrayView<char> get_grid(std::istream &grid_data)
    {
        std::vector<char> vec;
        size_t width = 0;

        std::string line;
        while (std::getline(grid_data, line))
        {
            width = line.size();
            vec.insert(vec.end(), line.begin(), line.end());
        }

        return aoc::grid::ArrayView<char>(std::move(vec), width);
    }
    // Token::Token(char sep) : m_sep(sep)
    // {
    // }

    // std::istream &operator>>(std::istream &is, Token &token)
    // {
    //     return std::getline(is, token);
    // }
} // namespace aoc