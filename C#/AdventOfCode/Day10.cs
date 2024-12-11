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
            var endpoints = new HashSet<Point>();
            var list = new List<Point>();
            GetTrailEndpoints(new HashSet<Point>(), pos, 9, list);
            endpoints.AddRange(list.Where(p => _grid[p] == 9));
            
            sum += endpoints.Count;
        }

        return new(sum.ToString());
    }

    public override ValueTask<string> Solve_2()
    {
        {
            int sum = 0;
            foreach (var pos in _grid.Positions().Where(p => _grid[p] == 0))
            {
                var list = new List<Point>();
                GetTrailEndpoints(new HashSet<Point>(), pos, 9, list);
            
                sum += list.Count(p => _grid[p] == 9);
            }

            return new(sum.ToString());
        }
    }

    private void GetTrailEndpoints(HashSet<Point> prevPath, Point curPoint, int depth, List<Point> endpoints)
    {
        if (prevPath.Count == depth)
        {
            endpoints.Add(curPoint);
            return;
        }

        prevPath.Add(curPoint);
        foreach (var neighbor in ((AdjacencyRule)Distance.Manhattan).Neighbors(curPoint))
        {
            if (!_grid.Contains(neighbor))
                continue;
            
            if (prevPath.Contains(neighbor))
                continue;
            
            if (_grid[neighbor] - _grid[curPoint] != 1)
                continue;
            
            GetTrailEndpoints(prevPath, neighbor, depth, endpoints);
        }
        prevPath.Remove(curPoint);
    }
}
