using SadRogue.Primitives;
using SadRogue.Primitives.GridViews;

namespace AdventOfCode;

public sealed class Day12 : BaseDay
{
    private readonly IGridView<char> _grid;

    public Day12()
    {
        _grid = File.ReadAllText(InputFilePath).ParseCharGrid();
    }

    public override ValueTask<string> Solve_1()
        => new(FindAreas(_grid).Sum(a => a.Count * Perimeter(a)).ToString());

    public override ValueTask<string> Solve_2()
        => new(FindAreas(_grid).Sum(a => a.Count * NumSides(a)).ToString());

    private static IEnumerable<Area> FindAreas(IGridView<char> grid)
    {
        HashSet<Point> visited = [];
        
        foreach (var pos in grid.Positions())
        {
            if (visited.Contains(pos))
                continue;

            var area = new Area();
            Stack<Point> stack = new();
            stack.Push(pos);
            while (stack.Count > 0)
            {
                var point = stack.Pop();
                if (!visited.Add(point))
                    continue;
                area.Add(point);
                
                foreach (var neighbor in AdjacencyRule
                             .Cardinals
                             .Neighbors(point)
                             .Where(p => grid.Contains(p) && !visited.Contains(p) && grid[p] == grid[point]))
                    stack.Push(neighbor);
            }

            yield return area;
        }
    }

    private static int Perimeter(IReadOnlyArea area)
    {
        int perimeter = 0;

        foreach (var pos in area)
        {
            foreach (var neighbor in AdjacencyRule.Cardinals.Neighbors(pos))
                if (!area.Contains(neighbor))
                    perimeter++;
        }
        
        return perimeter;
    }

    private static int NumSides(IReadOnlyArea area)
    {
        int numSides = 0;
        foreach (var pos in area)
        {
            // Outer corners
            numSides += AdjacencyRule.Cardinals.DirectionsOfNeighborsCache
                .Count(d => !area.Contains(pos + d) && !area.Contains(pos + (d + 2)));
            
            // Inner corners
            numSides += AdjacencyRule.Cardinals.DirectionsOfNeighborsCache
                .Count(d => area.Contains(pos + d) && !area.Contains(pos + (d + 1)) && area.Contains(pos + (d + 2)));
        }
        
        return numSides;
    }
}
