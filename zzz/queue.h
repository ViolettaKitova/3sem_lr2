#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
using namespace std;

struct Queue{
  string elements[100];
  int start;
  int end; 
};

void push(Queue& q, string el);
string pop(Queue& q);
void print(Queue& q);
void runQueue();

#endif
