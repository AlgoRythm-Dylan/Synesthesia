namespace SynTUI
{
    internal class WinAudioAPI
    {
        private float[] OutputBuffer;
        public WinAudioAPI()
        {
            OutputBuffer = new float[2048];
        }
        public void Start()
        {
            WinAudioLib.SynBegin(2048);
        }
        public float[] Update()
        {
            WinAudioLib.SynUpdate(OutputBuffer);
            return OutputBuffer;
        }
        public void End()
        {
            WinAudioLib.SynEnd();
        }
    }
}
