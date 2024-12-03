#include "utility.hpp"
#include <sstream>

namespace aoc
{
    std::vector<int> to_ints(const std::string &space_delimited_ints)
    {
        std::vector<int> result;
        std::stringstream ss(space_delimited_ints);

        int n;
        while (ss >> n)
            result.push_back(n);

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
    // Token::Token(char sep) : m_sep(sep)
    // {
    // }

    // std::istream &operator>>(std::istream &is, Token &token)
    // {
    //     return std::getline(is, token);
    // }
} // namespace aoc