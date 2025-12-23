namespace Syn
{
    public interface IDataBucketDriver
    {
        public float Bucket(ReadOnlySpan<float> data);
    }
}
