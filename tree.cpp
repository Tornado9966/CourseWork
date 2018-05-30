#include <iostream>
#include <cstdlib>
#include "tree.h"

using namespace std;

int Tree<int>::Counter(Node* root) 
{
	if (root != nullptr) {
		count++;
		Counter(root->left);
		Counter(root->right);
	}
	return count;
	count = 0;
}

int Tree<int>::Levels(Node* root) 
{
	if (root != nullptr) {
		if ((root->level) > levels) levels++;
		Levels(root->left);
		Levels(root->right);
	}
	return (levels + 1);
	levels = 0;
}

int Tree<int>::Delete(int delkey) 
{
	if (root == nullptr) {
		return 0;
	}
	Node* pointer = root;
	Node* parent = nullptr;

	while (pointer != nullptr && pointer->key != delkey) {
		parent = pointer;
		if (delkey < pointer->key) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
		if ((delkey < pointer->key) && (pointer->left == nullptr)) {
			delkey = root->key;
			return 0;
		}
		if ((delkey > pointer->key) && (pointer->right == nullptr)) {
			delkey = root->key;
			return 0;
		}
	}

	if (pointer != nullptr) {
		Node* removed = nullptr;

		if (pointer->left == nullptr || pointer->right == nullptr)
		{
			Node* child = nullptr;
			removed = pointer;

			if (pointer->left != nullptr) {
				child = pointer->left;
			}
			else if (pointer->right != nullptr) {
				child = pointer->right;
			}

			if (child != nullptr) {
				child->pos = pointer->pos;
				child->level = pointer->level;
			}

			if (parent == nullptr) {
				root = child;
			}
			else {
				if (parent->left == pointer) {
					parent->left = child;
				}
				else if (parent->right == pointer) {
					parent->right = child;
				}
			}
		}
		else { // (pointer->left != NULL && pointer->right != NULL)
			Node* mostLeft = pointer->right;
			Node* mostLeftParent = pointer;

			while (mostLeft->left != nullptr) {
				mostLeftParent = mostLeft;
				mostLeft = mostLeft->left;
			}

			pointer->key = mostLeft->key;
			pointer->value = mostLeft->value;
			removed = mostLeft;

			if (mostLeftParent->left == mostLeft) {
				mostLeftParent->left = nullptr;
			}
			else {
				mostLeftParent->right = nullptr;
			}
		}
		return delkey;
		delete removed;
	}
}

int Tree<int>::FindKeyByPos(Node* root, int posfind) 
{
	if ((posfind < 1) || (posfind > (pow(2, Levels(root)) - 1))) {
		return 0;
	}
	if (root != nullptr) {
		if ((root->pos) == posfind) {
			key = root->key;
		}
		FindKeyByPos(root->left, posfind);
		FindKeyByPos(root->right, posfind);
	}
	return key;
	key = 0;
}

int Tree<int>::FindValueByPos(Node* root, int posfind) 
{
	if ((posfind < 1) || (posfind >(pow(2, Levels(root)) - 1))) {
		return 0;
	}
	if (root != nullptr) {
		if ((root->pos) == posfind) {
			value = root->value;
		}
		FindValueByPos(root->left, posfind);
		FindValueByPos(root->right, posfind);
	}
	return value;
	value = 0;
}

/*bool Equal(Tree<int> tree1, Tree<int> tree2) {
	int count1 = tree1.Counter(tree1.Root());
	int count2 = tree2.Counter(tree2.Root());
	if (count1 != count2) return false;

	int levels1 = tree1.Levels(tree1.Root());
	int levels2 = tree2.Levels(tree2.Root());
	if (levels1 != levels2) return false;

	for (int i = 1; i < pow(2, levels1); i++) {
		if ((tree1.FindKeyByPos(tree1.Root(), i) != tree2.FindKeyByPos(tree2.Root(), i)) || (tree1.FindValueByPos(tree1.Root(), i) != tree2.FindValueByPos(tree2.Root(), i))) {
			tree1.EqualTr = false;
			tree2.EqualTr = false;
		}
		if (!(tree1.FindKeyByPos(tree1.Root(), i)) && (tree2.FindKeyByPos(tree2.Root(), i))) {
			tree1.EqualTr = false;
			tree2.EqualTr = false;
		}
		if ((tree1.FindKeyByPos(tree1.Root(), i)) && !(tree2.FindKeyByPos(tree2.Root(), i))) {
			tree1.EqualTr = false;
			tree2.EqualTr = false;
		}
		if (!(tree1.FindKeyByPos(tree1.Root(), i)) && !(tree2.FindKeyByPos(tree2.Root(), i)) && (i == (pow(2, levels1)) - 1)) {
			tree1.EqualTr = tree1.EqualTr;
			tree2.EqualTr = tree2.EqualTr;
		}
		if (!(tree1.FindKeyByPos(tree1.Root(), i)) && !(tree2.FindKeyByPos(tree2.Root(), i))) {
			i++;
		}
	}
	return tree1.EqualTr;
}*/

void Tree<int>::Print(Node* root) 
{
	if (root != nullptr) {
		cout << "( " << root->key << ", " << root->value << " ) - " << root->pos << ", " << "level - " << root->level << endl;
		Print(root->left);
		Print(root->right);
	}
}

/*int main() {
	Tree<int> tree1;
	tree1.Add(10, 5);
	tree1.Add(12, 7);
	tree1.Add(7, 8);
	tree1.Add(5, 10);
	tree1.Add(9, 15);
	tree1.Add(11, 11);
	tree1.Print(tree1.Root());

	cout << tree1.FindKeyByPos(tree1.Root(), 5) << endl;
	cout << endl;

	Tree<int> tree2;
	tree2.Add(10, 5);
	tree2.Add(12, 7);
	tree2.Add(7, 8);
	tree2.Add(5, 10);
	tree2.Add(9, 15);
	tree2.Add(11, 11);
	tree2.Print(tree2.Root());
	cout << endl;
	cout << Equal(tree1, tree2) << endl;

	cout << tree1.Levels(tree1.Root()) << endl;

	cout << tree1.count << endl;

	system("pause");
	return 0;
}*/