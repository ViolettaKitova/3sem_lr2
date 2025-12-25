#include <iostream>
#include <string>
#include "queue.h"
#include <fstream>
using namespace std;

/*struct Queue{
  string elements[100];
  int start;
  int end; 
};*/

void push(Queue& q, string el){
  if (q.end > 99){
    cout << "Ошибка! Нельзя добавить элемент" << endl;
    return;
  } else {
    q.end++;
    q.elements[q.end] = el;
    if (q.end == 0){
      q.start = 0;
    }
  }
}

string pop(Queue& q){ //чтоб вернул удаляемый 
  if (q.end < q.start || q.end == -1){
    cout << "Ошибка! Нельзя удалить элемент" << endl;
    return "";
  } else {
    string delEl = q.elements[q.start];
    q.start++;
    if (q.start > q.end){
      q.start = 0;
      q.end = -1;
    }
    return delEl;
  }
}

void print(Queue& q){
  if (q.start > q.end || q.end == -1){
    cout << "Ошибка!" << endl;
    return;
  }
  for (int i = q.start; i <= q.end; i++){
    cout << q.elements[i] << " ";
  }
  cout << endl;
  return;
}

void runQueue(){
  Queue q;
  q.start = 0;
  q.end = -1;
  string command;
  string el;
  ofstream logfile("log.txt", ios::app);
  logfile << "=== Начало работы с очередью ===" << endl;
  
  cout << "Работа с очередью" << endl;
  while (true){
    cout << "Введите команду: push, pop, print, exit" << endl;
    cin >> command;
    
    logfile << "Команда: " << command << endl;
    
    if (command == "push"){
      cout << "Введите элемент: " << endl;
      cin >> el;
      push(q, el);
      logfile << "Добавлен элемент в очередь: " << el << endl;
    }
    else if (command == "pop"){
      pop(q);
      logfile << "Удален элемент из очереди" << endl;
    }
    else if (command == "print"){
      print(q);
      logfile << "Вывод очереди на экран" << endl;
    }
    else if (command == "exit"){
      logfile << "=== Завершение работы с очередью ===" << endl << endl;
      break;
    } else {
      cout << "Ошибка!" << endl;
      logfile << "Неизвестная команда: " << command << endl;
    }
  }
  logfile.close();
}
