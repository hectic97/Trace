#ifndef __AVL_REBALANCE_H__
#include "BinarySearchTree.h"
#include "BinaryTree2.h"

int GetHeight(BTreeNode* bst)
{
	int leftH;
	int rightH;

	if (bst == NULL)
		return 0;

	leftH = GetHeight(GetLeftSubTree(bst));
	rightH = GetHeight(GetRightSubTree(bst));

	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

int GetHeightDiff(BTreeNode* bst)
{
	int lsh;
	int rsh;
	if (bst == NULL)
		return 0;
	lsh = GetHeight(GetLeftSubTree(bst));
	rsh = GetHeight(GetRightSubTree(bst));
	return lsh - rsh;
}

BTreeNode* RotateLL(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetLeftSubTree(bst);

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	ChangeRightSubTree(cNode, pNode);
	
	return cNode;  // new root node
}

BTreeNode* RotateRR(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetRightSubTree(bst);

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);

	return cNode;  // new root node
}

BTreeNode* RotateLR(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, RotateRR(cNode));
	return RotateLL(pNode);
}

BTreeNode* RotateRL(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode));
	return RotateRR(pNode);
}
BTreeNode* Rebalance(BTreeNode** pRoot)
{

	int hDiff = GetHeightDiff(*pRoot);

	if (hDiff > 1)
	{
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)
			*pRoot = RotateLL(*pRoot);
		else
			*pRoot = RotateLR(*pRoot);
	}

	if (hDiff < -1)
	{
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
			*pRoot = RotateRR(*pRoot);
		else
			*pRoot = RotateRL(*pRoot);
	}
	return *pRoot;
}

#endif // !__AVL_REBALANCE_H__
