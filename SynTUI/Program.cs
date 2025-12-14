using System.Diagnostics;

namespace SynTUI
{
    internal class Program
    {
        public static bool IsRunning { get; set; } = true;
        private static Stopwatch RenderFrameSW = Stopwatch.StartNew();
        private static WinAudioAPI AudioAPI = new();
        static void Main(string[] args)
        {
            using var pen = ConsolePen.PickUp();
            try
            {
                Loop(pen);
            }
            finally
            {
                AudioAPI.End();
            }
        }
        static void Loop(ConsolePen pen)
        {
            pen.CursorVisible = false;
            pen.Title = "Synesthesia Visualizer";
            AudioAPI.Start();
            Draw(pen);
            while (IsRunning)
            {
                if(RenderFrameSW.ElapsedMilliseconds >= 30)
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
            }
        }
        static void Draw(ConsolePen pen)
        {
            var buckets = AudioAPI.Update();
            pen.Print("Buckets[0]: " + buckets[0]);
            pen.Update();
        }
    }
}
