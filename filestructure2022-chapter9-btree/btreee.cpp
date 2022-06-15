/*
B-Tree의 특징
B-Tree는 아래에서 위로 동작하는 Upward from the Bottom 형식이다. 인덱스 레코드가 꽉 차있지 않아도 되며, 
overflow가 발생했을 때 split을 통해 node의 레코드를 둘로 나눈다.

또한 leaf node에서 데이터를 가리키고 leaf node를 제외한 나머지 node에서는 다른 node를 가리키는 포인터를 가지고 있다. 
또한 B-Tree의 order는 각 node에서 최대로 가질 수 있는 인덱스 필드의 포인터 개수이다.

order가 m인 B-Tree의 특징은 다음과 같다.
각 node는 최대 m개의 자식을 가질 수 있다.
root node는 leaf node를 제외한 모든 node는 반드시 m/2개의 자식 노드를 가져야 한다.
높이가 1 이상인 B-Tree의 root node는 최소 2개의 자식 node를 가져야 한다.
모든 leaf node는 같은 레벨에 위치해야 한다.

B-Tree algorithm
Find correct leaf L // search
Put data entry onto L // put
	if L has enough space, done!
	else, must split L(into L and a new node L2)
Parent node may overflow
	then push up

객체 지향적 프로그래밍 관점에서의 B-Tree
B-Tree는 인덱스 파일이며 대부분의 B-Tree 연산은 메모리에서 수행한다. 
B-Tree의 일부인 특정한 node를 메모리에 올려서 연산을 수행하는데, 따라서 SimpleIndex 클래스를 상속받은 BTreeNode 클래스를 구현해야 한다.

template <class keyType>
class SimpleIndex
{
public:
	SimpleIndex(int maxKeys = 100, int unique = 1);
	~Simpleindex();
	void Clear();
	int Insert(const keyType key, int recAddr);
	int Remove(const keyType key, const int recAddr = -1);
	int Search(const keyType key, const int recAddr = -1,
		const int exact = 1) const;
	...
protected:
	int MaxKeys;
	int NumKeys;
	keyType* Keys;
	int* RecAddrs;
	int Find(const keyType key, const int recAddr -1,
		const int exact = 1) const;
	...
};
// this is the in-memory version of the BTreeNode
template <class keyType>
class BTreeNode: public SimpleIndex<keyType>
{
public:
	BTreeNode(int maxKeys, int unique = 1);
	int Insert(const keyType key, int recAddr);
	int Remove(const keyType key, int recAddr = -1);
	int LargestKey(); // returns value of largest key
	int Split(BTreeNode<keyType>* newNode); // move keys into newNode
	int Merge(BTreeNode<keyType>* fromNode); // move keys from fromNode
	int UpdateKey(keyType oldKey, keyType newKey, int recAddr = -1);
	int Pack(IOBuffer& buffer) const;
	int Unpack(IOBuffer& buffer);
	static int InitBuffer(FixedFieldBuffer& buffer, int maxKeys,
		int keySize = sizeof(keyType));
protected:
	int MaxBKeys; // maximum number of keys in a node
	friend class BTree<keyType>;
};


각 node에서의 연산 결과는 BTree 클래스로 전달된다. BTree 클래스는 디스크에 있는 B-Tree의 정보를 나타내는 클래스로, 
노드를 선택하여 메모리에 올리고 연산을 수행하는 동작을 정의한다.

template <class keyType>
class BTree
// this is the full version of the BTree
{
public:
	BTree(int order, int keySize = sizeof(keyType), int unique = 1);
  ~BTree();
  //int Open (char * name, int mode);
  int Open (char * name, ios_base::openmode mode);
  //int BTree<keyType>::Open (char * name, ios_base::openmode mode)
  int Create (char * name, ios_base::openmode mode);
  //int Create (char * name, int mode);
  int Close ();
  int Insert (const keyType key, const int recAddr);
  int Remove (const keyType key, const int recAddr = -1);
  int Search (const keyType key, const int recAddr = -1);
  void Print (ostream &);
  void Print (ostream &, int nodeAddr, int level);
protected:
  typedef BTreeNode<keyType> BTNode;// useful shorthand
  BTNode * FindLeaf (const keyType key);
  // load a branch into memory down to the leaf with key
  BTNode * NewNode ();
  BTNode * Fetch(const int recaddr);
  int Store (BTNode *);
  BTNode Root;
  int Height; // height of tree
  int Order; // order of tree
  int PoolSize;
  BTNode ** Nodes; // pool of available nodes
  // Nodes[1] is level 1, etc. (see FindLeaf)
  // Nodes[Height-1] is leaf
  FixedFieldBuffer Buffer;
  RecordFile<BTNode> BTreeFile;
};


BTree에서 Search는 두 단계로 진행된다. 먼저 root에서부터 시작하여 leafnode를 찾는다. 
만약 leafnode를 발견하면 그 node에서 다시 원하는 키값에 해당하는 레코드를 찾는다.

template <class keyType>
int BTree<keyType>::Search(const keyType key, const int recAddr)
{
	BTNode* leafNode;
	leafNode = FindLeaf(key);
	return leafNode -> Search(key, recAddr);
}

// load a branch into memory down to the leaf with key
template <class keyType>
BTreeNode<keyType>* BTree<keyType>::FindLeaf(const keyType key)
{
	int recAddr, level;
	for(level = 1; level < Height; level++) {
		// inexact search
		recAddr = Node[level-1]->Search(key,-1,0);
		Nodes[level]=Fetch(recAddr);
		// Fetch = Read + Unpack
		// Store = Write + Pack
	}
	return Nodes[level-1];
}


Insert는 새로운 데이터를 삽입하는 메서드로, root에서부터 input의 위치를 찾고 그 위치의 node 상태에 따라 다양한 동작들을 수행한다.



Step 1. key를 삽입하기 위해 leaf의 level을 찾는다.
Step 2. node에 빈 공간이 존재하면 새 데이터를 삽입하고 포인터를 업데이트한다.
Step 3. node에 overflow가 발생하면 새로운 node를 생성하여 split을 통해 반씩 나누어 저장한다.
Step 4. split될 때 조상 node에 overflow가 발생하면 마찬가지로 split을 통해 반씩 나누어 저장한다.
Step 5. 만일 root node에서도 overflow가 발생하면 새로운 root node를 생성하여 split한다.

template <class keyType>
int BTree<keyType>::Insert (const keyType key, const int recAddr)
{
  int result; int level = Height-1;
  int newLargest=0; keyType prevKey, largestKey;
  BTNode * thisNode, * newNode, * parentNode;
  thisNode = FindLeaf (key);

  // test for special case of new largest key in tree
  if (key > thisNode->LargestKey())
	{newLargest = 1; prevKey=thisNode->LargestKey();}

  result = thisNode -> Insert (key, recAddr);

  // handle special case of new largest key in tree
  if (newLargest)
	for (int i = 0; i<Height-1; i++)
	{
	  Nodes[i]->UpdateKey(prevKey,key);
	  if (i>0) Store (Nodes[i]);
	}

  while (result==-1) // if overflow and not root
  {
	//remember the largest key
	largestKey = thisNode->LargestKey();
	// split the node
	newNode = NewNode();
	thisNode->Split(newNode);
	Store(thisNode); Store(newNode);
	level--; // go up to parent level
	if (level < 0) break;
	// insert newNode into parent of thisNode
	parentNode = Nodes[level];
	result = parentNode->UpdateKey(largestKey,thisNode->LargestKey());
	result = parentNode->Insert(newNode->LargestKey(),newNode->RecAddr);
	thisNode = parentNode;
  }
  Store(thisNode);
  if (level >= 0) return 1;// insert complete
  // else we just split the root
  int newAddr = BTreeFile.Append(Root); // put previous root into file
  // insert 2 keys in new root node
  Root.Keys[0]=thisNode->LargestKey();
  Root.RecAddrs[0]=newAddr;
  Root.Keys[1]=newNode->LargestKey();
  Root.RecAddrs[1]=newNode->RecAddr;
  Root.NumKeys=2;
  Height++;
  return 1;
}
template <class keyType>
int BTreeNode<keyType>::Split (BTreeNode<keyType> * newNode)
{
  // check for sufficient number of keys
  if (this->NumKeys < this->MaxKeys) return 0;
  // find the first Key to be moved into the new node
  int midpt = (this->NumKeys+1)/2;
  int numNewKeys = this->NumKeys - midpt;
  // check that number of keys for newNode is ok
  if (numNewKeys > newNode -> MaxBKeys
	|| numNewKeys < newNode -> MinKeys)
	return 0;
  // move the keys and recaddrs from this to newNode
  for (int i = midpt; i< this->NumKeys; i++)
  {:
	newNode->Keys[i-midpt] = this->Keys[i];
	newNode->RecAddrs[i-midpt] = this->RecAddrs[i];
  }
  // set number of keys in the two Nodes
  newNode->NumKeys = numNewKeys;
  this->NumKeys = midpt;
  // Link the nodes together
  return 1;
}


Remove는 데이터를 삭제하는 메서드로, root에서부터 key의 위치를 찾고 그 위치의 node 상태에 따라 다양한 동작들을 수행한다. 
node n에서 key k를 지우는 단계는 다음과 같다.



Step 1. key를 제거하기 위해 leaf의 level을 찾는다.
Step 2. node n의 entry 수 > m/2이고 k가 가장 큰 값이 아니라면 그냥 지운다.
Step 3. node n의 entry 수 > m/2이고 k가 가장 큰 값이면 key를 지우고 포인터를 새로운 largest key를 가리키도록 업데이트한다.
Step 4. node n의 entry 수 = m/2이고 n의 형제 node가 충분한 공간을 가진다면 node n과 형제 node를 merge하고 부모 node에서 포인터를 지운다.
Step 5. node n의 entry 수 = m/2이고 n의 형제 node도 공간이 없다면 부모 노드를 새로 나누어 빈 공간을 가지는 node를 만든 후 포인터를 업데이트한다.



B-Tree의 Worst case
B-Tree도 당연히 worst case가 존재한다. 앞서 말한 B-Tree의 특징 2번과 3번에 의해 order가 m인 B-Tree에서 node는 m/2개의 자식 노드를 가져야 한다. 
이때 모든 node가 딱 반만 차있다면 B-Tree의 특징은 만족하면서 node의 수는 가장 많은 worst case가 된다.



이 경우 다음을 만족하는 d가 B-Tree의 level이 된다.
*/



