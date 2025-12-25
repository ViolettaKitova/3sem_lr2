#include <iostream>
#include <queue>
#include <string>
#include <stack>
#include "tree.h"
#include <fstream>
using namespace std;

/*struct Node {
  string data;
  Node* left; //левый потомок
  Node* right; //правый
};

struct CompleteBinaryTree {
  Node* root; //корень
  int count; //кол-во узлов в дереве
};*/

Node* createNode(string el) { //создание узла
  Node* newNode = new Node;
  newNode->data = el;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

void createTree(CompleteBinaryTree& tree){
  tree.root = nullptr;
  tree.count = 0;
}

void add(CompleteBinaryTree& tree, string el) {
  Node* newNode = createNode(el);
  
  if (tree.root == nullptr) {
    tree.root = newNode;
    tree.count = 1;
    return;
  }
    
  int position = tree.count + 1;
  string path = ""; //последовательность букв R/L, которая говорит куда идти
  
  int temp = position; 
  while (temp > 1) {
    if (temp % 2 == 0) {
      path = "L" + path;
    } else {
      path = "R" + path;
    }
      temp /= 2;
  }
    
  Node* current = tree.root;
  for (int i = 0; i < path.length() - 1; i++) {
    if (path[i] == 'L') {
      current = current->left;
    } else {
      current = current->right;
    }
  }
    
  if (path.back() == 'L') { //если последний шаг - левый, то добавляем как левого потомка
    current->left = newNode;
  } else {
    current->right = newNode;
  }
  tree.count++;
}

bool search(Node* root, string value) { //поиск через обход в ширину
  if (root == nullptr){
    cout << "Ошибка! Корень пуст" << endl;
    return false;
  }    
  queue<Node*> q; //очередь из указателей на Node
  q.push(root);  
  while (!q.empty()) { 
    Node* current = q.front(); //front - передний элемент      
    q.pop();                 
    if (current->data == value) {     
      return true;                  
    }
    if (current->left != nullptr) q.push(current->left); //если левый существует то добавляем в очередь
    if (current->right != nullptr) q.push(current->right); 
  }
  return false;
}

bool isComplete(Node* root, int index, int totalNodes) {
  if (root == nullptr) return true; //пустое дерево - полное
  if (index >= totalNodes) return false;
  return isComplete(root->left, 2 * index + 1, totalNodes) && isComplete(root->right, 2 * index + 2, totalNodes);
}

int countNodes(Node* root) {
  if (root == nullptr) return 0;
  return 1 + countNodes(root->left) + countNodes(root->right);
}

void printDepth(Node* root) { //в глубину сверху-вниз
  if (root == nullptr) return; 
  stack<Node*> s;
  s.push(root);
  while (!s.empty()) {
    Node* current = s.top();
    s.pop();
    cout << current->data << " ";    
    if (current->right != nullptr) s.push(current->right);
    if (current->left != nullptr) s.push(current->left);
  }
  cout << endl;
}

void printBreadth(Node* root) {
  if (root == nullptr){
    cout << "Ошибка! Корень пуст" << endl;
    return;
  }
  queue<Node*> q;
  q.push(root); //добавляем в очередь корень
  while (!q.empty()) { //пока очередь не пуста
    Node* current = q.front(); //первый элемент из очереди
    q.pop();                        
    cout << current->data << " "; 
    if (current->left != nullptr) q.push(current->left); //если есть левый потомок - добавляем в очередь
    if (current->right != nullptr) q.push(current->right);  
  }
  cout << endl;
}

void runTree() {
  CompleteBinaryTree tree;
  createTree(tree);
  string command;
  ofstream logfile("log.txt", ios::app);
  logfile << "=== Начало работы с деревом ===" << endl;
  
  cout << "Введите команду для полного бинарного дерева: add, search, complete, depth, breadth, count, exit" << endl;  
  while (true) {
    cin >> command;   
    logfile << "Команда: " << command << endl;
    
    if (command == "add") {
      string el;
      cin >> el;
      add(tree, el);
      cout << "Элемент добавлен" << endl;
      logfile << "Добавлен элемент в дерево: " << el << endl;
    } else if (command == "search") {
      string value;
      cin >> value;
      if (search(tree.root, value)) {
        cout << "'" << value << "' найден" << endl;
        logfile << "Элемент найден: " << value << endl;
      } else {
        cout << "'" << value << "' не найден" << endl;
        logfile << "Элемент не найден: " << value << endl;
      }
    } else if (command == "complete") {
      int totalNodes = countNodes(tree.root);
      bool complete = isComplete(tree.root, 0, totalNodes);
      cout << (complete ? "Да" : "Нет") << endl;
      logfile << "Проверка полноты дерева: " << (complete ? "Да" : "Нет") << endl;
    } else if (command == "depth") {
      printDepth(tree.root);
      logfile << "Вывод дерева в глубину" << endl;
    } else if (command == "breadth") {
      printBreadth(tree.root);
      logfile << "Вывод дерева в ширину" << endl;
    } else if (command == "count") {
      int nodeCount = countNodes(tree.root);
      cout << nodeCount << endl;
      logfile << "Количество узлов: " << nodeCount << endl;
    } else if (command == "exit") {
      logfile << "=== Завершение работы с деревом ===" << endl << endl;
      break;
    } else {
      cout << "Ошибка! Неизвестная команда" << endl;
      logfile << "Неизвестная команда: " << command << endl;
    }
  }
  logfile.close();
  return;
}
