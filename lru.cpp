#include "lru.h"
#include <iostream>
using namespace std;

int lruHash(int key, int size) {
    return key % size;
}

void createLRUCache(LRUCache* cache, int capacity) {
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = nullptr;
    cache->tail = nullptr;
    
    // Создаем хеш-таблицу
    cache->hashSize = capacity * 2;
    cache->hashTable = new LRUNode*[cache->hashSize];
    
    for (int i = 0; i < cache->hashSize; i++) {
        cache->hashTable[i] = nullptr;
    }
}

//функция для поиска в хеш-таблице
LRUNode* lruFindInHash(LRUCache* cache, int key) {
    int index = lruHash(key, cache->hashSize);
    LRUNode* node = cache->hashTable[index];
    
    while (node != nullptr) {
        if (node->key == key) {
            return node;
        }
        node = node->next; 
    }
    
    return nullptr;
}

//функция для добавления в хеш-таблицу
void lruAddToHash(LRUCache* cache, LRUNode* node) {
    int index = lruHash(node->key, cache->hashSize);
    
    node->next = cache->hashTable[index];
    cache->hashTable[index] = node;
}

//функция для удаления из хеш-таблицы
void lruRemoveFromHash(LRUCache* cache, int key) {
    int index = lruHash(key, cache->hashSize);
    LRUNode* current = cache->hashTable[index];
    LRUNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                // Удаляем первый элемент цепочки
                cache->hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            return;
        }
        prev = current;
        current = current->next;
    }
}

void lruPut(LRUCache* cache, int key, string value) {
    LRUNode* existing = lruFindInHash(cache, key);
    
    if (existing != nullptr) {
        existing->value = value;
        
        if (existing != cache->head) {
            if (existing->prev) existing->prev->next = existing->next;
            if (existing->next) existing->next->prev = existing->prev;
            
            if (existing == cache->tail) {
                cache->tail = existing->prev;
            }
            
            existing->next = cache->head;
            existing->prev = nullptr;
            
            if (cache->head != nullptr) {
                cache->head->prev = existing;
            }
            
            cache->head = existing;
            
            if (cache->tail == nullptr) {
                cache->tail = existing;
            }
        }
        return;
    }
    
    if (cache->size >= cache->capacity) {
        LRUNode* lruNode = cache->tail;
        
        if (lruNode != nullptr) {
            if (lruNode->prev != nullptr) {
                lruNode->prev->next = nullptr;
            }
            cache->tail = lruNode->prev;
            
            if (cache->head == lruNode) {
                cache->head = nullptr;
            }
            
            lruRemoveFromHash(cache, lruNode->key);
            
            delete lruNode;
            cache->size--;
        }
    }
    
    LRUNode* newNode = new LRUNode;
    newNode->key = key;
    newNode->value = value;
    newNode->prev = nullptr;
    newNode->next = cache->head;
    
    lruAddToHash(cache, newNode);
    
    if (cache->head != nullptr) {
        cache->head->prev = newNode;
    }
    
    cache->head = newNode;
    
    if (cache->tail == nullptr) {
        cache->tail = newNode;
    }
    
    cache->size++;
}

string lruGet(LRUCache* cache, int key) {
    LRUNode* node = lruFindInHash(cache, key);
    
    if (node == nullptr) {
        return "-1"; 
    }
    
    if (node != cache->head) {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        
        if (node == cache->tail) {
            cache->tail = node->prev;
        }
        
        node->next = cache->head;
        node->prev = nullptr;
        
        if (cache->head != nullptr) {
            cache->head->prev = node;
        }
        
        cache->head = node;
        
        if (cache->tail == nullptr) {
            cache->tail = node;
        }
    }
    
    return node->value;
}

void lruPrint(LRUCache* cache) {
    cout << "LRU Cache (capacity: " << cache->capacity << ", size: " << cache->size << ")\n";
    
    if (cache->size == 0) {
        cout << "Пусто\n";
        return;
    }
    
    cout << "Самый недавний -> самый старый: ";
    
    LRUNode* current = cache->head;
    while (current != nullptr) {
        cout << current->key << ":" << current->value;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

void lruFree(LRUCache* cache) {
    LRUNode* current = cache->head;
    while (current != nullptr) {
        LRUNode* next = current->next;
        delete current;
        current = next;
    }
    
    // Очищаем хеш-таблицу
    delete[] cache->hashTable;
    
    cache->head = nullptr;
    cache->tail = nullptr;
    cache->size = 0;
    cache->capacity = 0;
}

void lruDemoTask7() {
    cout << "Демонстрация задание 7" << endl;
    
    LRUCache cache;
    createLRUCache(&cache, 2);
    
    cout << "Пример из задания:\n";
    cout << "capacity = 2\n\n";
    
    cout << "1. SET 1 2\n";
    lruPut(&cache, 1, "2");
    lruPrint(&cache);
    
    cout << "\n2. SET 2 3\n";
    lruPut(&cache, 2, "3");
    lruPrint(&cache);
    
    cout << "\n3. SET 1 5\n";
    lruPut(&cache, 1, "5");
    lruPrint(&cache);
    
    cout << "\n4. SET 4 5\n";
    lruPut(&cache, 4, "5");
    lruPrint(&cache);
    
    cout << "\n5. GET 4\n";
    cout << "   Результат: " << lruGet(&cache, 4) << endl;
    lruPrint(&cache);
    
    cout << "\n6. SET 1 2\n";
    lruPut(&cache, 1, "2");
    lruPrint(&cache);
    
    cout << "\n7. GET 3\n";
    cout << "   Результат: " << lruGet(&cache, 3) << endl;
    
    cout << "\nИтоговый вывод: 5 -1\n";
    
    lruFree(&cache);
}
