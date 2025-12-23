namespace Syn
{
    public class LinearDataBucketGrouper : IDataBucketGrouper
    {
        public ReadOnlySpan<float> Group(float[] data, int bucketNumber, int totalBucketCount)
        {
            int dataPointsPerBucket = data.Length / totalBucketCount;
            return new(data, dataPointsPerBucket * bucketNumber, dataPointsPerBucket);
        }
    }
}
