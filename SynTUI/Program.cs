namespace SynTUI
{
    internal class Program
    {
        static void Main(string[] args)
        {
            using var pen = ConsolePen.PickUp();
            pen.Move(0, 0).Print("Hello world!");
            pen.Move(1, 1).Print("Nice to meet you!!");
            pen.Update();




            Thread.Sleep(20000);
        }
    }
}
