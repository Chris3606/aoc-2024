using SadRogue.Primitives;
using SadRogue.Primitives.GridViews;

namespace AdventOfCode;

public sealed class Day10 : BaseDay
{
    private readonly IGridView<int> _grid;

    public Day10()
    {
        var charView = File.ReadAllText(InputFilePath).ParseCharGrid();
        var view = new ArrayView<int>(charView.Width, charView.Height);
        view.ApplyOverlay(p => charView[p] - '0');
        _grid = view;
    }

    public override ValueTask<string> Solve_1()
    {
        int sum = 0;
        foreach (var pos in _grid.Positions().Where(p => _grid[p] == 0))
        {
            int trailheadScore = 0;
            var points = new Queue<Point>();
            points.Enqueue(pos);
            var visited = new HashSet<Point>();
            while (points.Count > 0)
            {
                var point = points.Dequeue();
                if (visited.Contains(point) || Distance.Manhattan.Calculate(pos, point) > 9)
                    continue;
                
                visited.Add(point);

                if (_grid[point] == 9)
                {
                    trailheadScore++;
                    continue;
                }

                foreach (var neighbor in ((AdjacencyRule)Distance.Manhattan)
                         .Neighbors(point)
                         .Where(p => _grid.Contains(p) && !visited.Contains(p)))
                {
                    if (_grid[neighbor] - _grid[point] == 1)
                        points.Enqueue(neighbor);
                }
            }
            
            sum += trailheadScore;
        }

        return new(sum.ToString());
    }

    public override ValueTask<string> Solve_2() => throw new NotImplementedException();
}
