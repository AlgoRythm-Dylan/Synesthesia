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
            pen.Title = "Clock";
            while (IsRunning)
            {
                Draw(pen);
                Thread.Sleep(250);
                pen.Clear();
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
            string time = DateTime.Now.ToLongTimeString();
            string date = DateTime.Now.ToLongDateString();
            int centerVertical = pen.Height / 2;
            pen.Move((pen.Width / 2) - (time.Length / 2), centerVertical - 1).Print(time);
            pen.Move((pen.Width / 2) - (date.Length / 2), centerVertical).Print(date);
            pen.Update();
        }
    }
}
