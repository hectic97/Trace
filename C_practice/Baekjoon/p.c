//#include <stdio.h>
//#include <stdlib.h>
//typedef enum { false, true } bool; // 0 == false, 1 == true;
//typedef int bdata;
//typedef struct _btreenode
//{
//	bdata item;
//	struct _btreenode* left_child;
//	struct _btreenode* right_child;
//	bool istheaded;
//} btreenode;
//btreenode* createnode(bdata item);
//void destroynode(btreenode* node);
//void createleftsubtree(btreenode* root, btreenode* left);
//void createrightsubtree(btreenode* root, btreenode* right);
//btreenode* leftmost(btreenode* node);
//void inorder(btreenode* node);
//void tester();
//int main() {
//	tester();
//}//void tester() {
//	int n, m, root, child;
//	char type;
//	btreenode** array;
//	btreenode* root = null;
//	scanf("%d", &n);
//	array = (btreenode**)malloc(sizeof(btreenode*) * n);
//	for (int i = 0; i < n; i++)
//		array[i] = createnode(i + 1);
//	scanf("%d", &m);
//	for (int i = 0; i < m; i++) {
//		while (getchar() != '\n'); // = fflush(stdin) = __fpurge(stdin)
//		scanf("%c %d %d", &type, &root, &child);
//		if (root == null)
//			root = array[root - 1]; 
//		if (type == 'l') createleftsubtree(array[root - 1], array[child - 1]);
//		else if (type == 'r') createrightsubtree(array[root - 1], array[child - 1]);
//		else exit(1);
//	}
//	inorder(root);
//	for (int i = 0; i < n; i++)
//		destroynode(array[i]);
//	free(array);
//}
///* modify from here */
//btreenode* createnode(bdata item)
//{
//	btreenode* newnode = (btreenode*)malloc(sizeof(btreenode));
//	newnode->istheaded = false;
//	newnode->item = item;
//	newnode->left_child = null;
//	newnode->right_child = null;
//	return newnode;
//}
//void destroynode(btreenode* node)
//{
//	free(node);
//}
//void createleftsubtree(btreenode* root, btreenode* left)
//{
//	root->left_child = left;
//	left->istheaded = true;
//	left->right_child = root;
//
//	
//}
//void createrightsubtree(btreenode* root, btreenode* right)
//{
//	if (root->istheaded)
//	{
//		right->right_child = root->right_child;
//		right->istheaded = true;
//		root->istheaded = false;
//	}
//	root->right_child = right;
//}
//btreenode* leftmost(btreenode* node)
//{
//	if (node == null)
//		return null;
//	while (node->left_child != null)
//		node = node->left_child;
//	return node;
//}
//
//void inorder(btreenode* node)
//{
//	
//	btreenode* cur = leftmost(node);
//	
//	
//	while (cur != null)
//	{
//		printf("%d ", cur->item);
//		if (cur->istheaded)
//			cur = cur->right_child;
//		else
//			cur = leftmost(cur->right_child);
//	}
//}
//
//
///* modify to here */