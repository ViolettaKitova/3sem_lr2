#include <iostream>
#include <string>
#include "stack.h"
#include <fstream>
using namespace std;

/*struct Stack{
  string elements[100]; 
  int top; // индекс верхнего элемента
};*/

void push(Stack& st, string el){
  if (st.top >= 99){  
    cout << "Ошибка! Нельзя добавить элемент" << endl;
  } else {
    st.top++;  
    st.elements[st.top] = el;
  }
}

string pop(Stack& st){ //не просто удалил но и вернул удаляемый
  if (st.top < 0){  
    cout << "Ошибка! Нельзя удалить элемент" << endl;
    return ""; 
  } else {
    string delEl = st.elements[st.top];
    st.top--;
    return delEl;
  }
}

void print(Stack& st){
  for (int i = 0; i <= st.top; i++){  
    cout << st.elements[i] << " ";  
  }
  cout << endl;  
}

void runStack(){
  Stack st; 
  st.top = -1;  
  string command;  
  string el;
  ofstream logfile("log.txt", ios::app);
  logfile << "=== Начало работы со стеком ===" << endl;
  
  cout << "Работа со стеком" << endl;
  while(true) { 
    cout << "Введите команду: push, pop, print, exit" << endl;
    cin >> command;
    logfile << "Команда: " << command << endl;
    
    if (command == "push"){
      cout << "Введите элемент: ";
      cin >> el;
      push(st, el);  
      logfile << "Добавлен элемент в стек: " << el << endl;
    }
    else if (command == "pop"){
      pop(st);  
      logfile << "Удален элемент из стека" << endl;
    }
    else if (command == "print"){
      print(st);  
      logfile << "Вывод стека на экран" << endl;
    }
    else if (command == "exit"){
      logfile << "=== Завершение работы со стеком ===" << endl << endl;
      break;  
    } else {
      cout << "Неизвестная команда!" << endl;
      logfile << "Неизвестная команда: " << command << endl;
    }
  }
  logfile.close();
}
