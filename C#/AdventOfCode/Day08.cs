using SadRogue.Primitives;
using SadRogue.Primitives.GridViews;

namespace AdventOfCode;

public sealed class Day08 : BaseDay
{
    private readonly Dictionary<char, List<Point>> _map;
    private readonly Rectangle _bounds;

    public Day08()
    {
        var grid = File.ReadAllText(InputFilePath).ParseCharGrid();
        _map = new Dictionary<char, List<Point>>();

        foreach (var pos in grid.Positions().Where(p => grid[p] != '.'))
        {
            if (!_map.ContainsKey(grid[pos]))
                _map[grid[pos]] = [];
            
            _map[grid[pos]].Add(pos);
        }
        
        _bounds = grid.Bounds();
    }

    public override ValueTask<string> Solve_1()
        => new (FindAntinodes(_map, _bounds, 1, false).Count.ToString());

    public override ValueTask<string> Solve_2()
        => new (FindAntinodes(_map, _bounds, null, true).Count.ToString());

    private static IEnumerable<Point> ExtendLine(Point lineStart, Point slope)
    {
        var cur = lineStart;
        while (true)
        {
            cur += slope;
            yield return cur;
        }
        // ReSharper disable once IteratorNeverReturns
    }
    private static HashSet<Point> FindAntinodes(Dictionary<char, List<Point>> antennas, Rectangle bounds, int? extensionLimit, bool includeStartingPoints)
    {
        var antinodes = new HashSet<Point>();
        foreach (var (_, points) in antennas)
        {
            for (int i = 0; i < points.Count; i++)
            for (int j = i + 1; j < points.Count; j++)
            {
                var slope = new Point(points[j].X - points[i].X, points[j].Y - points[i].Y);
                AddAntinodes(antinodes, points[j], slope, bounds, extensionLimit, includeStartingPoints);
                AddAntinodes(antinodes, points[i], slope * -1, bounds, extensionLimit, includeStartingPoints);
            }
        }
        return antinodes;
    }

    private static void AddAntinodes(HashSet<Point> antinodes, Point startingPoint, Point slope, Rectangle bounds, int? extensionLimit, bool includeStart)
    {
        var lineExtension = extensionLimit.HasValue ?
            ExtendLine(startingPoint, slope * -1).Take(extensionLimit.Value) :
            ExtendLine(startingPoint, slope);
        antinodes.AddRange(lineExtension.TakeWhile(bounds.Contains));
        if (includeStart)
            antinodes.Add(startingPoint);
    }
}
