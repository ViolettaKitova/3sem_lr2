#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <string>
#include <stack>
using namespace std;

struct Node {
  string data;
  Node* left; //левый потомок
  Node* right; //правый
};

struct CompleteBinaryTree {
  Node* root; //корень
  int count; //кол-во узлов в дереве
};

Node* createNode(string el);
void createTree(CompleteBinaryTree& tree);
void add(CompleteBinaryTree& tree, string el);
bool search(Node* root, string value);
bool isComplete(Node* root, int index, int totalNodes);
int countNodes(Node* root);
void printDepth(Node* root);
void printBreadth(Node* root);
void runTree();

#endif
