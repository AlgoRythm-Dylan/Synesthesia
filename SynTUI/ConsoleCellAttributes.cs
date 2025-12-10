namespace SynTUI
{
    internal class ConsoleCellAttributes : IComparable<ConsoleCellAttributes>
    {
        public bool HasBrightForeground { get; set; } = false;
        public bool HasBrightBackground { get; set; } = false;
        public bool IsUnderline { get; set; } = false;
        public bool IsNegative { get; set; } = false;
        public ConsoleColor? Foreground { get; set; } = null;
        public ConsoleColor? Background { get; set; } = null;

        public int CompareTo(ConsoleCellAttributes? other)
        {
            if(other is null)
            {
                return -1;
            }
            else
            {
                if(IsUnderline == other.IsUnderline &&
                   HasBrightBackground == other.HasBrightBackground &&
                   HasBrightForeground == other.HasBrightForeground &&
                   IsNegative == other.IsNegative &&
                   Foreground == other.Foreground &&
                   Background == other.Background)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
        }
        public bool IsEmpty
        {
            get
            {
                return IsUnderline == false &&
                       HasBrightBackground == false &&
                       HasBrightForeground == false &&
                       IsNegative == false &&
                       Foreground == null &&
                       Background == null;
            }
        }
        public string Render()
        {
            string answer = "";
            if (IsUnderline)
            {
                answer += Sequences.Underline;
            }
            if (IsNegative)
            {
                answer += Sequences.Negative;
            }
            if (Foreground is not null)
            {
                uint attrCode = 30 + (uint)Foreground.Value;
                if (HasBrightForeground)
                {
                    attrCode += 60;
                }
                answer += $"{Sequences.Escape}[{attrCode}m";
            }
            if (Background is not null)
            {
                uint attrCode = 40 + (uint)Background.Value;
                if (HasBrightForeground)
                {
                    attrCode += 60;
                }
                answer += $"{Sequences.Escape}[{attrCode}m";
            }
            return answer;
        }
    }
}
