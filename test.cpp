#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include "tree.h"

using namespace std;

bool Equal(Tree<int> tree1, Tree<int> tree2) 
{
	bool equalTree = true;

	int count1 = tree1.Counter(tree1.Root());
	int count2 = tree2.Counter(tree2.Root());
	if (count1 != count2) return false;

	int levels1 = tree1.Levels(tree1.Root());
	int levels2 = tree2.Levels(tree2.Root());
	if (levels1 != levels2) return false;

	for (int i = 1; i < pow(2, levels1); i++) {
		int key1 = tree1.FindKeyByPos(tree1.Root(), i);
		int key2 = tree2.FindKeyByPos(tree2.Root(), i);
		int value1 = tree1.FindValueByPos(tree1.Root(), i);
		int value2 = tree2.FindValueByPos(tree2.Root(), i);

		if (key1 != key2) {
			equalTree = false;
		}
		if (value1 != value2) {
			equalTree = false;
		}
		if (!key1 && key2) {
			equalTree = false;
		}
		if (key1 && !key2) {
			equalTree = false;
		}
		if (!key1 && !key2 && (i == (pow(2, levels1)) - 1)) {
			equalTree = equalTree;
		}
		if (!key1 && !key2) {
			i++;
		}
	}
	return equalTree;
}

TEST_CASE("Check Add") {
	Tree<int> tree;
	tree.Add(10, 1);
	tree.Add(13, 10);
	tree.Add(6, 3);
	tree.Add(3, 8);
	tree.Add(8, 11);
	tree.Add(17, 14);
	tree.Add(11, 40);
	tree.Add(7, 2);
	tree.Add(12, 5);
	tree.Add(20, 7);
	CHECK(*tree.getIter() == 10);
	CHECK(*(++tree.getIter()) == 13);
	CHECK(*(--tree.getIter()) == 6);
	CHECK(tree.Counter(tree.getIter().getNode()) == 10);
	CHECK(tree.Levels(tree.getIter().getNode()) == 4);
	CHECK(*tree.getIter() == 10);
}

TEST_CASE("Check Delete") {
	Tree<int> tree;
	tree.Add(10, 1);
	tree.Add(13, 10);
	tree.Add(6, 3);
	tree.Add(3, 8);
	tree.Add(8, 11);
	tree.Add(17, 14);
	tree.Add(11, 40);
	tree.Add(7, 2);
	tree.Add(12, 5);
	tree.Add(20, 7);
	CHECK(tree.Delete(6) == 6);
	CHECK(tree.Counter(tree.getIter().getNode()) == 9);
	CHECK(tree.Levels(tree.getIter().getNode()) == 4);
	CHECK(tree.FindKeyByPos(tree.getIter().getNode(), 2) == 7);
	CHECK(tree.FindValueByPos(tree.getIter().getNode(), 2) == 2);
	CHECK(tree.Delete(40) == 0);

	Tree<int> tree1;
	CHECK(tree1.Delete(10) == 0);
}

TEST_CASE("Check FindKeyByPos and FindValueByPos") {
	Tree<int> tree;
	tree.Add(10, 1);
	tree.Add(13, 10);
	tree.Add(6, 3);
	tree.Add(3, 8);
	tree.Add(8, 11);
	tree.Add(17, 14);
	tree.Add(11, 40);
	tree.Add(7, 2);
	tree.Add(12, 5);
	tree.Add(20, 7);
	CHECK(tree.FindKeyByPos(tree.getIter().getNode(), 5) == 8);
	CHECK(tree.FindValueByPos(tree.getIter().getNode(), 6) == 40);
	CHECK(tree.FindKeyByPos(tree.getIter().getNode(), -2) == 0);
	CHECK(tree.FindValueByPos(tree.getIter().getNode(), -3) == 0);
	CHECK(tree.FindKeyByPos(tree.getIter().getNode(), 18) == 0);
	CHECK(tree.FindValueByPos(tree.getIter().getNode(), 20) == 0);
}

