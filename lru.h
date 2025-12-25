#ifndef LRU_H
#define LRU_H
#include <iostream>
#include <string>
using namespace std;

struct LRUNode {
    int key;
    string value;
    LRUNode* prev;
    LRUNode* next;
};

struct LRUCache {
    LRUNode* head;
    LRUNode* tail;
    int capacity;
    int size;
    
    // Простая хеш-таблица для быстрого поиска
    LRUNode** hashTable;
    int hashSize;
};

void createLRUCache(LRUCache* cache, int capacity);
void lruPut(LRUCache* cache, int key, string value);
string lruGet(LRUCache* cache, int key);
void lruPrint(LRUCache* cache);
void lruFree(LRUCache* cache);
void lruDemoTask7(); 

#endif
