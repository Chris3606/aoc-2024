using SadRogue.Primitives;

namespace AdventOfCode;

public sealed class Day05 : BaseDay
{
    private readonly Dictionary<int, List<int>> _dependencyGraph;
    private readonly List<List<int>> _updates;

    public Day05()
    {
        var input = File.ReadAllText(InputFilePath).Replace("\r", "");
        var parts = input.Split("\n\n");
        if (parts.Length != 2)
            throw new ArgumentException("Invalid input.");
        
        _dependencyGraph = new Dictionary<int, List<int>>();
        foreach (var rule in parts[0].ToLines())
        {
            var deps = rule.Split('|');
            if (deps.Length != 2)
                throw new ArgumentException("Invalid input.");

            int depender = int.Parse(deps[1]);
            int dependency = int.Parse(deps[0]);
            
            if (!_dependencyGraph.ContainsKey(depender))
                _dependencyGraph[depender] = [];
            
            _dependencyGraph[depender].Add(dependency);
        }

        _updates = parts[1]
            .ToLines()
            .Select(s => s.ParseList(',', int.Parse).ToList())
            .ToList();
    }

    public override ValueTask<string> Solve_1()
        => new(_updates
            .Where(i => IsCorrectOrder(i, _dependencyGraph))
            .Sum(l => l[l.Count / 2])
            .ToString());

    public override ValueTask<string> Solve_2()
    {
        int sumMiddlePages = 0;
        foreach (var update in _updates.Where(i => !IsCorrectOrder(i, _dependencyGraph)))
        {
            var resolver = new DependencyResolver(update, _dependencyGraph);
            var correctUpdate = new List<int>();
            foreach (var page in update)
                correctUpdate.AddRange(resolver.GetDependencyTree(page).Where(i => !correctUpdate.Contains(i)));

            sumMiddlePages += correctUpdate[correctUpdate.Count / 2];
        }
        
        return new(sumMiddlePages.ToString());
    }

    private static bool IsCorrectOrder(IReadOnlyList<int> update, IReadOnlyDictionary<int, List<int>> dependencyGraph)
    {
        var updateValues = update.ToHashSet();
        var seenValues = new HashSet<int>();
        foreach (var page in update)
        {
            // No dependencies, so this can't affect ordering
            if (!dependencyGraph.TryGetValue(page, out var dependencies))
            {
                seenValues.Add(page);
                continue;
            }

            // Check that we've seen each dependency before (so long as it's in the list somewhere)
            if (dependencies.Any(i => updateValues.Contains(i) && !seenValues.Contains(i)))
                return false;
            
            seenValues.Add(page);
        }

        return true;
    }
}

class DependencyResolver(IEnumerable<int> update, IReadOnlyDictionary<int, List<int>> dependencyGraph)
{
    private readonly HashSet<int> _updateValues = update.ToHashSet();
    private readonly Dictionary<int, List<int>> _dependencyCache = new();

    public IReadOnlyList<int> GetDependencyTree(int page)
    {
        // If we've already calculated the dependencies for this one before, just return the cached version
        if (_dependencyCache.TryGetValue(page, out var existingDeps))
            return existingDeps.AsReadOnly();
        
        // There's only work to do if the value we've given is in the original list; otherwise its a dependency
        // that's irrelevant
        var dependencies = new List<int>();
        if (_updateValues.Contains(page))
        {
            // There are dependencies, so we'll need to resolve them recursively
            if (dependencyGraph.TryGetValue(page, out var dependenciesGraph))
            {
                foreach (var dependency in dependenciesGraph)
                {
                    var subtree = GetDependencyTree(dependency);
                    dependencies.AddRange(subtree.Where(i => !dependencies.Contains(i)));
                }
            }
            
            // Otherwise, there's no dependencies (or we already added them); so add ourselves if we haven't
            // already
            if (!dependencies.Contains(page))
                dependencies.Add(page);
        }
        
        // Cache teh result and return it
        _dependencyCache[page] = dependencies;
        return dependencies.AsReadOnly();
    }
}
