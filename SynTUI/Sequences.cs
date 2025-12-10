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
        public static string SoftReset
        {
            get => $"{Escape}[!p";
        }
        public static string LineDrawMode
        {
            get => $"{Escape}(0";
        }
        public static string ASCIIMode
        {
            get => $"{Escape}(B";
        }
        public static string Underline
        {
            get => $"{Escape}[4m";
        }
        public static string Negative
        {
            get => $"{Escape}[7m";
        }
        public static string DefaultAttributes
        {
            get => $"{Escape}[0m";
        }
    }
}
