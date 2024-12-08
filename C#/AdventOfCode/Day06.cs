using SadRogue.Primitives;
using SadRogue.Primitives.GridViews;

namespace AdventOfCode;

public sealed class Day06 : BaseDay
{
    private readonly ArrayView<char> _grid;
    private readonly Point _guardStart;

    public Day06()
    {
        _grid = File.ReadAllText(InputFilePath).ParseCharGrid();
        _guardStart = _grid.Positions().Single(p => _grid[p] == '^');
        _grid[_guardStart] = '.';
    }

    public override ValueTask<string> Solve_1()
        => new(
            (SimulateGuardPatrol(_guardStart, _grid) ?? throw new Exception("Original input was a loop"))
            .Count
            .ToString());

    public override ValueTask<string> Solve_2()
    {
        var originalPath = SimulateGuardPatrol(_guardStart, _grid);
        if (originalPath == null)
            throw new Exception("Original input was a loop");
        
        return new(originalPath.Keys
            .Where(p => p != _guardStart)
            .Count(p => ObstacleCreatesLoop(_grid, _guardStart, p))
            .ToString());
    }

    // Given a guard starting position and board state, simulate the guard's route.
    // Infinite loop returns null; otherwise a set of all positions visited
    private static Dictionary<Point, List<Direction>>? SimulateGuardPatrol(Point guardStart, IGridView<char> grid)
    {
        var visited = new Dictionary<Point, List<Direction>>();
        var curGuardPos = guardStart;
        var curGuardDir = Direction.Up;
        
        while (grid.Contains(curGuardPos))
        {
            // Visit current position
            if (!visited.ContainsKey(curGuardPos))
                visited.Add(curGuardPos, []);
            
            // If we have have visited this position before from the same direction, then we're stuck in a loop.
            var list = visited[curGuardPos];
            if (list.Contains(curGuardDir))
                return null;
            list.Add(curGuardDir);
            
            // Turn clockwise 90 degrees until we find either an escape or a free position
            var newPosition = curGuardPos + curGuardDir;
            while (grid.Contains(newPosition) && grid[newPosition] == '#')
            {
                curGuardDir += 2;
                newPosition = curGuardPos + curGuardDir;
            }
            
            // Proceed
            curGuardPos = newPosition;
        }
        
        return visited;
    }

    private static bool ObstacleCreatesLoop(ISettableGridView<char> grid, Point guardStart, Point newObstacle)
    {
        if (grid[newObstacle] != '.')
            throw new ArgumentException("You can only place obstacles on free tiles.");
        
        grid[newObstacle] = '#';
        var visited = SimulateGuardPatrol(guardStart, grid);
        grid[newObstacle] = '.';

        return visited == null;
    }
}
