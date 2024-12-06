namespace AdventOfCode;

public sealed class Day02 : BaseDay
{
    private readonly List<int[]> _reports;

    public Day02()
    {
        _reports = File
            .ReadAllLines(InputFilePath)
            .Select(line => line.ParseList(' ', int.Parse).ToArray())
            .ToList();
    }

    public override ValueTask<string> Solve_1() => new(_input.Length.ToString());

    public override ValueTask<string> Solve_2() => throw new NotImplementedException();
}
