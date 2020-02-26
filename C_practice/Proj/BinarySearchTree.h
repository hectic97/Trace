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

	if (cNode == NULL)  //���� ��� X
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

		if (GetLeftSubTree(dNode) != NULL)  //���� ��尡 ���� �ڽ� ��带 ������ ������
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);
		if (GetLeftSubTree(pNode) == dNode)  //������尡 �θ����� ���� �ڽ� ����ϰ��
			ChangeLeftSubTree(pNode, dcNode); // ��������� �θ��忡 ��������� �ڽĳ�带 ����
		else
			ChangeRightSubTree(pNode, dcNode);
	}
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode);  //mNode == ��ü���
		BTreeNode* mpNode = dNode;
		int delData;
		
		while (GetLeftSubTree(mNode != NULL))
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		delData = GetData(dNode);
		SetData(dNode, GetData(mNode));//��ü ����� �����͸� ������ ��忡 ����
		
		if (GetLeftSubTree(mpNode) == mNode) //��ü ��尡 �θ� ����� ���� ����� ���
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));
		dNode = mNode;
		SetData(dNode, delData);
	}

	//������ ��尡 ��Ʈ ����� ���
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot); //��Ʈ ����� ����

	free(pVRoot);
	return dNode;

}
