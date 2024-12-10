#include "day09/solution.hpp"
#include <sstream>

namespace aoc
{
    DiskEntry::DiskEntry(size_t size) : m_type(Type::FREE_SPACE), m_size(size)
    {
    }

    DiskEntry::DiskEntry(size_t size, size_t id)
        : m_type(Type::FILE), m_id(id), m_size(size)
    {
    }

    size_t DiskEntry::id() const
    {
        if (m_type == Type::FREE_SPACE)
            throw std::runtime_error("Free space doesn't have an ID.");

        return m_id;
    }

    size_t DiskEntry::size() const
    {
        return m_size;
    }

    DiskEntry::Type DiskEntry::type() const
    {
        return m_type;
    }

    void DiskEntry::shrink_to(size_t size)
    {
        m_size = size;
    }

    void DiskEntry::make_free()
    {
        m_type = DiskEntry::Type::FREE_SPACE;
    }

    Day09::Day09() : Day(9)
    {
    }

    Day09::InputType Day09::parse_input(std::ifstream &input_file)
    {
        std::stringstream ss;
        ss << input_file.rdbuf();

        std::string s = ss.str();

        std::vector<std::optional<int>> disk1;
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (i % 2 == 0) // File
                for (size_t j = 0; j < static_cast<size_t>(s[i] - '0'); ++j)
                    disk1.push_back(i / 2);
            else // Free space
                for (size_t j = 0; j < static_cast<size_t>(s[i] - '0'); ++j)
                    disk1.push_back(std::nullopt);
        }

        std::vector<DiskEntry> disk2;
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (i % 2 == 0) // File
                disk2.push_back(DiskEntry(s[i] = '0', i / 2));
            else
                disk2.push_back(DiskEntry(s[i] - '0'));
        }

        return InputType(disk1, disk2);
    }

    Day09::Solution1Type Day09::part1(const InputType &input)
    {
        std::vector<std::optional<int>> input_copy = input.first;

        size_t next_free_idx = 0;
        size_t end_file = input_copy.size() - 1;

        while (true)
        {
            // Advance to next free space
            while (next_free_idx < end_file && input_copy[next_free_idx])
                ++next_free_idx;

            if (next_free_idx >= end_file)
                break;

            // Go back to the closest empty file block to the end
            while (end_file > next_free_idx && !input_copy[end_file])
                --end_file;

            if (end_file <= next_free_idx)
                break;

            // Move block
            auto value = *input_copy[end_file];
            input_copy[end_file] = std::nullopt;
            input_copy[next_free_idx] = value;
        }

        long long checksum = 0;
        for (size_t i = 0; i < input_copy.size() && input_copy[i]; ++i)
        {
            checksum += *input_copy[i] * i;
            if (checksum < 0)
                throw std::runtime_error("Foo");
        }

        return checksum;
    }

    Day09::Solution2Type Day09::part2(const InputType &input)
    {
        std::vector<std::optional<int>> input_copy = input.first;

        //size_t next_free_idx = 0;
        size_t end_file = input_copy.size() - 1;

        while (true)
        {
            // // Advance to next free space
            // while (next_free_idx < end_file && input_copy[next_free_idx])
            //     ++next_free_idx;

            // if (next_free_idx >= end_file)
            //     break;

            // Go back to the closest file block to the end
            while (end_file > 0 && !input_copy[end_file])
                --end_file;

            if (!input_copy[end_file])
                break;

            // Find size of file block
            size_t end_file_start = end_file;
            while (end_file_start > 0 && input_copy[end_file_start] &&
                   *input_copy[end_file_start] == *input_copy[end_file])
                end_file_start--;

            if (input_copy[end_file_start] &&
                *input_copy[end_file_start] != input_copy[end_file])
                end_file_start++;

            size_t file_size = end_file - end_file_start + 1;

            // Iterate through free space blocks and see if we can find one big enough
            size_t free_idx = 0;
            bool found_free = false;
            for (size_t i = 0; i < end_file_start; i++)
            {
                // Start of free space block
                if (!input_copy[i])
                {
                    size_t free_size = 0;
                    for (size_t j = i; j < end_file_start && !input_copy[j];
                         j++)
                        free_size++;

                    if (free_size >= file_size)
                    {
                        found_free = true;
                        free_idx = i;
                        break;
                    }
                }
            }

            // Move file
            if (found_free)
            {
                for (size_t i = 0; i < file_size; i++)
                {
                    input_copy[free_idx + i] = *input_copy[end_file_start + i];
                    input_copy[end_file_start + i] = std::nullopt;
                }
            }
        }

        long long checksum = 0;
        for (size_t i = 0; i < input_copy.size() && input_copy[i]; ++i)
        {
            checksum += *input_copy[i] * i;
            if (checksum < 0)
                throw std::runtime_error("Foo");
        }

        return checksum;


        // std::vector<DiskEntry> input_copy = input.second;
        // // std::vector<bool> has_moved(input_copy.size());
        // // for (size_t i = 0; i < has_moved.size(); i++)
        // //     has_moved[i] = false;

        // size_t idx = input_copy.size();
        // while (idx > 0)
        // {
        //     idx--;
        //     if (input_copy[idx].type() != DiskEntry::Type::FILE)
        //         continue;

        //     // Find first location in which it fits (before itself)
        //     size_t fitsIdx = 0;
        //     bool fits = false;
        //     for (size_t i = 0; i < idx; ++i)
        //     {
        //         // if (has_moved[i])
        //         //     break;

        //         if (input_copy[i].type() == DiskEntry::Type::FREE_SPACE &&
        //             input_copy[i].size() >= input_copy[i].size())
        //         {
        //             fits = true;
        //             fitsIdx = i;
        //             break;
        //         }
        //     }

        //     // If file fits, shift it down.
        //     //has_moved[idx] = true;
        //     if (fits)
        //     {
        //         input_copy[fitsIdx].shrink_to(input_copy[fitsIdx].size() -
        //                                       input_copy[idx].size());
        //         input_copy.insert(input_copy.begin() + fitsIdx,
        //                           input_copy[idx]);
        //         input_copy[idx].make_free();
        //     }
        // }

        // // Calculate checksum
        // long long checksum = 0;
        // size_t blockIdx = 0;
        // for (auto &entry : input_copy)
        // {
        //     if (entry.type() != DiskEntry::Type::FILE)
        //     {
        //         blockIdx += entry.size();
        //         continue;
        //     }

        //     for (size_t i = 0; i < entry.size(); ++i)
        //     {
        //         checksum += blockIdx * entry.id();
        //         ++blockIdx;
        //     }
        // }

        // return checksum;
    }
} // namespace aoc
