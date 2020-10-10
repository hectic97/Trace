#ifndef __BINARY_TREE_2__
#define __BINARY_TREE_2__
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BTData;
typedef struct _node
{
	BTData data;
	struct _node* left;
	struct _node* right;

}Node;
typedef Node BTreeNode;

BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

BTData GetData(BTreeNode* bt)
{
	return bt->data;
}

void SetData(BTreeNode* bt,BTData data)
{
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt)
{
	return bt->left;
}
BTreeNode* GetRightSubTree(BTreeNode* bt)
{
	return bt->right;
}
void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)
		free(main->left);
	main->left = sub;
}
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)
		free(main->right);
	main->right = sub;
}
void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)
		free(main->left);
	main->left = sub;
}
void ChangeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	main->left = sub;
}
void ChangeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	main->right = sub;
}
BTreeNode* RemoveLeftSubTree(BTreeNode* bt)
{
	BTreeNode* delNode;

	if (bt != NULL)
	{
		delNode = bt->left;
		bt->left = NULL;
	}
	return delNode;
}
BTreeNode* RemoveRightSubTree(BTreeNode* bt)
{
	BTreeNode* delNode;

	if (bt != NULL)
	{
		delNode = bt->right;
		bt->right = NULL;
	}
	return delNode;
}

#endif // ! __BINARY_TREE_2__
