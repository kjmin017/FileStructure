/*
Creating address
���ڿ��� �ƽ�Ű�ڵ�� �ٲپ� �ּҷ� ����ϴ� hash function�� ��� prefix n bits�� address�� ����ϴµ� 
�̴� collision�� ���� �߻���Ű�� ������ �ȴ�. ���� prefix���� suffix�� ����Ͽ� �ּҸ� ���ϱ� ���� reverse�� �����Ѵ�.

int MakeAddress(char* key, int depth)
{
	int retval = 0;
	int mask = 1;
	int hashVal = Hash(key);
	// reverse the bits
	for (int j = 0; j < depth; ++j)
	{
		retval = retval << 1;
		int lowbit = hashVal & mask;
		retval = retval | lowbit;
		hashVal = hashVal >> 1;
	}
	return retval;
}


Bucket Class
class Bucket: public TextIndex
{
protected:
	// access to Bucket members is only through class Directory
	Bucket(Directory & dir, int maxKeys = defaultMaxKeys);
	int Insert(char* key, int recAddr);
	int Remove(char* key);
	Bucket* Split(); // split the bucket and redistribute the keys
	// calculate the range of a new (split) bucket
	int NewRange(int& newStart, int& newEnd);
	int Redistribute(Bucket& newBucket);
	int FindBuddy();
	int TryCombine(); // atempt to combine buckets
	int Combine(Bucket* buddy, int buddyIndex);
	int Depth;
	Directory & Dir; // directory that contains the bucket
	int BucketAddr;
	ostream& Print(ostream&);
	friend class Directory;
	friend class BucketBuffer;
};


Directory Class
class Directory
{
public:
	Directory(int maxBucketKeys = -1);
	~Directory();
	int Open(char* name);
	int Create(char* name);
	int Close();
	int Insert(char* key, int recAddr);
	int Remove(char* key);
	int Search(char* key);
	ostream& Print(ostream& stream);
protected:
	int Depth; // global depth
	int NumCells; // 2**(global depth)
	int * BucketAddr;

	int DoubleSize();
	int Collapse();
	int InsertBucket(int bucketAddr, int first, int last);
	int RemoveBucket(int bucketIndex, int depth);
	int Find(char* key);
	int StoreBucket(Bucket* bucket);
	int LoadBucket(BUcket* bucket, int bucketAddr);

	int MaxBucketKeys;
	BufferFile * DirectoryFile;
	LenghthFieldBuffer * DirectoryBuffer;
	Bucket * CurrentBucket;
	BucketBuffer * theBucketBuffer;
	BufferFile * BucketFile;
	int Pack() const;
	int Unpack();
	Bucket * PrintBucket;

	friend class Bucket;
};




Extendible hashing - Search
hash function���� ���� ������� prefix d bits�� ��´�.
�� ���� �ش��ϴ� dircectory�� ���� �����͸� ã�´�.
�����Ͱ� ����Ű�� ��Ŷ���� ���ڵ带 ã�´�.


Extendible hashing - Insert
hash function���� ���� ������� prefix d bits�� ��´�.
�� ���� �ش��ϴ� directory�� ���� �����͸� ã�´�.
�����Ͱ� ����Ű�� ��Ŷ�� ���ڵ带 �����Ѵ�.
�̹� ��Ŷ�� full�̶�� overflow(collision)�� �߻��Ѵ�. ���� directory�� ũ�⸦ �� ��� ������Ű�� split�� �����Ѵ�.
�ش� ��Ŷ�� ������ ������ ��Ŷ�� �״�� �д�. �� �߰��� directory entry�� �����ʹ� �߰����־�� �Ѵ�.
split�� �����ϰ� ���� recursive�ϰ� directory�� Insert�� �ٽ� �ѹ� �����Ѵ�.
Bucket * Bucket::Split()
{
	int newStart, newEnd;
	if(Depth == Dir.Depth)
		Dir.DoubleSize();
	Bucket * newBucket = new Bucket(Dir, MaxKeys);
	Dir.StoreBucket(newBucket);
	NewRange(newStart, newEnd);
	Dir.InsertBucket(newBUcket->BucketAddr, newStart, newEnd);
	Depth++;
	newBucket->Depth = Depth;
	Redistribute(*newBucket);
	Dir.StoreBucket(this);
	Dir.StoreBucket(newBucket);
	return newBucket;
}


Extendible hahing - Delete
hash fucntion���� ���� ������� prefix d bits�� ��´�.
�� ���� �ش��ϴ� directory�� ���� �����͸� ã�´�.
�����Ͱ� ����Ű�� ��Ŷ���� ���ڵ带 �����Ѵ�.
���� �ش� bucket�� ���ڵ� ���� buddy bucket�� ���ڵ� ���� ���� ��Ŷ�� size ���϶�� combine�� �����Ѵ�.
buddy bucket�� bucket�� �ּҰ� ������ �� bit�� �ٸ��� �������� �� ���� bucket�� ���Ѵ�.
local depth�� global depth�� ������ buddy bucket�� �����Ѵ�.
int Bucket::FindBuddy()
{
	if(Dir.Depth == 0) return -1;
	if(Depth < Dir.Depth) return -1;
	int sharedAddress = MakeAddress(Keys[0], Depth);
	return sharedAddress ^ 1; // exclusive or with low bit
}

int Bucket::TryCombine()
{
	int result;
	int buddyIndex = FindBuddy();
	if(buddyIndex == -1) return 0; // no combination possible(no buddy)
	// load buddy bucket into memory
	int buddyAddr = Dir.BucketAddr[buddyIndex];
	Bucket* buddyBucket = new Bucket(Dir, MaxKeys);
	Dir.LoadBucket(buddyBucket, buddyAddr);
	// if the sum of the sizes of the buckets is too big, return
	if (NumKeys + buddyBucket->NumKeys > MaxKeys) return 0;
	Combine(buddyBucket, buddyIndex); // collapse the 2 buckets
	result = Dir.Collapse();
	if(result) TryCombine();
	reutnr 1;
}

int Bucket::Combine(Bucket* buddy, int buddyIndex)
{
	int result;
	for(int i = 0; i < buddy->NumKeys; i++)
	{// insert the key of the buddy into this
		result = Insert(buddy->Keys[i], buddy->RecAddrs[i];
		if(!result) return 0;
	}
	Depth --;
	Dir.RemoveBucket(buddyIndex, Depth);
	return 1;
}


// if collapse is possible, reduce size by half
int Directory::Collapse()
{
	if(Depth == 0) return 0;
	for(int i = 0; i < NumCells; i += 2)
		if(BucketAddr[i] != BucketAddr[i+1]) return 0;
	int newSize = NumCells / 2;
	int* newAddrs = new int[newSize];
	for(int j = 0; j < newSize; j++)
		newAddrs[j] = BucketAddr[j*2];
	delete BucketAddr;
	BucketAddr = newAddrs;
	Depth--;
	NumCells = newSize;
	return 1;
}
*/