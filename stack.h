#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
using namespace std;

struct Stack{
  string elements[100]; 
  int top; // индекс верхнего элемента
};

void push(Stack& st, string el);
string pop(Stack& st);
void print(Stack& st);
void runStack();

#endif
