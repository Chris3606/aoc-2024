namespace AdventOfCode;

/// <summary>
/// Utility (extension) methods for common AoC operations.
/// </summary>
public static class Utility
{
    /// <summary>
    /// Given a sequence, return a histogram which maps each key to the number of times it occurs in the list.
    /// </summary>
    /// <param name="value">The list to convert.</param>
    /// <typeparam name="T">The type of items in the list.</typeparam>
    /// <returns>A dictionary mapping each item in the original list to the number of times it occurs.</returns>
    public static Dictionary<T, int> ToHistogram<T>(this IReadOnlyList<T> value)
        where T : notnull
    {
        var dictionary = new Dictionary<T, int>();
        foreach (var element in value)
            dictionary[element] = dictionary.GetValueOrDefault(element, 0) + 1;
        
        return dictionary;
    }
    
    /// <summary>
    /// Parse a list of type T, separated by the given character, and using the function given to convert elements.
    /// </summary>
    /// <remarks>
    /// The intent is to take a string of a format like "1 2 3 4 5" and enable you to convert it to a list of the
    /// elements 1, 2, 3, 4, and 5.
    /// </remarks>
    /// <param name="value">String to parse elements from.</param>
    /// <param name="separator">The separator of the elements.</param>
    /// <param name="parser">A parser function that turns strings into the appropriate type.</param>
    /// <param name="splitOptions">Options to use during splitting.</param>
    /// <typeparam name="T">Type of items to parse.</typeparam>
    /// <returns>An enumerator of the elements.</returns>
    public static IEnumerable<T> ParseList<T>(this string value, char separator, Func<string, T> parser, StringSplitOptions splitOptions = StringSplitOptions.RemoveEmptyEntries)
        => value.Split(separator, splitOptions).Select(parser);
}