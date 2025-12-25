#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;

struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
};

struct BST {
    BSTNode* root;
    int size;
};

void createBST(BST* tree);
BSTNode* createBSTNode(int value);
void bstInsert(BST* tree, int value);
bool bstSearch(BSTNode* root, int value);
void bstInorder(BSTNode* root);
void bstPreorder(BSTNode* root);
void bstPostorder(BSTNode* root);
void bstFree(BSTNode* root);

void bstSwapTwoNodes(BST* tree);
void bstRecover(BST* tree); 
void bstPrintTree(BSTNode* root, string prefix = "", bool isLeft = true);
void bstDemoTask5(); 

#endif
