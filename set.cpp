#include "set.h"
#include <iostream>
using namespace std;

void createSet(Set* s, int initialCapacity) {
    s->capacity = initialCapacity;
    s->size = 0;
    s->elements = new string[initialCapacity];
}

void setAdd(Set* s, string value) {
    // Проверяем, нет ли уже такого элемента
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == value) {
            return; // Элемент уже есть
        }
    }
    
    // Если места нет, увеличиваем массив
    if (s->size >= s->capacity) {
        int newCapacity = s->capacity * 2;
        string* newData = new string[newCapacity];
        
        for (int i = 0; i < s->size; i++) {
            newData[i] = s->elements[i];
        }
        
        delete[] s->elements;
        s->elements = newData;
        s->capacity = newCapacity;
    }
    
    // Добавляем элемент
    s->elements[s->size] = value;
    s->size++;
}

void setDelete(Set* s, string value) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == value) {
            // Сдвигаем все элементы после найденного
            for (int j = i; j < s->size - 1; j++) {
                s->elements[j] = s->elements[j + 1];
            }
            s->size--;
            return;
        }
    }
}

bool setContains(Set* s, string value) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == value) {
            return true;
        }
    }
    return false;
}

void printSet(Set* s) {
    cout << "{ ";
    for (int i = 0; i < s->size; i++) {
        cout << s->elements[i];
        if (i < s->size - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void freeSet(Set* s) {
    delete[] s->elements;
    s->size = 0;
    s->capacity = 0;
}

// Задание 3: Разбиение множества (вариант 1)
bool canPartitionSet(Set* s) {
    // Конвертируем string в int
    int* nums = new int[s->size];
    int total = 0;
    
    for (int i = 0; i < s->size; i++) {
        nums[i] = stoi(s->elements[i]);
        total += nums[i];
    }
    
    cout << "Множество: ";
    printSet(s);
    cout << "Сумма всех элементов: " << total << endl;
    
    if (total % 2 != 0) {
        cout << "Невозможно разбить (сумма нечетная)" << endl;
        delete[] nums;
        return false;
    }
    
    int target = total / 2;
    cout << "Ищем подмножества с суммой = " << target << endl;
    
    // Генерируем все подмножества
    int totalSubsets = 1 << s->size; // 2^n
    
    for (int mask = 0; mask < totalSubsets; mask++) {
        int sum = 0;
        for (int i = 0; i < s->size; i++) {
            if (mask & (1 << i)) {
                sum += nums[i];
            }
        }
        
        if (sum == target && mask != 0 && mask != totalSubsets - 1) {
            cout << "\nНайдено разбиение:\n";
            
            // Первое подмножество
            cout << "Подмножество 1: { ";
            bool first = true;
            int sum1 = 0;
            for (int i = 0; i < s->size; i++) {
                if (mask & (1 << i)) {
                    if (!first) cout << ", ";
                    cout << nums[i];
                    sum1 += nums[i];
                    first = false;
                }
            }
            cout << " } Сумма = " << sum1 << endl;
            
            // Второе подмножество
            cout << "Подмножество 2: { ";
            first = true;
            int sum2 = 0;
            for (int i = 0; i < s->size; i++) {
                if (!(mask & (1 << i))) {
                    if (!first) cout << ", ";
                    cout << nums[i];
                    sum2 += nums[i];
                    first = false;
                }
            }
            cout << " } Сумма = " << sum2 << endl;
            
            delete[] nums;
            return true;
        }
    }
    
    cout << "Не найдено подмножеств с суммой " << target << endl;
    delete[] nums;
    return false;
}
