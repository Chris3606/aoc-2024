namespace AdventOfCode;

public sealed class Day11 : BaseDay
{
    private readonly IReadOnlyList<long> _originalNumbers;

    public Day11()
    {
        _originalNumbers = File.ReadAllText(InputFilePath).ParseList(' ', long.Parse).ToList();
    }

    public override ValueTask<string> Solve_1()
     => new(_originalNumbers.Sum(i => GetNumbersRecursive(i, 25, new())).ToString());

    public override ValueTask<string> Solve_2()
        => new(_originalNumbers.Sum(i => GetNumbersRecursive(i, 75, new())).ToString());

    private static long GetNumbersRecursive(long number, int iterations, Dictionary<(long num, int iterations), long> cache)
    {
        if (iterations == 0)
            return 1;
        
        if (cache.ContainsKey((number, iterations)))
            return cache[(number, iterations)];

        if (number == 0)
            cache[(number, iterations)] = GetNumbersRecursive(1, iterations - 1, cache);
        
        else if (number.ToString().Length % 2 == 0)
        {
            var digits = number.ToString();

            cache[(number, iterations)] =
                GetNumbersRecursive(long.Parse(digits[..(digits.Length / 2)]), iterations - 1, cache) +
                GetNumbersRecursive(long.Parse(digits[(digits.Length / 2)..]), iterations - 1, cache);
        }
        else
            cache[(number, iterations)] = GetNumbersRecursive(number * 2024, iterations - 1, cache);
        
        return cache[(number, iterations)];
    }
}
