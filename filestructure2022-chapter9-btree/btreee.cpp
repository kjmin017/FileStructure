/*
Find correct leaf L // search
Put data entry onto L // put
	if L has enough space, done!
	else, must split L(into L and a new node L2)
Parent node may overflow
	then push up


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




*/