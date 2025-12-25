#include <iostream>
#include <string>
#include "array.h"
#include <fstream>
using namespace std;

void createArray(Array* arr, int initialSize){ //initialSize - начальный размер массива
  arr->size = initialSize;
  arr->data = new string[initialSize];
}

void addToEnd(Array* arr, string value){
  string* newData = new string[arr->size + 1];
  for (int i = 0; i < arr->size; i++){
    newData[i] = arr->data[i];
  }
  newData[arr->size] = value;
  delete[] arr->data;
  arr->data = newData;
  arr->size++;
}

void addToIndex(Array* arr, int index, string value){
  if (index < 0 || index > arr->size){
    cout << "Ошибка! Некорректный индекс" << endl;
    return;
  }
  string* newData = new string[arr->size + 1];
  for (int i = 0; i < index; i++){
    newData[i] = arr->data[i];
  }
  newData[index] = value;
  for (int i = index; i < arr->size; i++){
    newData[i + 1] = arr->data[i];
  }
  delete[] arr->data;
  arr->data = newData;
  arr->size++;
}

string getIndex(Array* arr, int index){
  if (index < 0 || index >= arr->size){
    cout << "Ошибка! Неверный индекс" << endl;
    return "";
  }
  return arr->data[index];
}

void deleteByIndex(Array* arr, int index){
  if (index < 0 || index >= arr->size){
    cout << "Ошибка! Неверный индекс" << endl;
    return;
  }
  if (arr->size <= 1) {
    cout << "Ошибка! Нельзя удалить элемент" << endl;
    return;
  }
  string* newData = new string[arr->size - 1];
  for (int i = 0; i < index; i++){
    newData[i] = arr->data[i];
  }
  for (int i = index + 1; i < arr->size; i++){
    newData[i - 1] = arr->data[i];
  }
  delete[] arr->data;
  arr->data = newData;
  arr->size--;
}

void replaceByIndex(Array* arr, int index, string value){
  if (index < 0 || index >= arr->size){
    cout << "Ошибка! Неверный индекс" << endl;
    return;
  }
  arr->data[index] = value;
}

int length(Array* arr){
  return arr->size;
}

void printArray(Array* arr) {
    cout << "Массив: [";
    for (int i = 0; i < arr->size; i++) {
        cout << arr->data[i];
        if (i < arr->size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void runArray(){
  Array myArray;
  string command;
  bool arrayCreated = false;
  ofstream logfile("log.txt", ios::app);
  cout << "Работа с массивом" << endl;
  cout << "Доступные команды: createArray, addToEnd, addToIndex, getIndex, deleteByIndex, replaceByIndex, length, printArray, exit" << endl;

  logfile << "=== Начало работы с массивом ===" << endl;
  
  while(true) {
    cout << "\nВведите команду: ";
    cin >> command;
    
    logfile << "Выполнена команда: " << command << endl;
    
    if (command == "exit") {
      logfile << "=== Завершение работы ===" << endl << endl;
      break;
    }
    else if (command == "createArray") {
      if (!arrayCreated) {
        createArray(&myArray, 0);
        arrayCreated = true;
        cout << "Массив создан" << endl;
        logfile << "Массив создан" << endl;
      } else {
        cout << "Массив уже создан" << endl;
        logfile << "Попытка повторного создания массива" << endl;
      }
    }
    else if (command == "addToEnd") {
      string value;
      cout << "Введите значение: ";
      cin >> value;
      addToEnd(&myArray, value);
      logfile << "Добавлен элемент в конец: " << value << endl;
    }
    else if (command == "addToIndex") {
      int index;
      string value;
      cout << "Введите индекс: ";
      cin >> index;
      cout << "Введите значение: ";
      cin >> value;
      addToIndex(&myArray, index, value);
      logfile << "Добавлен элемент по индексу " << index << ": " << value << endl;
    }
    else if (command == "getIndex") {
      int index;
      cout << "Введите индекс: ";
      cin >> index;
      string value = getIndex(&myArray, index);
      if (value != "") {
        cout << value << endl;
        logfile << "Получен элемент по индексу " << index << ": " << value << endl;
      }
    }
    else if (command == "deleteByIndex") {
      int index;
      cout << "Введите индекс: ";
      cin >> index;
      deleteByIndex(&myArray, index);
      logfile << "Удален элемент по индексу " << index << endl;
    }
    else if (command == "replaceByIndex") {
      int index;
      string value;
      cout << "Введите индекс: ";
      cin >> index;
      cout << "Введите новое значение: ";
      cin >> value;
      replaceByIndex(&myArray, index, value);
      logfile << "Заменен элемент по индексу " << index << " на: " << value << endl;
    }
    else if (command == "length") {
      int len = length(&myArray);
      cout << "Длина массива: " << len << endl;
      logfile << "Запрос длины массива: " << len << endl;
    }
    else if (command == "printArray") {
      printArray(&myArray);
      logfile << "Вывод массива на экран" << endl;
    }
    else {
      cout << "Неизвестная команда! Попробуйте снова." << endl;
      logfile << "Неизвестная команда: " << command << endl;
    }
  }
  
  if (arrayCreated) {
    delete[] myArray.data;
    logfile << "Память массива освобождена" << endl;
  }
  logfile.close();
}
