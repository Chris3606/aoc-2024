using SadRogue.Primitives;

namespace AdventOfCode;

public sealed class Day09 : BaseDay
{
    private readonly List<int?> _drive;

    public Day09()
    {
        var input = File.ReadAllText(InputFilePath);
        _drive = new List<int?>();
        for (int i = 0; i < _input.Length; i++)
        {
            for (int j = 0; j < _input[i] - '0'; j++)
                _drive.Add(i % 2 == 0 ? i / 2 : null);
        }
    }

    public override ValueTask<string> Solve_1()
    {
        Console.WriteLine(_drive.ExtendToString(separator: " ", elementStringifier: i => i.HasValue ? i.Value.ToString() : "."));
        return new(0.ToString());
    }

    public override ValueTask<string> Solve_2() => throw new NotImplementedException();
}
