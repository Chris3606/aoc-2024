namespace AdventOfCode;

public sealed class Day11 : BaseDay
{
    private readonly IReadOnlyList<long> _originalNumbers;

    public Day11()
    {
        _originalNumbers = File.ReadAllText(InputFilePath).ParseList(' ', long.Parse).ToList();
    }

    public override ValueTask<string> Solve_1()
    {
        var list = _originalNumbers.ToList();
        var newList = new List<long>();
        for (int i = 0; i < 25; i++)
        {
            foreach (long elem in list)
            {
                if (elem == 0)
                    newList.Add(1);
                else if (elem.ToString().Length % 2 == 0)
                {
                    var digits = elem.ToString();
                    newList.Add(long.Parse(digits[0..(digits.Length / 2)]));
                    newList.Add(long.Parse(digits[(digits.Length / 2)..]));
                }
                else
                    newList.Add(elem * 2024);
            }

            (list, newList) = (newList, list);
            newList.Clear();
        }

        return new(list.Count.ToString());
    }

    public override ValueTask<string> Solve_2() => throw new NotImplementedException();
}
