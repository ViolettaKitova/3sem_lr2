#include "atd_set.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void atd_create(ATD_Set* s, int capacity) {
    s->capacity = capacity;
    s->size = 0;
    s->elements = new string[capacity];
}

void atd_add(ATD_Set* s, string element) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == element) {
            return; 
        }
    }
    
    if (s->size >= s->capacity) {
        int newCapacity = s->capacity * 2;
        string* newArray = new string[newCapacity];
        
        for (int i = 0; i < s->size; i++) {
            newArray[i] = s->elements[i];
        }
        
        delete[] s->elements;
        s->elements = newArray;
        s->capacity = newCapacity;
    }
    
    s->elements[s->size] = element;
    s->size++;
}

void atd_delete(ATD_Set* s, string element) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == element) {
            for (int j = i; j < s->size - 1; j++) {
                s->elements[j] = s->elements[j + 1];
            }
            s->size--;
            return;
        }
    }
}

bool atd_contains(ATD_Set* s, string element) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == element) {
            return true;
        }
    }
    return false;
}

void atd_print(ATD_Set* s) {
    cout << "{ ";
    for (int i = 0; i < s->size; i++) {
        cout << s->elements[i];
        if (i < s->size - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void atd_free(ATD_Set* s) {
    delete[] s->elements;
    s->size = 0;
    s->capacity = 0;
}

void atd_process_file(const char* filename, const char* query) {
    ATD_Set myset;
    atd_create(&myset, 10);
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }
    
    string line;
    cout << "Чтение файла " << filename << "..." << endl;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string command, value;
        ss >> command >> value;
        
        if (command == "SETADD") {
            atd_add(&myset, value);
            cout << "SETADD " << value << endl;
        }
        else if (command == "SETDEL") {
            atd_delete(&myset, value);
            cout << "SETDEL " << value << endl;
        }
        else if (command == "SET_AT") {
            bool found = atd_contains(&myset, value);
            cout << "SET_AT " << value << " = " << (found ? "true" : "false") << endl;
        }
    }
    
    file.close();
    
    cout << "\nЗапрос: " << query << endl;
    stringstream ss(query);
    string command, value;
    ss >> command >> value;
    
    if (command == "SET_AT") {
        bool found = atd_contains(&myset, value);
        cout << "Результат: " << (found ? "true" : "false") << endl;
    }
    
    cout << "\nИтоговое множество: ";
    atd_print(&myset);
    
    atd_free(&myset);
}
