namespace SynTUI
{
    internal class ConsolePen : IDisposable
    {
        private ConsolePen()
        {
            Console.Write(Sequences.AlternateScreen + Sequences.Clear + Sequences.MoveCursor(0, 0));
        }
        public static ConsolePen PickUp()
        {
            return new ConsolePen();
        }
        public void Dispose()
        {
            Console.Write(Sequences.RegularScreen);
        }
    }
}
