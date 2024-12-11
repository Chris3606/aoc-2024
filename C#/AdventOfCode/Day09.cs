using SadRogue.Primitives;

namespace AdventOfCode;

public sealed class Day09 : BaseDay
{
    private readonly List<int?> _drive;

    public Day09()
    {
        var input = File.ReadAllText(InputFilePath);
        _drive = [];
        for (int i = 0; i < input.Length; i++)
        {
            for (int j = 0; j < input[i] - '0'; j++)
                _drive.Add(i % 2 == 0 ? i / 2 : null);
        }
    }

    public override ValueTask<string> Solve_1()
    {
        // Console.WriteLine(_drive.ExtendToString(separator: " ", elementStringifier: i => i.HasValue ? i.Value.ToString() : "."));

        var drive = _drive.ToList();
        int nextFileBlock = _drive.Count - 1;
        int nextFreeSpace = 0;

        while (nextFileBlock >= nextFreeSpace)
        {
            // Find next valid file block
            while (nextFileBlock >= 0 && !drive[nextFileBlock].HasValue)
                nextFileBlock--;
            if (nextFileBlock < 0)
                break;
            
            // Find next eligible free space
            while (nextFreeSpace < nextFileBlock && drive[nextFreeSpace].HasValue)
                nextFreeSpace++;

            if (nextFreeSpace >= nextFileBlock)
                break;
            
            // Move block down
            drive[nextFreeSpace] = drive[nextFileBlock];
            drive[nextFileBlock] = null;
        }
        
        
        return new(GetChecksum(drive).ToString());
    }

    public override ValueTask<string> Solve_2()
    {
        var drive = _drive.ToList();
        
        int endFileBlock = _drive.Count - 1;
        while (endFileBlock >= 0)
        {
            // Find end of next valid file block
            while (endFileBlock >= 0 && !drive[endFileBlock].HasValue)
                endFileBlock--;
            if (endFileBlock < 0)
                break;
            
            // Find start of the current file block
            int startFileBlock = endFileBlock;
            
            while (startFileBlock >= 0 && drive[startFileBlock] == drive[endFileBlock])
                   startFileBlock--;
            startFileBlock++;
            
            int fileSize = endFileBlock - startFileBlock + 1;
            
            // Look for a free space block big enough
            for (int i = 0; i < startFileBlock; i++)
            {
                if (drive[i].HasValue)
                    continue;
                
                // Find end
                int j = i + 1;
                for (; j < startFileBlock && !drive[j].HasValue; j++)
                {
                }

                int freeSize = j - i;
                if (freeSize < fileSize)
                {
                    i = j;
                }
                else // Block is big enough, move file
                {
                    for (int idx = 0; idx < fileSize; idx++)
                    {
                        drive[i + idx] = drive[startFileBlock + idx];
                        drive[startFileBlock + idx] = null;
                    }
                }
            }
            
            endFileBlock = startFileBlock - 1;
        }
        
        return new(GetChecksum(drive).ToString());
    }

    private static long GetChecksum(IReadOnlyList<int?> drive)
    {
        long checksum = 0;

        for (int i = 0; i < drive.Count; i++)
        {
            var val = drive[i];
            if (val.HasValue)
                checksum += val.Value * i;
        }
        
        return checksum;
    }
}
