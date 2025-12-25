#include "hash.h"
#include <iostream>
using namespace std;

// ==================== МЕТОД ЦЕПОЧЕК ====================

void createHashTableChaining(HashTableChaining* ht, int cap) {
    ht->capacity = cap;
    ht->size = 0;
    ht->table = new HashNode*[cap];
    
    for (int i = 0; i < cap; i++) {
        ht->table[i] = nullptr;
    }
}

int hashFunction1(string key, int capacity) {
    // Простая хеш-функция: сумма кодов символов
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    return hash % capacity;
}

int hashFunction2(string key, int capacity) {
    // Хеш-функция методом умножения
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = hash * 31 + key[i];
    }
    return abs(hash) % capacity;
}

void hashInsertChaining(HashTableChaining* ht, string key, string value) {
    int index = hashFunction1(key, ht->capacity);
    
    HashNode* newNode = new HashNode;
    newNode->key = key;
    newNode->value = value;
    newNode->next = nullptr;
    
    // Если цепочка пустая
    if (ht->table[index] == nullptr) {
        ht->table[index] = newNode;
    } else {
        // Добавляем в начало цепочки
        newNode->next = ht->table[index];
        ht->table[index] = newNode;
    }
    
    ht->size++;
}

string hashSearchChaining(HashTableChaining* ht, string key) {
    int index = hashFunction1(key, ht->capacity);
    
    HashNode* current = ht->table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return "Not Found";
}

void hashDeleteChaining(HashTableChaining* ht, string key) {
    int index = hashFunction1(key, ht->capacity);
    
    HashNode* current = ht->table[index];
    HashNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                // Удаляем первый элемент цепочки
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            delete current;
            ht->size--;
            return;
        }
        
        prev = current;
        current = current->next;
    }
}

void printHashTableChaining(HashTableChaining* ht) {
    cout << "Хеш-таблица (метод цепочек):" << endl;
    for (int i = 0; i < ht->capacity; i++) {
        cout << "[" << i << "]: ";
        
        HashNode* current = ht->table[i];
        if (current == nullptr) {
            cout << "пусто";
        } else {
            while (current != nullptr) {
                cout << current->key << ":" << current->value;
                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
        }
        cout << endl;
    }
}

void freeHashTableChaining(HashTableChaining* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        HashNode* current = ht->table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    delete[] ht->table;
    ht->size = 0;
    ht->capacity = 0;
}

// ==================== ОТКРЫТАЯ АДРЕСАЦИЯ ====================

void createHashTableOpen(HashTableOpen* ht, int cap) {
    ht->capacity = cap;
    ht->size = 0;
    ht->table = new HashEntry[cap];
    
    for (int i = 0; i < cap; i++) {
        ht->table[i].isEmpty = true;
        ht->table[i].isDeleted = false;
    }
}

void hashInsertOpen(HashTableOpen* ht, string key, string value) {
    if (ht->size >= ht->capacity) {
        cout << "Таблица переполнена!" << endl;
        return;
    }
    
    int index = hashFunction1(key, ht->capacity);
    int originalIndex = index;
    int i = 0;
    
    // Линейное пробирование
    while (!ht->table[index].isEmpty && !ht->table[index].isDeleted) {
        if (ht->table[index].key == key) {
            // Обновляем существующий ключ
            ht->table[index].value = value;
            return;
        }
        
        i++;
        index = (originalIndex + i) % ht->capacity;
        
        if (index == originalIndex) {
            // Прошли весь круг
            cout << "Не удалось вставить элемент" << endl;
            return;
        }
    }
    
    // Нашли свободное место
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].isEmpty = false;
    ht->table[index].isDeleted = false;
    ht->size++;
}

string hashSearchOpen(HashTableOpen* ht, string key) {
    int index = hashFunction1(key, ht->capacity);
    int originalIndex = index;
    int i = 0;
    
    while (!ht->table[index].isEmpty) {
        if (!ht->table[index].isDeleted && ht->table[index].key == key) {
            return ht->table[index].value;
        }
        
        i++;
        index = (originalIndex + i) % ht->capacity;
        
        if (index == originalIndex) {
            break;
        }
    }
    
    return "Not Found";
}

void hashDeleteOpen(HashTableOpen* ht, string key) {
    int index = hashFunction1(key, ht->capacity);
    int originalIndex = index;
    int i = 0;
    
    while (!ht->table[index].isEmpty) {
        if (!ht->table[index].isDeleted && ht->table[index].key == key) {
            ht->table[index].isDeleted = true;
            ht->size--;
            return;
        }
        
        i++;
        index = (originalIndex + i) % ht->capacity;
        
        if (index == originalIndex) {
            break;
        }
    }
}

void printHashTableOpen(HashTableOpen* ht) {
    cout << "Хеш-таблица (открытая адресация):" << endl;
    for (int i = 0; i < ht->capacity; i++) {
        cout << "[" << i << "]: ";
        
        if (ht->table[i].isEmpty) {
            cout << "пусто";
        } else if (ht->table[i].isDeleted) {
            cout << "удалено";
        } else {
            cout << ht->table[i].key << ":" << ht->table[i].value;
        }
        cout << endl;
    }
}

void freeHashTableOpen(HashTableOpen* ht) {
    delete[] ht->table;
    ht->size = 0;
    ht->capacity = 0;
}

// ==================== РИМСКИЕ ЦИФРЫ ====================

string intToRoman(int num) {
    if (num <= 0 || num > 3999) {
        return "Invalid";
    }
    
    // Массив значений и символов
    string roman = "";
    
    // Таблица соответствий
    while (num >= 1000) { roman += "M"; num -= 1000; }
    if (num >= 900) { roman += "CM"; num -= 900; }
    if (num >= 500) { roman += "D"; num -= 500; }
    if (num >= 400) { roman += "CD"; num -= 400; }
    while (num >= 100) { roman += "C"; num -= 100; }
    if (num >= 90) { roman += "XC"; num -= 90; }
    if (num >= 50) { roman += "L"; num -= 50; }
    if (num >= 40) { roman += "XL"; num -= 40; }
    while (num >= 10) { roman += "X"; num -= 10; }
    if (num >= 9) { roman += "IX"; num -= 9; }
    if (num >= 5) { roman += "V"; num -= 5; }
    if (num >= 4) { roman += "IV"; num -= 4; }
    while (num >= 1) { roman += "I"; num -= 1; }
    
    return roman;
}

int romanToInt(string roman) {
    int result = 0;
    
    for (int i = 0; i < roman.length(); i++) {
        char current = roman[i];
        char next = (i + 1 < roman.length()) ? roman[i + 1] : '\0';
        
        switch (current) {
            case 'I':
                if (next == 'V') { result += 4; i++; }
                else if (next == 'X') { result += 9; i++; }
                else result += 1;
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                if (next == 'L') { result += 40; i++; }
                else if (next == 'C') { result += 90; i++; }
                else result += 10;
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                if (next == 'D') { result += 400; i++; }
                else if (next == 'M') { result += 900; i++; }
                else result += 100;
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
        }
    }
    
    return result;
}
