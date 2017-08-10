#pragma once
/******
 *	Author:	º®½­Ñ©1719
 *	Email:	<lkysyzxz@outlook.com>
 *	Date:	2017.8.11
 *	Detail:	This file descripte the definition of AVL Tree.
 *			These code comes from Baidu Baike's introduction.
 *			In Baike,there is C-Style code on the website:https://baike.baidu.com/item/AVL%E6%A0%91/10986648?fr=aladdin
 *			I have copy it in AVLTree.cpp and write a comment.
 *			Today,my work was to translate it into CPP.I use class to encapsulate it.
 *			I have wrote some testing code to test it.I insert 1,2,3....10 in order and it seems performed well.
 *			But other work I should do is to make more testing code to test it.
 *			I need to make some case,such as insert 10,9,8...1 in order and 5,3,4 and 5,7,6 and other big data test.
 *
 *			Besides AVLTree,I try to write an iterator for AVLTree class,it runs good and no exception.But its running
 *			effection has not been test.
 *	Other:	Have your fun.
 */
#include<stack>
#include<memory>
using std::stack;
class EmptyNode
{
public:
	static EmptyNode* EmptyNodeFactory()
	{
		return new EmptyNode();
	}

	static void EmptyNodeRevoke(EmptyNode* node)
	{
		delete node;
	}
};

class ResultNode
{
public:
	int key;
public:
	static ResultNode* ResultNodeFactory(int key)
	{
		ResultNode* res = new ResultNode();
		res->key = key;
		return res;
	}
};

class TreeNode :public EmptyNode
{
public:
	static TreeNode* NodeFactory()
	{
		return new TreeNode();
	}

	static void NodeRevoke(TreeNode* node, EmptyNode* eNode)
	{
		if (eNode != nullptr)
			EmptyNode::EmptyNodeRevoke(eNode);
		if (node != nullptr)
			delete node;
	}

	static void Right_Rotation(TreeNode* node)
	{
		TreeNode* tmp = node->right;
		int tmpKey = node->key;
		node->right = node->left;
		node->key = node->left->key;
		node->left = node->right->left;
		node->right->right = tmp;
		node->right->key = tmpKey;
	}

	static void Left_Rotation(TreeNode* node)
	{
		TreeNode* tmp = node->left;
		int tmpKey = node->key;
		node->left = node->right;
		node->key = node->right->key;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = tmp;
		node->left->key = tmpKey;
	}
public:
	TreeNode* left;
	TreeNode* right;
	int key;
	int height;
};

class AVLTree
{
public:
	static stack<TreeNode*> travel_path;
	static void stack_clear()
	{
		while (!travel_path.empty())
		{
			travel_path.pop();
		}
	}
	static TreeNode* stack_pop()
	{
		TreeNode* res = travel_path.top();
		travel_path.pop();
		return res;
	}

	static void stack_push(TreeNode* node)
	{
		travel_path.push(node);
	}

	static bool stack_empty()
	{
		return travel_path.empty();
	}
public:
	TreeNode* root;
private:
	int Rebalance(TreeNode* node)
	{
		bool finish = false;
		while (!stack_empty() && !finish)
		{
			int tmp_height, old_height;
			node = stack_pop();
			old_height = node->height;
			if (node->left->height - node->right->height == 2)
			{
				if (node->left->left->height - node->right->height == 1)
				{
					TreeNode::Right_Rotation(node);
					node->right->height = node->right->left->height + 1;
					node->height = node->right->height + 1;
				}
				else
				{
					TreeNode::Left_Rotation(node->left);
					TreeNode::Right_Rotation(node);
					tmp_height = node->left->left->height;
					node->left->height = tmp_height + 1;
					node->right->height = tmp_height + 1;
					node->height = tmp_height + 2;
				}
			}
			else if (node->left->height - node->right->height == -2)
			{
				if (node->right->right->height - node->left->height == 1)
				{
					TreeNode::Left_Rotation(node);
					node->left->height = node->left->right->height + 1;
					node->height = node->left->height + 1;
				}
				else
				{
					TreeNode::Right_Rotation(node->right);
					TreeNode::Left_Rotation(node);
					tmp_height = node->right->right->height;
					node->left->height = tmp_height + 1;
					node->right->height = tmp_height + 1;
					node->height = tmp_height + 2;
				}
			}
			else
			{
				if (node->left->height > node->right->height)
					node->height = node->left->height + 1;
				else
					node->height = node->right->height + 1;
			}
			if (node->height == old_height)
				finish = true;
		}
		stack_clear();
		return 0;
	}
public:
	AVLTree()
	{
		root = new TreeNode();
		root->height = 0;
		root->left = nullptr;
		root->right = nullptr;
	}

