using System.Text.RegularExpressions;

namespace AdventOfCode;

public readonly record struct Token<T>(int Index, T Value);

public sealed partial class Day03 : BaseDay
{
    private readonly string _input;

    public Day03()
    {
        _input = File.ReadAllText(InputFilePath);
    }

    public override ValueTask<string> Solve_1()
    {
        var multiplications = MultiplicationRegex().Matches(_input);
        
        int simulationResult = SimulateProgram(
            multiplications.Select(
                m => new Token<(int, int)>(
                    m.Index,
                    (int.Parse(m.Groups[1].Value), int.Parse(m.Groups[2].Value)))).ToArray(), 
            Array.Empty<Token<string>>());
        return new(simulationResult.ToString());
    }

    public override ValueTask<string> Solve_2()
    {
        
        var multiplications = MultiplicationRegex().Matches(_input);
        var conditionals = ConditionalRegex().Matches(_input);
    
        int simulationResult = SimulateProgram(
            multiplications.Select(
                m => new Token<(int, int)>(
                    m.Index,
                    (int.Parse(m.Groups[1].Value), int.Parse(m.Groups[2].Value)))).ToArray(), 
            conditionals.Select(m => new Token<string>(m.Index, m.Groups[1].Value)).ToArray());
        return new(simulationResult.ToString());
    }

    private static int SimulateProgram(
        IReadOnlyList<Token<(int o1, int o2)>> multiplications,
        IReadOnlyList<Token<string>> conditionals)
    {
        bool multiplicationsEnabled = true;
        int currentlyAppliedConditionalIdx = 0;

        int sum = 0;
        foreach (var (index, (o1, o2)) in multiplications)
        {
            // Apply any conditionals that come before this multiplication
            while (currentlyAppliedConditionalIdx < conditionals.Count &&
                   conditionals[currentlyAppliedConditionalIdx].Index < index)
            {
                multiplicationsEnabled = conditionals[currentlyAppliedConditionalIdx].Value switch
                {
                    "do" => true,
                    "don't" => false,
                    _ => throw new Exception($"Unexpected conditional: {conditionals[currentlyAppliedConditionalIdx].Value}")
                };
                currentlyAppliedConditionalIdx++;
            }
            
            // Add in multiplication result as needed
            if (multiplicationsEnabled)
                sum += o1 * o2;
        }

        return sum;
    }

    [GeneratedRegex(@"mul\((\d+),(\d+)\)")]
    private static partial Regex MultiplicationRegex();
    
    [GeneratedRegex(@"(do|don't)\(\)")]
    private static partial Regex ConditionalRegex();
}
