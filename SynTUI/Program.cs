namespace SynTUI
{
    internal class Program
    {
        public static bool IsRunning { get; set; } = true;
        static void Main(string[] args)
        {
            using var pen = ConsolePen.PickUp();
            Loop(pen);
            
        }
        static void Loop(ConsolePen pen)
        {
            pen.CursorVisible = false;
            pen.SetTitle("Clock");
            while (IsRunning)
            {
                string time = DateTime.Now.ToLongTimeString();
                pen.Move((pen.Width / 2) - (time.Length / 2), pen.Height / 2).Print(time);
                pen.Update();
                Thread.Sleep(250);
                pen.Clear();
            }
        }
    }
}
