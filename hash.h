#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <string>
using namespace std;

// Для метода цепочек
struct HashNode {
    string key;
    string value;
    HashNode* next;
};

struct HashTableChaining {
    HashNode** table;
    int capacity;
    int size;
};

// Для открытой адресации
struct HashEntry {
    string key;
    string value;
    bool isDeleted;
    bool isEmpty;
};

struct HashTableOpen {
    HashEntry* table;
    int capacity;
    int size;
};

// Функции для метода цепочек
void createHashTableChaining(HashTableChaining* ht, int cap);
void hashInsertChaining(HashTableChaining* ht, string key, string value);
string hashSearchChaining(HashTableChaining* ht, string key);
void hashDeleteChaining(HashTableChaining* ht, string key);
void printHashTableChaining(HashTableChaining* ht);
void freeHashTableChaining(HashTableChaining* ht);

// Функции для открытой адресации
void createHashTableOpen(HashTableOpen* ht, int cap);
void hashInsertOpen(HashTableOpen* ht, string key, string value);
string hashSearchOpen(HashTableOpen* ht, string key);
void hashDeleteOpen(HashTableOpen* ht, string key);
void printHashTableOpen(HashTableOpen* ht);
void freeHashTableOpen(HashTableOpen* ht);

// Хеш-функции
int hashFunction1(string key, int capacity); // Метод деления
int hashFunction2(string key, int capacity); // Метод умножения

// Римские цифры
string intToRoman(int num);
int romanToInt(string roman);

#endif
