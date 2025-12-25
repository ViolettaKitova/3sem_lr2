#include <iostream>
#include <string>
#include "doublyLL.h"
#include <fstream>
using namespace std;

bool ErrDLL(NodeDLL* head) {
    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return true;
    }
    return false;
}

void createHead(NodeDLL*& head, NodeDLL*& tail, string el){
    head = new NodeDLL;
    head->data = el;
    head->next = nullptr;
    head->prev = nullptr;
    tail = head;
}

void addToHeadDLL(NodeDLL*& head, NodeDLL*& tail, string el){
    if (head == nullptr) { //если пусто, то создаем голову
        createHead(head, tail, el);
        return;
    }
    NodeDLL* newNode = new NodeDLL;
    newNode->data = el;
    newNode->next = head;
    newNode->prev = nullptr;
    head->prev = newNode;
    head = newNode;
}

void addToTailDLL(NodeDLL*& head, NodeDLL*& tail, string el){
    if (head == nullptr) { //если пусто, то создаем голову
        createHead(head, tail, el);
        return;
    }
    NodeDLL* newNode = new NodeDLL;
    newNode->data = el;
    newNode->next = nullptr;
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

void addBeforeDLL(NodeDLL*& head, NodeDLL*& tail, string el, string target){ 
    if (ErrDLL(head)) return;
    NodeDLL* current = head;
    while (current != nullptr){
        if (current->data == target){
            NodeDLL* newNode = new NodeDLL;
            newNode->data = el;
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr){
                current->prev->next = newNode;
            } else {
                head = newNode;
            }
            current->prev = newNode;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден" << endl;
}

void addAfterDLL(NodeDLL*& head, NodeDLL*& tail, string el, string target){ 
    if (ErrDLL(head)) return;
    NodeDLL* current = head;
    while (current != nullptr){
        if (current->data == target){
            NodeDLL* newNode = new NodeDLL;
            newNode->data = el;
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next != nullptr){
                current->next->prev = newNode;
            } else {
                tail = newNode; 
            }
            current->next = newNode;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден" << endl;
}

void delToHeadDLL(NodeDLL*& head, NodeDLL*& tail){ 
    if (ErrDLL(head)) return;
    NodeDLL* temp = head;
    head = head->next;
    if (head != nullptr){
        head->prev = nullptr;
    } else {
        tail = nullptr; 
    }
    delete temp;
}

void delToTailDLL(NodeDLL*& head, NodeDLL*& tail){
    if (ErrDLL(head)) return;
    NodeDLL* nodeDel = tail;
    if (tail->prev != nullptr){
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete nodeDel;
}

void delBeforeDLL(NodeDLL*& head, NodeDLL*& tail, string target){ 
    if (head == nullptr || head->next == nullptr) {
        cout << "Ошибка! Недостаточно элементов" << endl;
        return;
    }
    NodeDLL* current = head;
    while (current != nullptr){
        if (current->data == target && current->prev != nullptr){
            NodeDLL* temp = current->prev;
            if (temp->prev != nullptr){
                temp->prev->next = current;
            } else {
                head = current; 
            }
            current->prev = temp->prev;
            delete temp;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден" << endl;
}

void delAfterDLL(NodeDLL*& head, NodeDLL*& tail, string target){ 
    if (head == nullptr || head->next == nullptr) {
        cout << "Ошибка! Недостаточно элементов" << endl;
        return;
    }
    NodeDLL* current = head;
    while (current != nullptr){
        if (current->data == target && current->next != nullptr){
            NodeDLL* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr){
                temp->next->prev = current;
            } else {
                tail = current; 
            }
            delete temp;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден или нет элемента после" << endl;
}

void delByElDLL(NodeDLL*& head, NodeDLL*& tail, string el){ 
    if (ErrDLL(head)) return;
    NodeDLL* current = head;
    while (current != nullptr){
        if (current->data == el){
            if (current->prev != nullptr){
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr){
                current->next->prev = current->prev;
            } else {
                tail = current->prev; 
            }
            delete current;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден" << endl;
}

void printDLL(NodeDLL* head){ 
    if (ErrDLL(head)) return;
    NodeDLL* temp = head;
    while (temp != nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void printBackwardDLL(NodeDLL* tail){ 
    if (tail == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }
    NodeDLL* temp = tail;
    while (temp != nullptr){
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
}

void searchDLL(NodeDLL* head, string el){
    if (ErrDLL(head)) return;
    NodeDLL* current = head;
    int pos = 0;
    while (current != nullptr){
        if (current->data == el){
            cout << "Элемент найден на позиции " << pos << endl;
            return;
        }
        current = current->next;
        pos++;
    }
    cout << "Элемент не найден" << endl;
}

void runDoublyLinkedList(){
    NodeDLL* head = nullptr;
    NodeDLL* tail = nullptr;
    string command;
    string el, target;
    ofstream logfile("log.txt", ios::app);
    
    logfile << "=== Начало работы с двусвязным списком ===" << endl;
    
    cout << "Двусвязный список" << endl;
    cout << "Доступные команды: createHead, addToHead, addToTail, addBefore, addAfter, delToHead, delToTail, delBefore, delAfter, delByEl, print, printBackward, search, exit" << endl;
    
    while (true){
        cout << "Введите команду:" << endl;
        cin >> command;
        
        logfile << "Команда: " << command << endl;
        
        if (command == "exit") {
            logfile << "=== Завершение работы с двусвязным списком ===" << endl << endl;
            break;
        }
        else if (command == "createHead"){
            cout << "Введите элемент для создания головы: ";
            cin >> el;
            createHead(head, tail, el);
            logfile << "Голова создана: " << el << endl;
        }
        else if (command == "addToHead"){
            cout << "Введите элемент: ";
            cin >> el;
            addToHeadDLL(head, tail, el); 
            logfile << "Добавлен элемент в начало: " << el << endl;
        }
        else if (command == "addToTail"){
            cout << "Введите элемент: ";
            cin >> el;
            addToTailDLL(head, tail, el); 
            logfile << "Добавлен элемент в конец: " << el << endl;
        }
        else if (command == "addBefore"){
            cout << "Введите элемент, который необходимо добавить: ";
            cin >> el;
            cout << "Введите элемент, перед которым добавляем: ";
            cin >> target;
            addBeforeDLL(head, tail, el, target); 
            logfile << "Добавлен элемент " << el << " перед " << target << endl;
        }
        else if (command == "addAfter"){
            cout << "Введите элемент, который необходимо добавить: ";
            cin >> el;
            cout << "Введите элемент, после которого добавляем: ";
            cin >> target;
            addAfterDLL(head, tail, el, target); 
            logfile << "Добавлен элемент " << el << " после " << target << endl;
        }
        else if (command == "delToHead"){
            delToHeadDLL(head, tail); 
            logfile << "Удален первый элемент" << endl;
        }
        else if (command == "delToTail"){
            delToTailDLL(head, tail);
            logfile << "Удален последний элемент" << endl;
        }
        else if (command == "delBefore"){
            cout << "Введите элемент, перед которым необходимо удалить элемент: ";
            cin >> target;
            delBeforeDLL(head, tail, target);
            logfile << "Удален элемент перед " << target << endl;
        }
        else if (command == "delAfter"){
            cout << "Введите элемент, после которого необходимо удалить элемент: ";
            cin >> target;
            delAfterDLL(head, tail, target); 
            logfile << "Удален элемент после " << target << endl;
        }
        else if (command == "delByEl"){
            cout << "Введите элемент, который нужно удалить: ";
            cin >> el;
            delByElDLL(head, tail, el); 
            logfile << "Удален элемент: " << el << endl;
        }
        else if (command == "print"){
            printDLL(head);
            logfile << "Вывод списка на экран" << endl;
        }
        else if (command == "printBackward"){
            printBackwardDLL(tail);
            logfile << "Вывод списка в обратном порядке" << endl;
        }
        else if (command == "search"){
            cout << "Введите элемент для поиска: ";
            cin >> el;
            searchDLL(head, el);
            logfile << "Поиск элемента: " << el << endl;
        }
        else{
            cout << "Ошибка! Неверная команда" << endl;
            logfile << "Неизвестная команда: " << command << endl;
        }
    }
    logfile.close();
}
