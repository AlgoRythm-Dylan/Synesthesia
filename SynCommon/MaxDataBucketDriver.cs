namespace Syn
{
    public class MaxDataBucketDriver : IDataBucketDriver
    {
        public float Bucket(ReadOnlySpan<float> data)
        {
            if(data.Length == 0)
            {
                return 0;
            }
            float max = data[0];
            for(int i = 0; i < data.Length; i++)
            {
                max = Math.Max(data[i], max);
            }
            return max;
        }
    }
}
