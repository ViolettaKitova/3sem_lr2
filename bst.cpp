#include "bst.h"
#include <iostream>
using namespace std;

void createBST(BST* tree) {
    tree->root = nullptr;
    tree->size = 0;
}

BSTNode* createBSTNode(int value) {
    BSTNode* newNode = new BSTNode;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void bstInsert(BST* tree, int value) {
    BSTNode* newNode = createBSTNode(value);
    
    if (tree->root == nullptr) {
        tree->root = newNode;
        tree->size = 1;
        return;
    }
    
    BSTNode* current = tree->root;
    BSTNode* parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            delete newNode;
            return;
        }
    }
    
    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    tree->size++;
}

bool bstSearch(BSTNode* root, int value) {
    BSTNode* current = root;
    
    while (current != nullptr) {
        if (value == current->value) {
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return false;
}

void bstInorder(BSTNode* root) {
    if (root == nullptr) return;
    
    bstInorder(root->left);
    cout << root->value << " ";
    bstInorder(root->right);
}

void bstPreorder(BSTNode* root) {
    if (root == nullptr) return;
    
    cout << root->value << " ";
    bstPreorder(root->left);
    bstPreorder(root->right);
}

void bstPostorder(BSTNode* root) {
    if (root == nullptr) return;
    
    bstPostorder(root->left);
    bstPostorder(root->right);
    cout << root->value << " ";
}

void bstFree(BSTNode* root) {
    if (root == nullptr) return;
    
    bstFree(root->left);
    bstFree(root->right);
    delete root;
}

BSTNode* first = nullptr;
BSTNode* second = nullptr;
BSTNode* prevNode = nullptr;

// Вспомогательная функция для обхода inorder
void bstInorderTraversal(BSTNode* root) {
    if (root == nullptr) return;
    
    bstInorderTraversal(root->left);
    
    if (prevNode != nullptr && prevNode->value > root->value) {
        if (first == nullptr) {
            first = prevNode;
        }
        second = root;
    }
    prevNode = root;
    
    bstInorderTraversal(root->right);
}

// Функция восстановления BST
void bstRecover(BST* tree) {
    first = nullptr;
    second = nullptr;
    prevNode = nullptr;
    
    bstInorderTraversal(tree->root);
    
    if (first != nullptr && second != nullptr) {
        int temp = first->value;
        first->value = second->value;
        second->value = temp;
    }
}

void bstSwapTwoNodes(BST* tree) {
    if (tree->root != nullptr) {
        bstFree(tree->root);
    }
    
    bstInsert(tree, 4);
    bstInsert(tree, 2);
    bstInsert(tree, 6);
    bstInsert(tree, 1);
    bstInsert(tree, 3);
    bstInsert(tree, 5);
    bstInsert(tree, 7);
    
    BSTNode* node2 = nullptr;
    BSTNode* node6 = nullptr;
    
    BSTNode* current = tree->root;
    
    while (current != nullptr) {
        if (current->value == 2) {
            node2 = current;
            break;
        } else if (2 < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
   
    current = tree->root;
    while (current != nullptr) {
        if (current->value == 6) {
            node6 = current;
            break;
        } else if (6 < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (node2 != nullptr && node6 != nullptr) {
        node2->value = 6;
        node6->value = 2;
    }
}

void bstPrintTree(BSTNode* root, string prefix, bool isLeft) {
    if (root == nullptr) return;
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->value << endl;
    
    bstPrintTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    bstPrintTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

void bstDemoTask5() {
    cout << "\n=== Демонстрация задания 5 ===\n";
    
    BST tree;
    createBST(&tree);
    
    //Создаем дерево с двумя поменянными узлами
    cout << "1. Создаем правильное BST и меняем два узла местами\n";
    bstSwapTwoNodes(&tree);
    
    cout << "\n2. Дерево после обмена узлов 2 и 6:\n";
    bstPrintTree(tree.root);
    
    cout << "\n3. Обход inorder (неправильный порядок): ";
    bstInorder(tree.root);
    cout << endl;
    cout << "   Ожидаемый порядок: 1 2 3 4 5 6 7\n";
    
    //Восстанавливаем дерево
    cout << "\n4. Восстанавливаем BST...\n";
    bstRecover(&tree);
    
    cout << "\n5. Обход inorder после восстановления: ";
    bstInorder(tree.root);
    cout << endl;
    
    cout << "\n6. Восстановленное дерево:\n";
    bstPrintTree(tree.root);
    
    cout << "\n7. Проверяем другие обходы:\n";
    cout << "   Preorder:  ";
    bstPreorder(tree.root);
    cout << "\n   Postorder: ";
    bstPostorder(tree.root);
    cout << endl;
    
    bstFree(tree.root);
}
