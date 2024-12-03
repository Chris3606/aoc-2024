#pragma once
#include "grid/point.hpp"
#include <memory>
#include <vector>

namespace aoc::grid
{
    template <typename T>
    class ArrayView
    {
    public:
        ArrayView(size_t width, size_t height)
            : m_data(), m_width(width), m_height(height)
        {
            m_data.resize(width * height);
        };

        ArrayView(std::vector<T> &&data, size_t width)
            : m_data(std::move(data)), m_width(width),
              m_height(m_data.size() / width) {};

        size_t width() const
        {
            return m_width;
        };

        size_t height() const
        {
            return m_height;
        };

        T &operator[](size_t index)
        {
            return m_data[index];
        };
        const T &operator[](size_t index) const
        {
            return m_data[index];
        };

        T &operator[](const Point &location)
        {
            return m_data[location.to_index(m_width)];
        };
        const T &operator[](const Point &location) const
        {
            return m_data[location.to_index(m_width)];
        };

        bool contains(const aoc::grid::Point &point) const
        {
            return point.x >= 0 && point.y >= 0 &&
                   static_cast<size_t>(point.x) < width() &&
                   static_cast<size_t>(point.y) < height();
        };


    private:
        std::vector<T> m_data;
        size_t m_width;
        size_t m_height;
    };
} // namespace aoc::grid