using SadRogue.Primitives;

namespace AdventOfCode;

public readonly record struct Arcade(Point ButtonA, Point ButtonB, Point Prize);

public sealed class Day13 : BaseDay
{
    private readonly List<Arcade> _arcades;

    public Day13()
    {
        var input = File.ReadAllText(InputFilePath);
        var arcadeData = input.Replace("\r", "").Split("\n\n");
        _arcades = [];
        
        foreach (var arcade in arcadeData)
        {
            var lines = arcade.Split("\n");
            var buttonAData = lines[0].Split(": ")[1];
            var buttonBData = lines[1].Split(": ")[1];
            var prizeData = lines[2].Split(": ")[1];
            
            _arcades.Add(
                new Arcade(
                    PointFromInput(buttonAData), 
                    PointFromInput(buttonBData), 
                    PointFromInput(prizeData)));
        }
    }

    public override ValueTask<string> Solve_1()
    {
        int tokens = 0;
        foreach (var arcade in _arcades)
        {
            int cheapest = int.MaxValue;
            for (int buttonAPresses = 0; buttonAPresses < 100; buttonAPresses++)
            {
                for (int buttonBPresses = 0; buttonBPresses < 100; buttonBPresses++)
                {
                    if (arcade.ButtonA * buttonAPresses + arcade.ButtonB * buttonBPresses == arcade.Prize)
                        cheapest = Math.Min(cheapest, buttonAPresses * 3 + buttonBPresses);
                }
            }

            if (cheapest != int.MaxValue)
                tokens += cheapest;
        }
        
        return new(tokens.ToString());
    }

    public override ValueTask<string> Solve_2() => throw new NotImplementedException();

    private static Point PointFromInput(string input)
    {
        var coordData = input.Split(", ");
        return new Point(int.Parse(coordData[0][2..]), int.Parse(coordData[1][2..]));
    }
}
