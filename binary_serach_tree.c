#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
	int val;
	struct _tree *left;
	struct _tree *right;
} tree, *ptree;

ptree newnode(int val) {
	ptree node = (ptree)malloc(sizeof(tree));
	
	node->val = val;
	node->left = node->right = NULL;
	
	return node;
}

ptree insert(ptree root, int val)
{
	if (root == NULL) {
		return newnode(val);
	}
	
	if (root->val < val) {
		root->right = insert(root->right, val);
	} else {
		root->left = insert(root->left, val);
	}
	
	return root;
}

int size(ptree root)
{
	if (root == NULL) {
		return 0;
	}
	
	return size(root->left) + size(root->right) + 1;
}

int _isvalid(ptree root, int min, int max) {
    if (root == NULL) return 1;
    
    if (root->val <= min || root->val >= max) return 0;
    
    return _isvalid(root->left, min, root->val) && _isvalid(root->right, root->val, max);
}
 
int isValidBST(ptree A) {
    return _isvalid(A, INT_MIN, INT_MAX);
}


int maxDepth(ptree root)
{
	int l, r;
	if (root == NULL) {
		return 0;
	}
	
	l = maxDepth(root->left);
	r = maxDepth(root->right);
	
	return (l > r) ? l + 1 : r + 1;
}

int minValue(ptree root)
{
	if (root == NULL) {
		return INT_MAX;
	}
	
	while (root->left != NULL) {
		root = root->left;
	}
	
	return root->val;
}

void printInorder(ptree root)
{
	if (root == NULL) return;
	
	printInorder(root->left);
	printf("%d, ", root->val);
	printInorder(root->right);
}

void printPostorder(ptree root)
{
	if (root == NULL) return;
	
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d, ", root->val);
}

int hasPathSum(ptree root, int sum)
{
	int val;
	if (root == NULL) {
		return (root->val == 0);
	}
	
	val = sum - root->val;
	return (hasPathSum(root->left, val) ||
		hasPathSum(root->right, val));	
}

void _printpaths(ptree root, int *res, int i)
{
	if (root == NULL) return;

	res[i++] = root->val;	
	if (root->left == NULL && root->right == NULL) {
		int j;
		for (j = 0; j < i; j++) {
			printf("%d, ", res[j]);
		}
		printf("\n");
		return;
	}
	
	_printpaths(root->left, res, i);
	_printpaths(root->right, res, i);
}

void printPaths(ptree root)
{
	int res[1000];
	_printpaths(root, res, 0);
}

int _sym(ptree A, ptree B) 
{
    if (A == NULL && B == NULL) return 1;
    
    if (A == NULL || B == NULL) return 0;
        
    if (A->val != B->val) return 0;
    
    return _sym(A->left, B->right) && _sym(A->right, B->left);
}

int isSymmetric(ptree A) {
    if (A == NULL) return 1;
    
    return _sym(A->left, A->right);
}

ptree getSuccessor(ptree A, int B) {
    ptree cur = A;
    ptree succ = NULL;
    ptree parent = NULL;
    
    while (cur->val != B) {
        if (cur->val > B) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    
    if (cur->right != NULL) {
        ptree temp = cur->right;
        
        while (temp->left != NULL) temp = temp->left;
        
        return temp;
    }
    
    parent = A;
    while (parent != cur) {
        if (parent->val > cur->val) {
            succ = parent;
            parent = parent->left;
        } else {
            parent = parent->right;
        }
    }
    
    return succ;
}

void doubleTree(ptree root)
{
	ptree temp;
	
	if (root == NULL) return;
	
	doubleTree(root->left);
	doubleTree(root->right);
	
	temp = newnode(root->val);
	temp->left = root->left;
	root->left = temp;
}

int isSameTree(ptree A, ptree B) {
    if (A == NULL && B == NULL) return 1;
    
    if (A == NULL || B == NULL) return 0;
    
    if (A->val != B->val) return 0;
    
    return (isSameTree(A->left, B->left) && isSameTree(A->right, B->right));
}

ptree invertTree(ptree root) {
    ptree temp;
    if (root == NULL) return root;
    
    invertTree(root->left);
    invertTree(root->right);
    
    temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    return root;
}

int countTrees(int keys)
{
	int count = 0;
	int left, right, root;
	
	if (keys <= 1) return 1;
	
	for (root = 1; root <= keys; root++) {
		left = countTrees(root-1);
		right = countTrees(keys - root);
		
		count += left*right;
	}
	
	return count;
}
