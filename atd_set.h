#ifndef ATD_SET_H
#define ATD_SET_H
#include <iostream>
#include <string>
#include <fstream>  
using namespace std;

struct ATD_Set {
    string* elements;
    int size;
    int capacity;
};

void atd_create(ATD_Set* s, int capacity);
void atd_add(ATD_Set* s, string element);
void atd_delete(ATD_Set* s, string element);
bool atd_contains(ATD_Set* s, string element);
void atd_print(ATD_Set* s);
void atd_free(ATD_Set* s);

void atd_process_file(const char* filename, const char* query);

#endif
