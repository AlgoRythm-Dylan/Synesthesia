using System.Diagnostics;

namespace SynTUI
{
    internal class Program
    {
        public static bool IsRunning { get; set; } = true;
        private static Stopwatch RenderFrameSW = Stopwatch.StartNew();
        static void Main(string[] args)
        {
            using var pen = ConsolePen.PickUp();
            Loop(pen);
            
        }
        static void Loop(ConsolePen pen)
        {
            pen.CursorVisible = false;
            pen.Title = "Clock";
            Draw(pen);
            while (IsRunning)
            {
                if(RenderFrameSW.ElapsedMilliseconds >= 250)
                {
                    Draw(pen);
                    pen.Clear();
                    RenderFrameSW.Restart();
                }
                while (Console.KeyAvailable)
                {
                    if(Console.ReadKey().KeyChar == 'q')
                    {
                        IsRunning = false;
                    }
                }
                // Realistically, we only need to poll every 25ms or so
                // for a console application
                Thread.Sleep(25);
            }
        }
        static void Draw(ConsolePen pen)
        {
            string time = DateTime.Now.ToLongTimeString();
            string date = DateTime.Now.ToLongDateString();
            int centerVertical = pen.Height / 2;
            pen.Attributes.Foreground = ConsoleColor.Blue;
            pen.Attributes.HasBrightForeground = true;
            pen.Move((pen.Width / 2) - (time.Length / 2), centerVertical - 1).Print(time);
            pen.Attributes = new();
            pen.Move((pen.Width / 2) - (date.Length / 2), centerVertical).Print(date);
            pen.Update();
        }
    }
}
