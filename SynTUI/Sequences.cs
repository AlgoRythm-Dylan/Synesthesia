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
            // Positions here are 1-based, so (0, 0) needs to be translated
            // to (1, 1)
            return $"{Escape}[{y+1};{x+1}H";
        }
        public static string Title(string title)
        {
            return $"{Escape}]0;{title}{Terminator}";
        }
        public static string CursorOn
        {
            get => $"{Escape}[?25h";
        }
        public static string CursorOff
        {
            get => $"{Escape}[?25l";
        }
    }
}
