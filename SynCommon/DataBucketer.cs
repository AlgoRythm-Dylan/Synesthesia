namespace Syn
{
    public class DataBucketer
    {
        public const int DEFAULT_BUCKET_COUNT = 32;
        public float[] Buckets { get; private set; }
        public IDataBucketDriver Driver { get; set; } = new MaxDataBucketDriver();
        public IDataBucketGrouper Grouper { get; set; } = new LinearDataBucketGrouper();

        public DataBucketer()
        {
            Buckets = new float[DEFAULT_BUCKET_COUNT];
        }
        public void SetBucketCount(int count)
        {
            if(count != Buckets.Length)
            {
                Buckets = new float[count];
            }
        }
        public float[] Bucket(float[] inputs)
        {
            for(int i = 0; i < Buckets.Length; i++)
            {
                Buckets[i] = Driver.Bucket(Grouper.Group(inputs, i, Buckets.Length));
            }
            return Buckets;
        }
    }
}
