#include<iostream>
#include<fstream>
using namespace std;
class Tree{
private:
	
	class Node
	{
	private:
		int key;
		Node* left;
		Node* right;
	public:
		Node()
		{
			key = -1;
			left = nullptr;
			right = nullptr;
		}
		void setKey(int aKey){ key = aKey; }
		void setLeft(Node* aLeft){ left = aLeft; }
		void setRight(Node* aRight){ right = aRight; }
		int Key(){ return key; }
		Node* Left(){ return left; }
		Node* Right(){ return right; }
	};
	
	Node* root;
public:
	Tree()
	{
		root = nullptr;
	}
	~Tree()
	{
		freeNode(root);
	}
	Node* Root(){ return root; }
	void addNode(int key)
	{
		if (!root)
		{
			cout << "add root node ... " << key << endl;
			Node* n = new Node();
			n->setKey(key);
			root = n;
		}
		else
		{
			cout << "add other node ... " << key << endl;
			addNode(key, root);
		}
	}
	void addNode(int key, Node* leaf)
	{
		if (key <= leaf->Key())
		{
			if (leaf->Left() != nullptr)//leaf->Left() != nullptr
				addNode(key, leaf->Left());
			else
			{
				Node* n = new Node();
				n->setKey(key);
				leaf->setLeft(n);
			}
		}
		else
		{
			if (leaf->Right() != nullptr)//leaf->Right() != nullptr
				addNode(key, leaf->Right());
			else
			{
				Node* n = new Node();
				n->setKey(key);
				leaf->setRight(n);
			}
		}
	}
	void freeNode(Node* leaf)
	{
		if (leaf != nullptr)//leaf!=nullptr
		{
			freeNode(leaf->Left());
			freeNode(leaf->Right());
			delete leaf;
		}
	}
	void inOrder(Node* n)
	{
		if (n != nullptr)//n!=nullptr
		{
			inOrder(n->Left());
			cout << n->Key() << " ";
			inOrder(n->Right());
		}
	}
	void preOrder(Node* n)
	{
		if (n != nullptr)//n!=nullptr
		{
			cout << n->Key() << " ";
			preOrder(n->Left());
			preOrder(n->Right());
		}
	}
	void postOrder(Node* n)
	{
		if (n != nullptr)//n!=nullptr
		{
			postOrder(n->Left());
			postOrder(n->Right());
			cout << n->Key() << " ";
		}
	}
};

int main()
{
	Tree* tree = new Tree();
	tree->addNode(30);
	tree->addNode(10);
	tree->addNode(20);
	tree->addNode(40);
	tree->addNode(50);

	cout << "In order traversal" << endl;
	tree->inOrder(tree->Root());
	cout << endl;

	cout << "Pre order traversal" << endl;
	tree->preOrder(tree->Root());
	cout << endl;

	cout << "Post order traversal" << endl;
	tree->postOrder(tree->Root());
	cout << endl;

	delete tree;
}
