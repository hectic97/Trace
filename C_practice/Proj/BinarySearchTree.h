#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__
#include "BinaryTree2.h"

typedef BTData BSTData;

void BSTMakeAndInit(BTreeNode** pRoot)
{
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode* bst)
{

	return GetData(bst);
}

void BSTInsert(BTreeNode** pRoot, BSTData data)
{
	BTreeNode* pNode = NULL;
	BTreeNode* cNode = *pRoot;
	BTreeNode* nNode = NULL;

	while (cNode != NULL)
	{
		if (data == GetData(cNode))
			return;
		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);

	}

	nNode = MakeBTreeNode();
	SetData(nNode, data);

	if (pNode != NULL)
	{
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else
	{
		*pRoot = nNode;
	}
}

BTreeNode* BSTSearch(BTreeNode* bst, BSTData target)
{
	BTreeNode* cNode = bst;
	BSTData cd;
	while (cNode != NULL)
	{
		cd = GetData(cNode);

		if (target == cd)
			return cNode;
		else if (target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);

	}
	return NULL;


}
BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target)
{
	BTreeNode* pVRoot = MakeBTreeNode();
	BTreeNode* pNode = pVRoot;
	BTreeNode* cNode = *pRoot;
	BTreeNode* dNode;

	ChangeRightSubTree(pVRoot, *pRoot);

	while (cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode;
		if (target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL)  //삭제 대상 X
		return NULL;
	dNode = cNode;

	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode;

		if (GetLeftSubTree(dNode) != NULL)  //삭제 노드가 왼쪽 자식 노드를 가지고 있으면
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);
		if (GetLeftSubTree(pNode) == dNode)  //삭제노드가 부모노드의 왼쪽 자식 노드일경우
			ChangeLeftSubTree(pNode, dcNode); // 삭제노드의 부모노드에 삭제노드의 자식노드를 연결
		else
			ChangeRightSubTree(pNode, dcNode);
	}
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode);  //mNode == 대체노드
		BTreeNode* mpNode = dNode;
		int delData;
		
		while (GetLeftSubTree(mNode != NULL))
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		delData = GetData(dNode);
		SetData(dNode, GetData(mNode));//대체 노드의 데이터를 삭제할 노드에 대입
		
		if (GetLeftSubTree(mpNode) == mNode) //대체 노드가 부모 노드의 왼쪽 노드일 경우
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));
		dNode = mNode;
		SetData(dNode, delData);
	}

	//삭제된 노드가 루트 노드인 경우
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot); //루트 노드의 변경

	free(pVRoot);
	return dNode;

}
