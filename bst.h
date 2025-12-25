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

// Основные функции
void createBST(BST* tree);
BSTNode* createBSTNode(int value);
void bstInsert(BST* tree, int value);
bool bstSearch(BSTNode* root, int value);
void bstInorder(BSTNode* root);
void bstPreorder(BSTNode* root);
void bstPostorder(BSTNode* root);
void bstFree(BSTNode* root);

// Функции для задания 5
void bstSwapTwoNodes(BST* tree); // Создает дерево с двумя поменянными узлами
void bstRecover(BST* tree); // Восстанавливает правильное BST
void bstPrintTree(BSTNode* root, string prefix = "", bool isLeft = true);
void bstDemoTask5(); // Добавляем эту строку

#endif
