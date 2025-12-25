#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <string>
using namespace std;

struct Array{
  string* data;
  int size;
};

void createArray(Array* arr, int initialSize);
void addToEnd(Array* arr, string value);
void addToIndex(Array* arr, int index, string value);
string getIndex(Array* arr, int index);
void deleteByIndex(Array* arr, int index);
void replaceByIndex(Array* arr, int index, string value);
int length(Array* arr);
void printArray(Array* arr);
void runArray();

#endif
