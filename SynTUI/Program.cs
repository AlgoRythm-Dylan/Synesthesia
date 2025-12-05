namespace SynTUI
{
    internal class Program
    {
        static void Main(string[] args)
        {
            using var pen = ConsolePen.PickUp();
            Thread.Sleep(2000);
        }
    }
}
