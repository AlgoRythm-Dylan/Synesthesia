using System.Text;

namespace SynTUI
{
    internal class ConsolePen : IDisposable
    {
        #region Public Properties
        public int Width { get; private set; }
        public int Height { get; private set; }
        public int PositionX { get; set; } = 0;
        public int PositionY { get; set; } = 0;
        public ConsoleCellAttributes Attributes { get; set; } = new();
        #endregion
        #region Private Properties
        private ConsoleCell[] Cells;
        private List<string> Commands = new();
        private string? PreRenderResult = null;
        #endregion
        #region Virtual Properties
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
        public string Title
        {
            set
            {
                Commands.Add(Sequences.Title(value));
            }
        }
        #endregion
        #region Construction and Destruction
        private ConsolePen()
        {
            BufferSizeCheck();
            Clear();
            Console.Write(Sequences.AlternateScreen + Sequences.Clear + Sequences.MoveCursor(0, 0));
        }
        public static ConsolePen PickUp()
        {
            return new ConsolePen();
        }
        public void Dispose()
        {
            Console.Write(Sequences.RegularScreen + Sequences.SoftReset);
        }
        #endregion
        #region Buffer Operations
        protected void BufferSizeCheck()
        {
            Attributes = new();
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
        public void Clear()
        {
            BufferSizeCheck();
            for (int i = 0; i < Cells.Length; i++)
            {
                Cells[i].Reset();
            }
            ResetPosition();
        }
        #endregion
        #region Positioning
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
        #endregion
        #region Positioning Metafunctions
        public bool PositionIsValid()
        {
            return (PositionY * Width) + PositionX < Cells.Length;
        }
        public void AdvancePosition()
        {
            PositionX++;
            if (PositionX >= Width)
            {
                PositionX = 0;
                PositionY++;
            }
        }
        public ConsoleCell CellAtPosition()
        {
            return Cells[(PositionY * Width) + PositionX];
        }
        #endregion
        #region Rendering
        protected string Render()
        {
            StringBuilder renderer = new();
            renderer.Append(Sequences.Clear + Sequences.DefaultAttributes);

            foreach (var command in Commands)
            {
                renderer.Append(command);
            }
            Commands.Clear();

            bool needToMove = true;
            ConsoleCell? lastRenderedCell = null;
            for (int row = 0; row < Height; row++)
            {
                for (int col = 0; col < Width; col++)
                {
                    var cellAt = Cells[(row * Width) + col];

                    if (lastRenderedCell is null || lastRenderedCell.Attributes.CompareTo(cellAt.Attributes) != 0)
                    {
                        if (cellAt.Attributes.IsEmpty)
                        {
                            renderer.Append(Sequences.DefaultAttributes);
                        }
                        else
                        {
                            renderer.Append(cellAt.Attributes.Render());
                        }
                    }

                    lastRenderedCell = cellAt;

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
                    renderer.Append(cellAt.Content);
                }
            }
            return renderer.ToString();
        }
        public void PreRender()
        {
            PreRenderResult = Render();
        }
        public void Update()
        {
            if(PreRenderResult is null)
            {
                Console.Write(Render());
            }
            else
            {
                Console.Write(PreRenderResult);
                PreRenderResult = null;
            }
            Console.Out.Flush();
        }
        #endregion
        #region Writing
        public bool WriteCell(string content)
        {
            if (PositionIsValid())
            {
                var thisCell = CellAtPosition();
                thisCell.Content = content;
                thisCell.Attributes = Attributes;
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
        #endregion
    }
}
