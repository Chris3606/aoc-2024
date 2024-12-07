namespace AdventOfCode;

public sealed class Day02 : BaseDay
{
    private readonly List<List<int>> _reports;

    public Day02()
    {
        _reports = File
            .ReadAllLines(InputFilePath)
            .Select(line => line.ParseList(' ', int.Parse).ToList())
            .ToList();
    }

    public override ValueTask<string> Solve_1() => new(_reports.Count(i => IsSafe(i, false)).ToString());

    public override ValueTask<string> Solve_2()
        => new(_reports.Count(i => IsSafe(i, true)).ToString());

    private static bool IsSafe(IReadOnlyList<int> report, bool tryRemovingSingle)
    {
        int diff = report[1] - report[0];
        
        int minDiff = diff >= 0 ? 1 : -3;
        int maxDiff = diff >= 0 ? 3 : -1;
        
        bool safe = report
            .Zip(report.Skip(1))
            .Select(pair => pair.Second - pair.First)
            .All(i => i >= minDiff && i <= maxDiff);

        if (safe || !tryRemovingSingle)
            return safe;

        for (int i = 0; i < report.Count; i++)
        {
            var newList = report.ToList();
            newList.RemoveAt(i);
            if (IsSafe(newList, false))
                return true;
        }

        return safe;
    }
}
