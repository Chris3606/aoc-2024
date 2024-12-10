namespace AdventOfCode;

public readonly record struct Equation(long TestValue, int[] Operands)
{
    public bool CanBeTrue(bool useConcats)
        => CanBeTrue(TestValue, 0, Operands, useConcats);

    private static bool CanBeTrue(long testValue, long aggregate, ReadOnlySpan<int> operands, bool useConcats)
    {
        while (true)
        {
            if (aggregate > testValue)
                return false;

            if (aggregate == testValue && operands.Length == 0)
                return true;

            if (operands.Length == 0)
                return false;

            bool multOrAdd = CanBeTrue(testValue, aggregate + operands[0], operands[1..], useConcats) 
                             || CanBeTrue(testValue, (aggregate == 0 ? 1 : aggregate) * operands[0], operands[1..], useConcats);
            if (multOrAdd || !useConcats)
                return multOrAdd;

            aggregate = long.Parse(aggregate + operands[0].ToString());
            operands = operands[1..];
        }
    }
}

public sealed class Day07 : BaseDay
{
    private readonly List<Equation> _equations;

    public Day07()
    {
        _equations = [];
        foreach (var line in File.ReadAllLines(InputFilePath))
        {
            var splitData = line.Split(": ");
            if (splitData.Length != 2)
                throw new ArgumentException($"Invalid input: {line}");
            
            _equations.Add(
                new Equation(
                    long.Parse(splitData[0]), 
                    splitData[1].ParseList(' ', int.Parse).ToArray()));
        }
    }

    public override ValueTask<string> Solve_1()
        => new(
            _equations
                .Where(eq => eq.CanBeTrue(false))
                .Sum(eq => eq.TestValue)
                .ToString());

    public override ValueTask<string> Solve_2()
        => new(
            _equations
                .Where(eq => eq.CanBeTrue(true))
                .Sum(eq => eq.TestValue)
                .ToString());

}
