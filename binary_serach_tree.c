#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
	int val;
	struct _tree *left;
	struct _tree *right;
} tree, *ptree;

/* create a new node */
ptree newnode(int val) {
	ptree node = (ptree)malloc(sizeof(tree));
	
	node->val = val;
	node->left = node->right = NULL;
	
	return node;
}

/* insert new node at appropriate place */
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

/* return size of BST */
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
 
/* Return true if a binary tree is a BST */
int isValidBST(ptree A) {
    return _isvalid(A, INT_MIN, INT_MAX);
}


/* 
 Compute the "maxDepth" of a tree -- the number of nodes along 
 the longest path from the root node down to the farthest leaf node. 
*/ 
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

/* 
 Given a  binary search tree, 
 return the minimum data value found in that tree. 
 Note that the entire tree does not need to be searched. 
*/ 
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

/* inorder traversal of BST */
void printInorder(ptree root)
{
	if (root == NULL) return;
	
	printInorder(root->left);
	printf("%d, ", root->val);
	printInorder(root->right);
}

/* postorder traversal of BST */
void printPostorder(ptree root)
{
	if (root == NULL) return;
	
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d, ", root->val);
}

/* 
 Given a tree and a sum, return true if there is a path from the root 
 down to a leaf, such that adding up all the values along the path 
 equals the given sum.
*/ 
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

/* 
 Given a binary tree, print out all of its root-to-leaf 
 paths, one per line. Uses a recursive helper to do the work. 
*/ 
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

/* Given a binary tree, check whether it is a mirror of 
   itself (ie, symmetric around its center).
   
   Following is symmetric :
    1
   / \
  2   2
 / \ / \
3  4 4  3 

The following is not symmetric:

 1
   / \
  2   2
   \   \
   3    3
*/
int isSymmetric(ptree A) {
    if (A == NULL) return 1;
    
    return _sym(A->left, A->right);
}

/* Given a BST node, return the node which has value just greater than the given node.*/
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

/* 
 For each node in a binary search tree, 
 create a new duplicate node, and insert 
 the duplicate as the left child of the original node. 
 The resulting tree should still be a binary search tree.
 So the tree... 
    2 
   / \ 
  1   3

 Is changed to... 
       2 
      / \ 
     2   3 
    /   / 
   1   3 
  / 
 1

*/ 
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

/* 
 Given two trees, return true if they are 
 structurally identical. 
*/ 
int isSameTree(ptree A, ptree B) {
    if (A == NULL && B == NULL) return 1;
    
    if (A == NULL || B == NULL) return 0;
    
    if (A->val != B->val) return 0;
    
    return (isSameTree(A->left, B->left) && isSameTree(A->right, B->right));
}

/*
Given a binary tree, invert the binary tree and return it. 
Look at the example for more details.

Example : 
Given binary tree

     1
   /   \
  2     3
 / \   / \
4   5 6   7
invert and return

     1
   /   \
  3     2
 / \   / \
7   6 5   4
*/
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

/* 
 For the key values 1...numKeys, how many structurally unique 
 binary search trees are possible that store those keys.
*/ 
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
