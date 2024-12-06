namespace AdventOfCode;

public sealed class Day01 : BaseDay
{
    private readonly List<int> _list1;
    private readonly List<int> _list2;

    public Day01()
    {
        _list1 = [];
        _list2 = [];

        foreach (var line in File.ReadAllLines(InputFilePath))
        {
            var split = line.Split(' ');
            _list1.Add(int.Parse(split[0]));
            _list2.Add(int.Parse(split[^1]));
        }
    }

    public override ValueTask<string> Solve_1() 
        => new(_list1.Order().Zip(_list2.Order()).Sum(val => Math.Abs(val.First - val.Second)).ToString());

    public override ValueTask<string> Solve_2()
    {
        var histogram = _list2.ToHistogram();
        
        return new ValueTask<string>(_list1.Select(x => x * histogram.GetValueOrDefault(x)).Sum().ToString());
    }
}
