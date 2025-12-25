#include <iostream>
#include "tasks.h"
using namespace std;

void printMenu() {
    
    cout << "Выберите задание:\n";
    cout << "1. Обратная польская запись\n";
    cout << "2. АТД Множество\n";
    cout << "3. Разбиение множества\n";
    cout << "4. Все подмассивы\n";
    cout << "5. Восстановление BST\n";
    cout << "6. Хеш-таблица\n";
    cout << "7. LRU кэш\n";
    cout << "0. Выход\n";
    cout << "> ";
}

int main() {
    while (true) {
        printMenu();
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: task1_rpn(); break;
            case 2: task2_atd_set(); break;
            case 3: task3_partition(); break;
            case 4: task4_subsets(); break;
            case 5: task5_bst(); break;
            case 6: task6_hash(); break;  
            case 7: task7_lru(); break;
            case 0: return 0;
            default: cout << "Неверный выбор\n";
        }
        
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
}
