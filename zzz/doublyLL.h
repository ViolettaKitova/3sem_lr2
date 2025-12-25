#ifndef DOUBLYLL_H
#define DOUBLYLL_H
#include <iostream>
#include <string>
using namespace std;

struct NodeDLL{
  string data; //имеющиеся элементы
  NodeDLL* next;
  NodeDLL* prev;
};

bool ErrDLL(NodeDLL* head);
void addToHeadDLL(NodeDLL*& head, string el);
void addToTailDLL(NodeDLL*& head, string el);
void addBeforeDLL(NodeDLL*& head, string el, string target);
void addAfterDLL(NodeDLL*& head, string el, string target);
void delToHeadDLL(NodeDLL*& head);
void delToTailDLL(NodeDLL*& head);
void delBeforeDLL(NodeDLL*& head, string target);
void delAfterDLL(NodeDLL*& head, string target);
void delByElDLL(NodeDLL*& head, string el);
void printDLL(NodeDLL* head);        
void printBackwardDLL(NodeDLL* tail);  
void searchDLL(NodeDLL* head, string el); 
void runDoublyLinkedList();

#endif
