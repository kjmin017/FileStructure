/*
Creating address
문자열을 아스키코드로 바꾸어 주소로 사용하는 hash function의 경우 prefix n bits로 address를 사용하는데 
이는 collision을 많이 발생시키는 원인이 된다. 따라서 prefix보다 suffix를 사용하여 주소를 구하기 위해 reverse를 수행한다.

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
hash function으로 나온 결과값의 prefix d bits를 얻는다.
이 값에 해당하는 dircectory로 가서 포인터를 찾는다.
포인터가 가리키는 버킷에서 레코드를 찾는다.


Extendible hashing - Insert
hash function으로 나온 결과값의 prefix d bits를 얻는다.
이 값에 해당하는 directory로 가서 포인터를 찾는다.
포인터가 가리키는 버킷에 레코드를 삽입한다.
이미 버킷이 full이라면 overflow(collision)가 발생한다. 따라서 directory의 크기를 두 배로 증가시키는 split을 수행한다.
해당 버킷을 제외한 나머지 버킷은 그대로 둔다. 단 추가된 directory entry에 포인터는 추가해주어야 한다.
split을 수행하고 나서 recursive하게 directory의 Insert를 다시 한번 수행한다.
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
hash fucntion으로 나온 결과값의 prefix d bits를 얻는다.
이 값에 해당하는 directory로 가서 포인터를 찾는다.
포인터가 가리키는 버킷에서 레코드를 삭제한다.
만약 해당 bucket의 레코드 수와 buddy bucket의 레코드 수의 합이 버킷의 size 이하라면 combine을 수행한다.
buddy bucket은 bucket의 주소가 마지막 한 bit만 다르고 나머지는 다 같은 bucket을 말한다.
local depth와 global depth가 같으면 buddy bucket이 존재한다.
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