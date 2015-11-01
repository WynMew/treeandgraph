#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "sstream"
#include "list"

using namespace std;

struct node
{
	int keyvalue;
	node *left;
	node *right;
};

class btree
{
public:
	btree();

	void insert(int key);
	node *search(int key);
	//	private:
	void insert(int pkey, int ckey);
	node *search(int key, node *leaf);
	node *searchp(int key, node *leaf);
	bool searchparent(int ckey1, int ckey2);
	int treesize(node *leaf);

	node *root;
};

btree::btree()
{
	root = NULL;
}

node *btree::search(int key, node *leaf)
{
	if (leaf != NULL)
	{
		if (key == leaf->keyvalue)
			return leaf;
		else
		{
			if (search(key, leaf->left)==NULL)
				search(key, leaf->right);
		}
	}
	else return NULL;
}

node *btree::searchp(int key, node *leaf)
{
	if ((leaf != NULL) && ((leaf->left != NULL) && (leaf->right == NULL)))
	{
		if ( key == leaf->left->keyvalue)
		{
			return leaf;
		}
		else 
		{
			searchp(key, leaf->left);
		}
	}
	else if ((leaf != NULL) && ((leaf->left == NULL) && (leaf->right != NULL)))
	{
		if (key == leaf->right->keyvalue)
		{
			return leaf;
		}
		else
		{
			searchp(key, leaf->right);
		}
	}
	else if ((leaf != NULL) && ((leaf->left != NULL) && (leaf->right != NULL)))
	{
		if (key == leaf->left->keyvalue)
		{
			return leaf;
		}
		else if (key == leaf->right->keyvalue)
		{
			return leaf;
		}
		else if (searchp(key, leaf->left) == NULL)
			searchp(key, leaf->right);
		else if ((searchp(key, leaf->left) == NULL)&&(searchp(key, leaf->right)==NULL))
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void btree::insert(int pkey, int ckey)
{
	node *thenode;
	node *childnode = new node;

	thenode = search(pkey, root);
	if (thenode != NULL)
	{
		if ((thenode->left == NULL) && (thenode->right == NULL))
		{
			thenode->left = childnode;
			thenode->left->keyvalue = ckey;
			thenode->left->left = NULL;
			thenode->left->right = NULL;
		}
		else if ((thenode->left != NULL) && (thenode->right == NULL))
		{
			thenode->right = childnode;
			thenode->right->keyvalue = ckey;
			thenode->right->left = NULL;
			thenode->right->right = NULL;
		}
		else
			cout << "error" << endl;
		return;
	}
	else
		cout << "error";
}

void btree::insert(int key)
{
	if (root != NULL)
	{
		insert(root->keyvalue, key);
	}
	else
	{
		root = new node;
		root->keyvalue = key;
		root->left = NULL;
		root->right = NULL;
	}
}

int btree::treesize(node *leaf)
{
	int yoursize = 0;
	if ((leaf != NULL) && ((leaf->left != NULL) && (leaf->right == NULL)))
	{
		yoursize = yoursize + treesize(leaf->left)+1;
	}
	else if ((leaf != NULL) && ((leaf->left == NULL) && (leaf->right != NULL)))
	{
		yoursize = yoursize + treesize(leaf->right)+1;
	}
	else if ((leaf != NULL) && ((leaf->left != NULL) && (leaf->right != NULL)))
	{
		yoursize = yoursize + treesize(leaf->left) + treesize(leaf->right)+1;
	}
	else if ((leaf != NULL) && ((leaf->left == NULL) && (leaf->right == NULL)))
	{
		yoursize = 1;
	}
	else
	{
		yoursize = 0;
	}
	return yoursize;
}

bool btree::searchparent(int ckey1, int ckey2)
{
	if (ckey1 == ckey2)
	{
		node *p;
		p = search(ckey1, root);
		int tsize = 0;
		tsize = treesize(p);
		cout << p->keyvalue<<" "<<tsize<<endl;
		return true;
	}
	else if ((ckey1 != ckey2) && ((ckey1 != root->keyvalue) && (ckey2 != root->keyvalue)))
	{
		node *p1, *p2;
		p1 = searchp(ckey1, root);
		p2 = searchp(ckey2, root);
		if (p1->keyvalue == p2->keyvalue)
		{
			return true;
		}
		else
		{
			if (!(searchparent(p1->keyvalue, ckey2)))
				searchparent(ckey1, p2->keyvalue);
		}
	}
	else if ((ckey1 != ckey2) && ((ckey1 == root->keyvalue) || (ckey2 == root->keyvalue)))
		return false;
}

node *btree::search(int key)
{
	return search(key, root);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numV, numE;
	int V1, V2;
	cin >> numV >> numE >> V1 >> V2;
	cin.ignore();

	string line;
	getline(cin, line);
	// input your tree
	istringstream str(line);

	int counter = 0;
	string buff;
	int parent, child;
	btree mytree;

	while (getline(str, buff, ' '))
	{
		if (counter % 2 == 0)
		{
			parent = atoi(buff.c_str());
			if (counter == 0)
			{
				mytree.insert(parent);
			}
		}

		else if (counter % 2 == 1)
		{
			child = atoi(buff.c_str());
//			cout << " P " << parent << " C " << child << endl;
			mytree.insert(parent, child);
		}

		counter++;
//		cout << counter << endl;
	}
	mytree.searchparent(V1, V2);
	system("pause");
	return 0;
}
