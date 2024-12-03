#include "day.hpp"
#include "day00/solution.hpp"
#include "day01/solution.hpp"
#include "day02/solution.hpp"
#include "day03/solution.hpp"
#include <iostream>
#include <vector>

std::vector<aoc::DayBase *> days{
    new aoc::Day00(),
    new aoc::Day01(),
    new aoc::Day02(),
    new aoc::Day03(),
};

int main(int argc, const char *argv[])
{
    if (argc < 2 || argc > 3 || (argc == 3 && std::string(argv[2]) != "-s"))
    {
        std::cerr << "Invalid usage: " << argv[0] << " <DAY> [-s]" << std::endl;
        return -1;
    }

    int day_num = 0;
    try
    {
        day_num = std::stoi(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Usage error: Day given was not a valid integer."
                  << std::endl;
        return -2;
    }


    bool sample = argc == 3;

    if (day_num < 0 || (size_t)day_num >= days.size())
    {
        std::cerr << "Usage error: Day given was not in accepted range."
                  << std::endl;
        return -3;
    }
    try
    {
        days[day_num]->solve(sample);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return -4;
    }

    return 0;
}