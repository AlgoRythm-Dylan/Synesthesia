namespace SynTUI
{
    internal class ConsoleCell
    {
        protected string _content = "";
        protected bool _empty = true;
        public string Content
        {
            get
            {
                return _content;
            }
            set
            {
                Touch();
                _content = value;
            }
        }
        public bool IsEmpty
        {
            get
            {
                return _empty;
            }
        }
        protected void Touch()
        {
            _empty = false;
        }
        public void Reset()
        {
            _content = "";
            _empty = true;
        }
        public ConsoleCellAttributes Attributes { get; set; } = new();
    }
}
