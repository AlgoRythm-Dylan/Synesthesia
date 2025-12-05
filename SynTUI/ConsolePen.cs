using System.Text;

namespace SynTUI
{
    internal class ConsolePen : IDisposable
    {
        public int Width { get; private set; }
        public int Height { get; private set; }
        private ConsoleCell[] Cells { get; set; }
        public int PositionX { get; set; } = 0;
        public int PositionY { get; set; } = 0;
        private List<string> Commands = new();
        public bool CursorVisible
        {
            set
            {
                if (value)
                {
                    Commands.Add(Sequences.CursorOn);
                }
                else
                {
                    Commands.Add(Sequences.CursorOff);
                }
            }
        }
        private ConsolePen()
        {
            Resize();
            Clear();
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
        protected void Resize()
        {
            int newWidth = Console.WindowWidth;
            int newHeight = Console.WindowHeight;
            if(newWidth != Width || newHeight != Height)
            {
                Width = newWidth;
                Height = newHeight;
            }
            Cells = new ConsoleCell[Width * Height];
            for(int i = 0; i < Cells.Length; i++) Cells[i] = new ConsoleCell();
        }
        public void ResetPosition()
        {
            PositionX = 0;
            PositionY = 0;
        }
        public ConsolePen Move(int x, int y)
        {
            PositionX = x;
            PositionY = y;
            return this;
        }
        public bool PositionIsValid()
        {
            return (PositionY * Width) + PositionX < Cells.Length;
        }
        public void AdvancePosition()
        {
            PositionX++;
            if(PositionX >= Width)
            {
                PositionX = 0;
                PositionY++;
            }
        }
        public ConsoleCell CellAtPosition()
        {
            return Cells[(PositionY * Width) + PositionX];
        }
        public void Clear()
        {
            Resize();
            for(int i = 0; i < Cells.Length; i++)
            {
                Cells[i].Reset();
            }
            ResetPosition();
        }
        public void Update()
        {
            StringBuilder renderer = new();
            renderer.Append(Sequences.Clear);

            foreach(var command in Commands){
                renderer.Append(command);
            }
            Commands.Clear();

            bool needToMove = true;
            for(int row = 0; row < Height; row++)
            {
                for(int col = 0; col < Width; col++)
                {
                    var cellAt = Cells[(row * Width) + col];
                    if (cellAt.IsEmpty)
                    {
                        needToMove = true;
                        continue;
                    }

                    if (needToMove)
                    {
                        renderer.Append(Sequences.MoveCursor(col, row));
                        needToMove = false;
                    }
                    renderer.Append(cellAt.Render());
                }
            }
            Console.Write(renderer.ToString());
            Console.Out.Flush();
        }
        public bool WriteCell(string content)
        {
            if (PositionIsValid())
            {
                var thisCell = CellAtPosition();
                thisCell.Content = content;
                AdvancePosition();
                return true;
            }
            return false;
        }
        public void Print(string content)
        {
            for (int cursor = 0; cursor < content.Length; cursor++)
            {
                if (!WriteCell(content.Substring(cursor, 1)))
                {
                    break;
                }
            }
        }
        public void SetTitle(string title)
        {
            Commands.Add(Sequences.Title(title));
        }
    }
}
