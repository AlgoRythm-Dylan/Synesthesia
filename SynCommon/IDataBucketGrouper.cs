namespace Syn
{
    public interface IDataBucketGrouper
    {
        public ReadOnlySpan<float> Group(float[] data, int bucketNumber, int totalBucketCount);
    }
}
