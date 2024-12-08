using SadRogue.Primitives;
using SadRogue.Primitives.GridViews;

namespace AdventOfCode;

public sealed class Day04 : BaseDay
{
    private readonly ArrayView<char> _input;
    
    public Day04()
    {
        _input = File.ReadAllText(InputFilePath).ParseCharGrid();
    }

    public override ValueTask<string> Solve_1()
    {
        return new ValueTask<string>(CountOccurrences("XMAS", _input).ToString());
    }

    public override ValueTask<string> Solve_2() => new(CountXFormations("MAS", _input).ToString());

    private static int CountOccurrences(string substr, IGridView<char> grid)
    {
        return grid.Positions()
            .Where(pos => grid[pos] == substr[0])
            .Sum(pos => AdjacencyRule.EightWay.DirectionsOfNeighborsClockwiseCache
                .Count(dir => GetSubstring(grid, pos, dir, substr.Length) == substr));
    }

    private static int CountXFormations(string word, IGridView<char> grid)
    {
        int xCount = 0;
        if (word.Length % 2 == 0)
            throw new ArgumentException("Word must have odd length.", nameof(word));

        foreach (var pos in grid.Positions())
        {
            if (grid[pos] != word[word.Length / 2])
                continue;

            int occurrences = 0;
            foreach (var diagonal in AdjacencyRule.Diagonals.DirectionsOfNeighborsClockwiseCache)
            {
                Point curPos = pos - diagonal.Multiply(word.Length / 2);
                if (GetSubstring(grid, curPos, diagonal, word.Length) == word)
                    occurrences++;
            }
            
            if (occurrences >= 2)
                xCount++;
        }

        return xCount;
    }

    private static string? GetSubstring(IGridView<char> grid, Point startPos, Direction dir, int substrLength)
    {
        string result = "";
        
        Point pos = startPos;
        while (grid.Contains(pos) && result.Length < substrLength)
        {
            result += grid[pos];
            pos += dir;
        }
        
        return result.Length == substrLength ? result : null;
    }
}
