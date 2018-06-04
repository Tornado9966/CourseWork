template <typename T>
class Tree
{
private:
	struct Node
	{
		T key;
		T value;
		T pos;
		T level;
		Node* left;
		Node* right;
		Node(int kEy, int data, int position, int lev) 
		{
			key = kEy;
			value = data;
			pos = position;
			level = lev;
			left = nullptr;
			right = nullptr;
		}
	};

	static void Add(Node *&node, int keyadd, int valueadd, int posadd, int leveladd) 
	{
		if (node == nullptr) {
			node = new Node(keyadd, valueadd, posadd, leveladd);
		}
		else {
			if (keyadd < node->key) {
				Add(node->left, keyadd, valueadd, (2 * posadd), (leveladd + 1));
			}
			else if (keyadd > node->key) {
				Add(node->right, keyadd, valueadd, ((2 * posadd) + 1), (leveladd + 1));
			}
		}
	}

	Node* root;

public:
	int count = 0;
	int levels = 0;
	int key = 0;
	int value = 0;

	Tree() 
	{
		root = nullptr;
	};

	Node* Root() 
	{
		return root;
	}

	void Add(int keyadd, int valueadd) 
	{
		Add(root, keyadd, valueadd, 1, 0);
	}

	int Delete(int delkey);
	int Counter(Node* root);
	int Levels(Node* root);
	int FindKeyByPos(Node* root, int posfind);
	int FindValueByPos(Node* root, int posfind);
	void Print(Node* root);

	class Iterator
	{
		Node* temp;
	public:
		Iterator(Node* node) : temp(node) {}

		Iterator& operator =(const Iterator &it) 
		{
			temp = it.temp;
			return *this;
		}

		Iterator& operator ++() 
		{
			temp = temp->right;
			return *this;
		}

		Iterator& operator --() 
		{
			temp = temp->left;
			return *this;
		}

		bool operator !=(const Iterator &smth) 
		{
			return (temp != smth.temp);
		}

		bool operator ==(const Iterator &smth) 
		{
			return (temp == smth.temp);
		}

		int& operator *() 
		{
			return temp->key;
		}

		Node* getNode() 
		{
			return temp;
		}
	};

	Iterator getIter() 
	{
		return Iterator(root);
	}

};