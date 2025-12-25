#ifndef SET_H
#define SET_H
#include <iostream>
#include <string>
using namespace std;

struct Set {
    string* elements;
    int size;
    int capacity;
};

void createSet(Set* s, int initialCapacity);
void setAdd(Set* s, string value);
void setDelete(Set* s, string value);
bool setContains(Set* s, string value);
void printSet(Set* s);
void freeSet(Set* s);
bool canPartitionSet(Set* s);

#endif
