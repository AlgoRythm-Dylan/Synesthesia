namespace SynTUI
{
    internal class Sequences
    {
        public static string Escape
        {
            get => "\x1b";
        }
        public static string Terminator
        {
            get => "\x1b\x5C";
        }
        public static string AlternateScreen
        {
            get => $"{Escape}[?1049h";
        }
        public static string RegularScreen
        {
            get => $"{Escape}[?1049l";
        }
        public static string Clear
        {
            get => $"{Escape}[2J";
        }
        public static string MoveCursor(int x, int y)
        {
            return $"{Escape}[{y};{x}H";
        }
        public static string Title(string title)
        {
            return $"{Escape}]0;{title}{Terminator}";
        }
    }
}
