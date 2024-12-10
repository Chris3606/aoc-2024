#pragma once
#include "day.hpp"
#include <optional>
#include <string>
#include <vector>

namespace aoc
{
    class DiskEntry
    {
    public:
        enum class Type
        {
            FILE = 0,
            FREE_SPACE = 1,
        };

        DiskEntry(size_t size);
        DiskEntry(size_t size, size_t file_id);

        size_t id() const;
        size_t size() const;
        Type type() const;
        void shrink_to(size_t size);
        void make_free();

    private:
        Type m_type;

        size_t m_id;
        size_t m_size;
    };

    class Day09 : public Day<std::pair<std::vector<std::optional<int>>,
                                       std::vector<DiskEntry>>,
                             long long>
    {
    public:
        Day09();

    protected:
        virtual InputType parse_input(std::ifstream &input_file) override final;
        virtual Solution1Type part1(const InputType &input) override final;
        virtual Solution2Type part2(const InputType &input) override final;
    };


} // namespace aoc