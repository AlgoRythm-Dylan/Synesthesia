using System.Runtime.InteropServices;

namespace SynTUI
{
    internal class WinAudioLib
    {
        [DllImport("SynLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SynBegin(ulong bufferSize);
        [DllImport("SynLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SynUpdate([In, Out] float[] outBuffer);
        [DllImport("SynLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SynEnd();
    }
}