TEST_CASE("Check Equal") {
	SUBCASE("Trees are not equal") {
		SUBCASE("Test 1") {
			Tree<int> tree1;
			tree1.Add(10, 1);
			tree1.Add(13, 10);
			tree1.Add(6, 3);
			tree1.Add(3, 8);
			tree1.Add(8, 11);
			tree1.Add(17, 14);
			tree1.Add(11, 40);
			tree1.Add(7, 2);
			tree1.Add(12, 5);
			tree1.Add(20, 7);

			Tree<int> tree2;
			tree2.Add(9, 1);
			tree2.Add(13, 10);
			tree2.Add(6, 3);
			tree2.Add(3, 8);
			tree2.Add(8, 11);
			tree2.Add(17, 14);
			tree2.Add(11, 40);
			tree2.Add(7, 2);
			tree2.Add(12, 5);
			tree2.Add(20, 7);

			CHECK(Equal(tree1, tree2) == false);
		}
		SUBCASE("Test 2") {
			Tree<int> tree1;
			tree1.Add(10, 1);
			tree1.Add(13, 10);
			tree1.Add(6, 3);
			tree1.Add(3, 8);
			tree1.Add(8, 11);
			tree1.Add(17, 14);
			tree1.Add(11, 40);
			tree1.Add(7, 2);
			tree1.Add(12, 5);
			tree1.Add(20, 7);

			Tree<int> tree2;
			tree2.Add(10, 1);
			tree2.Add(13, 10);
			tree2.Add(6, 3);
			tree2.Add(3, 8);
			tree2.Add(8, 11);
			tree2.Add(17, 14);
			tree2.Add(11, 40);
			tree2.Add(7, 2);
			tree2.Add(12, 5);

			CHECK(Equal(tree1, tree2) == false);
		}
		SUBCASE("Test 3") {
			Tree<int> tree1;
			tree1.Add(10, 1);
			tree1.Add(13, 10);
			tree1.Add(6, 3);
			tree1.Add(3, 8);
			tree1.Add(8, 11);
			tree1.Add(17, 14);
			tree1.Add(11, 40);
			tree1.Add(7, 2);
			tree1.Add(12, 5);
			tree1.Add(20, 7);

			Tree<int> tree2;
			tree2.Add(10, 1);
			tree2.Add(13, 10);
			tree2.Add(6, 3);
			tree2.Add(3, 8);
			tree2.Add(8, 11);
			tree2.Add(17, 15);
			tree2.Add(11, 40);
			tree2.Add(7, 2);
			tree2.Add(12, 5);
			tree2.Add(20, 7);

			CHECK(Equal(tree1, tree2) == false);
		}
		SUBCASE("Test 4") {
			Tree<int> tree1;
			tree1.Add(10, 1);
			tree1.Add(13, 10);
			tree1.Add(6, 3);
			tree1.Add(3, 8);
			tree1.Add(8, 11);
			tree1.Add(17, 14);
			tree1.Add(11, 40);
			tree1.Add(7, 2);
			tree1.Add(12, 5);
			tree1.Add(20, 7);

			Tree<int> tree2;
			tree2.Add(9, 1);
			tree2.Add(13, 10);
			tree2.Add(6, 3);
			tree2.Add(3, 8);
			tree2.Add(8, 11);
			tree2.Add(17, 14);
			tree2.Add(11, 40);
			tree2.Add(7, 2);
			tree2.Add(20, 7);
			tree2.Add(22, 8);

			CHECK(Equal(tree1, tree2) == false);
		}
	}
	SUBCASE("Trees are equal") {
		Tree<int> tree1;
		tree1.Add(10, 1);
		tree1.Add(13, 10);
		tree1.Add(6, 3);
		tree1.Add(3, 8);
		tree1.Add(8, 11);
		tree1.Add(17, 14);
		tree1.Add(11, 40);
		tree1.Add(7, 2);
		tree1.Add(12, 5);
		tree1.Add(20, 7);

		Tree<int> tree2;
		tree2.Add(10, 1);
		tree2.Add(13, 10);
		tree2.Add(6, 3);
		tree2.Add(3, 8);
		tree2.Add(8, 11);
		tree2.Add(17, 14);
		tree2.Add(11, 40);
		tree2.Add(7, 2);
		tree2.Add(12, 5);
		tree2.Add(20, 7);

		CHECK(Equal(tree1, tree2) == true);
	}
}