	bool Insert(TreeNode* tree, int key)
	{
		TreeNode* tmp = nullptr;
		int querykey = key;
		int new_key = key;
		if (tree->left == nullptr)
		{
			tree->left = reinterpret_cast<TreeNode*>(EmptyNode::EmptyNodeFactory());
			tree->right = nullptr;
			tree->key = new_key;
			tree->height = 0;
		}
		else
		{
			stack_clear();
			tmp = tree;
			while (tmp->right != nullptr)
			{
				stack_push(tmp);
				if (new_key < tmp->key)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			TreeNode* old_leaf = TreeNode::NodeFactory();
			old_leaf->left = tmp->left;
			old_leaf->right = nullptr;
			old_leaf->key = tmp->key;
			old_leaf->height = 0;
			TreeNode* new_leaf = TreeNode::NodeFactory();
			new_leaf->left = reinterpret_cast<TreeNode*>(EmptyNode::EmptyNodeFactory());
			new_leaf->key = new_key;
			new_leaf->right = nullptr;
			new_leaf->height = 0;
			if (tmp->key < new_key)
			{
				tmp->left = old_leaf;
				tmp->right = new_leaf;
				tmp->key = new_key;
			}
			else
			{
				tmp->left = old_leaf;
				tmp->right = new_leaf;
			}
			tmp->height = 1;
		}
		Rebalance(tmp);
		return 0;
	}


	int Delete(TreeNode* tree, int key)
	{
		TreeNode *tmp = nullptr;
		TreeNode *upper = nullptr;
		TreeNode *other = nullptr;
		if (tree->left == nullptr)
		{
			return -1;
		}
		else if (tree->right == nullptr)
		{
			if (tree->key == key)
			{
				TreeNode::EmptyNodeRevoke(tree->left);
				tree->left = nullptr;
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			tmp = tree;
			stack_clear();
			while (tmp->right != nullptr)
			{
				upper = tmp;
				stack_push(upper);
				if (key < tmp->key)
				{
					tmp = upper->left;
					other = upper->right;
				}
				else
				{
					tmp = upper->right;
					other = upper->left;
				}
			}
			upper->key = other->key;
			upper->left = other->left;
			upper->right = other->right;
			upper->height = upper->height--;
			TreeNode::NodeRevoke(tmp, tmp->left);
			TreeNode::NodeRevoke(other, nullptr);
			Rebalance(stack_pop());
			return 0;
		}
	}


	std::shared_ptr<ResultNode> Find(TreeNode* tree, int key)
	{
		TreeNode* tmp = tree;
		if (tmp->left == nullptr)
		{
			return nullptr;
		}
		else
		{
			tmp = tree;
			while (tmp->right != nullptr)
			{
				if (key < tmp->key)
				{
					tmp = tmp->left;
				}
				else
				{
					tmp = tmp->right;
				}
			}
			if (tmp->key == key)
			{
				return std::shared_ptr<ResultNode>(ResultNode::ResultNodeFactory(key));
			}
			else
			{
				return nullptr;
			}
		}
	}


public:
	class AVLConstIterator
	{
	private:
		stack<const TreeNode*> travel_stack;
		const TreeNode* root;
		const TreeNode* current;
	private:
		void InitIterator(const TreeNode* node)
		{
			const TreeNode* tmp = node;
			if (tmp->left == nullptr)
			{
				return;
			}
			else
			{
				while (tmp->right != nullptr)
				{
					travel_stack.push(tmp);
					tmp = tmp->left;
				}
				current = tmp;
				//travel_stack.push(current);
			}
		}
	public:
		AVLConstIterator(AVLConstIterator&& it):root(it.root),travel_stack(it.travel_stack),current(it.current)
		{
			int x;
			int y = x = 1;
		}

		AVLConstIterator(const TreeNode* _root=nullptr) :root(_root)
		{
			InitIterator(root);
		}

		AVLConstIterator(const AVLConstIterator &it) :root(it.root), travel_stack(it.travel_stack), current(it.current)
		{
			int x;
			int y = x = 1;
		}

		int operator*()const
		{
			return current->key;
		}

		void operator++(int)
		{
			if (travel_stack.size() == 0)
			{
				current = nullptr;
			}
			else {
				const TreeNode* tmp = travel_stack.top();
				travel_stack.pop();
				const TreeNode* nxt = tmp->right;
				while (nxt->right != nullptr)
				{
					travel_stack.push(nxt);
					nxt = nxt->left;
				}
				current = nxt;
			}
		}

		const AVLConstIterator& operator=(AVLConstIterator&& it)
		{
			this->travel_stack = it.travel_stack;
			this->root = it.root;
			this->current = it.current;
			return *this;
		}

		bool HasNext()
		{
			return current != nullptr;
		}
	};

public:
	AVLConstIterator Begin()
	{
		return AVLConstIterator(root);
	}
};