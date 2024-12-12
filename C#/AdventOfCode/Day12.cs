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
    {
        var areas = FindAreas(_grid);

        int sum = 0;
        foreach (var areasList in areas.Values)
            foreach (var area in areasList)
                sum += area.Count * Perimeter(area);
        
        return new(sum.ToString());
    }

    public override ValueTask<string> Solve_2()
    {
        var areas = FindAreas(_grid);

        int sum = 0;
        foreach (var pair in areas)
            foreach (var area in pair.Value)
                sum += area.Count * NumSides(area);

        return new(sum.ToString());
    }

    private static Dictionary<char, List<Area>> FindAreas(IGridView<char> grid)
    {
        Dictionary<char, List<Area>> areas = new();
        
        HashSet<Point> visited = new();
        
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
            
            if (!areas.ContainsKey(grid[pos]))
                areas.Add(grid[pos], []);
            
            areas[grid[pos]].Add(area);
        }

        return areas;
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
