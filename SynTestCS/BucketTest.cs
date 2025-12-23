using Syn;

namespace SynTestCS
{
    [TestClass]
    public sealed class BucketTest
    {
        [TestMethod]
        public void TestDefaultBucket()
        {
            DataBucketer bucketer = new();
            bucketer.SetBucketCount(2);
            var buckets = bucketer.Bucket([ 1, 2, 3, 4, 5, 6 ]);
            Assert.HasCount(2, buckets);
            Assert.AreEqual(3, buckets[0]);
            Assert.AreEqual(6, buckets[1]);
        }
    }
}
