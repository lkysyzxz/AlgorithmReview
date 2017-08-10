#include"AVLTree.h"
#include<iostream>
using namespace std;
int main()
{
	AVLTree tree;
	for (int i = 1; i <= 10; i++)
	{
		tree.Insert(tree.root, i);
	}
	tree.Delete(tree.root,5);
	shared_ptr<ResultNode> p = tree.Find(tree.root, 10);
	if (p != nullptr) {
		cout << p->key << endl;
	}
	else
	{
		cout << "Can not find!" << endl;
	}
	p = tree.Find(tree.root, 5);

	if (p != nullptr) {
		cout << p->key << endl;
	}
	else
	{
		cout << "Can not find!" << endl;
	}
	p = nullptr;
	
	//Test Iterator
	AVLTree::AVLConstIterator it = tree.Begin();
	while (it.HasNext())
	{
		cout << *it << endl;
		it++;
	}
	return 0;
}