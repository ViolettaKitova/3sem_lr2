#include "tasks.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

//задание 1
void task1_rpn() {
    cout << "Задание 1: Обратная польская запись" << endl;
    cout << "Введите выражение в обратной польской записи (например: 3 4 + 2 *):" << endl;
    
    string input;
    cin.ignore();
    getline(cin, input);
    
    stack<int> st;
    string token;
    
    for (size_t i = 0; i <= input.length(); i++) {
        if (i < input.length() && input[i] != ' ') {
            token += input[i];
        } 
        else if (!token.empty()) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (st.size() < 2) {
                    cout << "Ошибка: недостаточно операндов" << endl;
                    return;
                }
                
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                int result = 0;
                
                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else if (token == "/") {
                    if (b == 0) {
                        cout << "Ошибка: деление на ноль\n";
                        return;
                    }
                    result = a / b;
                }
                
                st.push(result);
            }
            else {
                try {
                    int num = stoi(token);
                    st.push(num);
                } catch (...) {
                    cout << "Ошибка: неверный токен '" << token << "'\n";
                    return;
                }
            }
            token = "";
        }
    }
    
    if (st.size() == 1) {
        cout << "Результат: " << st.top() << endl;
    } else {
        cout << "Ошибка: некорректное выражение\n";
    }
}

//Задание 2
void task2_atd_set() {
    cout << "Задание 2: АТД Множество" << endl;
    
    const int MAX_SIZE = 100;
    string elements[MAX_SIZE];
    int size = 0;
    
    cout << "Операции: ADD, DEL, CONTAINS, PRINT, EXIT\n";
    
    while (true) {
        cout << "\n> ";
        string cmd;
        cin >> cmd;
        
        if (cmd == "ADD") {
            if (size >= MAX_SIZE) {
                cout << "Множество переполнено\n";
                continue;
            }
            
            string elem;
            cin >> elem;
            
            bool exists = false;
            for (int i = 0; i < size; i++) {
                if (elements[i] == elem) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                elements[size++] = elem;
                cout << "Добавлено: " << elem << endl;
            } else {
                cout << "Элемент уже существует\n";
            }
        }
        else if (cmd == "DEL") {
            string elem;
            cin >> elem;
            
            bool found = false;
            for (int i = 0; i < size; i++) {
                if (elements[i] == elem) {
                    found = true;
                    for (int j = i; j < size - 1; j++) {
                        elements[j] = elements[j + 1];
                    }
                    size--;
                    cout << "Удалено: " << elem << endl;
                    break;
                }
            }
            
            if (!found) {
                cout << "Элемент не найден\n";
            }
        }
        else if (cmd == "CONTAINS") {
            string elem;
            cin >> elem;
            
            bool found = false;
            for (int i = 0; i < size; i++) {
                if (elements[i] == elem) {
                    found = true;
                    break;
                }
            }
            
            cout << (found ? "true" : "false") << endl;
        }
        else if (cmd == "PRINT") {
            cout << "{ ";
            for (int i = 0; i < size; i++) {
                cout << elements[i];
                if (i < size - 1) cout << ", ";
            }
            cout << " }" << endl;
        }
        else if (cmd == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда\n";
        }
    }
}

//Задание 3
void task3_partition() {
    cout << "Задание 3: Разбиение множества" << endl;
    
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    
    vector<int> nums(n);
    int total = 0;
    
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        total += nums[i];
    }
    
    if (total % 2 != 0) {
        cout << "Нельзя разбить на равные части (сумма нечетная)\n";
        return;
    }
    
    int target = total / 2;
    
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j < nums[i-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i-1]];
            }
        }
    }
    
    if (!dp[n][target]) {
        cout << "Нельзя разбить на равные части\n";
        return;
    }
    
    vector<int> subset1, subset2;
    int j = target;
    
    for (int i = n; i > 0 && j > 0; i--) {
        if (!dp[i-1][j]) {
            subset1.push_back(nums[i-1]);
            j -= nums[i-1];
        } else {
            subset2.push_back(nums[i-1]);
        }
    }
    
    cout << "\nРазбиение найдено:\n";
    
    cout << "Подмножество 1: { ";
    int sum1 = 0;
    for (size_t i = 0; i < subset1.size(); i++) {
        cout << subset1[i];
        sum1 += subset1[i];
        if (i < subset1.size() - 1) cout << ", ";
    }
    cout << " } Сумма: " << sum1 << endl;
    
    cout << "Подмножество 2: { ";
    int sum2 = 0;
    for (size_t i = 0; i < subset2.size(); i++) {
        cout << subset2[i];
        sum2 += subset2[i];
        if (i < subset2.size() - 1) cout << ", ";
    }
    cout << " } Сумма: " << sum2 << endl;
}

//Задание 4
void task4_subsets() {
    cout << "Задание 4: Все подмассивы" << endl;
    
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    
    vector<string> arr(n);
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Все подмассивы: " << endl;
    int count = 0;
    
    for (int start = 0; start < n; start++) {
        for (int end = start; end < n; end++) {
            count++;
            cout << count << ". { ";
            for (int i = start; i <= end; i++) {
                cout << arr[i];
                if (i < end) cout << ", ";
            }
            cout << " }\n";
        }
    }
    
    cout << "Всего подмассивов: " << count << endl;
}

//Задание 5
void task5_bst() {
    cout << "Задание 5: Восстановление BST" << endl;
    cout << "Введите последовательность чисел (0 для окончания):" << endl;
    
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    vector<int> values;
    int x;
    while (cin >> x && x != 0) {
        values.push_back(x);
    }
    
    if (values.size() < 2) {
        cout << "Нужно хотя бы 2 числа\n";
        return;
    }
    
    cout << "\nСоздаем BST...\n";
    cout << "Затем меняем два случайных узла...\n";
    
    sort(values.begin(), values.end());
    
    if (values.size() >= 2) {
        swap(values[1], values[values.size() - 2]);
        cout << "Поменяли " << values[1] << " и " << values[values.size() - 2] << " местами\n";
    }
    
    cout << "Обход поврежденного дерева:" << endl;
    for (int val : values) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Восстанавливаем BST..." << endl;
    sort(values.begin(), values.end());
    
    cout << "Обход inorder восстановленного дерева:" << endl;
    for (int val : values) {
        cout << val << " ";
    }
    cout << endl;
}

//Задание 6
void task6_hash() {
    cout << "Задание 6: Хеш-таблица" << endl;
    
    cout << "Выберите часть:\n";
    cout << "1. Методы хеширования\n";
    cout << "2. Римские цифры\n";
    cout << "> ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        cout << "Методы хеширования ---\n";
        
        const int TABLE_SIZE = 7;
        vector<vector<pair<string, string>>> table(TABLE_SIZE);
        
        cout << "Введите количество пар ключ-значение: ";
        int n;
        cin >> n;
        
        cout << "Введите пары ключ-значение:\n";
        for (int i = 0; i < n; i++) {
            string key, value;
            cin >> key >> value;
            
            // Хеш-функция
            int hash = 0;
            for (size_t j = 0; j < key.length(); j++) {
                hash += key[j];
            }
            hash %= TABLE_SIZE;
            
            table[hash].push_back(make_pair(key, value));
            cout << key << " -> " << value << " (хеш: " << hash << ")\n";
        }
        
        cout << "Хеш-таблица (метод цепочек):\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            if (table[i].empty()) {
                cout << "пусто";
            } else {
                for (size_t j = 0; j < table[i].size(); j++) {
                    cout << table[i][j].first << ":" << table[i][j].second;
                    if (j < table[i].size() - 1) cout << " -> ";
                }
            }
            cout << endl;
        }
    }
    else if (choice == 2) {
        cout << "Римские цифры\n";
        
        cout << "Введите число (1-3999): ";
        int num;
        cin >> num;
        
        if (num < 1 || num > 3999) {
            cout << "Неверное число\n";
            return;
        }
        
        vector<pair<int, string>> values;
        values.push_back(make_pair(1000, "M"));
        values.push_back(make_pair(900, "CM"));
        values.push_back(make_pair(500, "D"));
        values.push_back(make_pair(400, "CD"));
        values.push_back(make_pair(100, "C"));
        values.push_back(make_pair(90, "XC"));
        values.push_back(make_pair(50, "L"));
        values.push_back(make_pair(40, "XL"));
        values.push_back(make_pair(10, "X"));
        values.push_back(make_pair(9, "IX"));
        values.push_back(make_pair(5, "V"));
        values.push_back(make_pair(4, "IV"));
        values.push_back(make_pair(1, "I"));
        
        string roman;
        int temp = num;
        for (size_t i = 0; i < values.size(); i++) {
            int val = values[i].first;
            string sym = values[i].second;
            
            while (temp >= val) {
                roman += sym;
                temp -= val;
            }
        }
        
        cout << "Римское число: " << roman << endl;
    }
}       

//Задание 7
void task7_lru() {
    cout << "Задание 7: LRU кэш" << endl;
    
    cout << "Введите емкость кэша: ";
    int capacity;
    cin >> capacity;
    
    if (capacity <= 0) {
        cout << "Неверная емкость\n";
        return;
    }
    
    struct Node {
        int key;
        string value;
        Node* prev;
        Node* next;
    };
    
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
    
    cout << "Команды:" << endl;
    cout << "  PUT key value\n";
    cout << "  GET key\n";
    cout << "  PRINT\n";
    cout << "  EXIT\n";
    
    string cmd;
    while (true) {
        cout << "\n> ";
        cin >> cmd;
        
        if (cmd == "PUT") {
            int key;
            string value;
            cin >> key >> value;
            
            Node* current = head;
            while (current) {
                if (current->key == key) {
                    current->value = value;
                    
                    if (current != head) {
                        if (current->prev) current->prev->next = current->next;
                        if (current->next) current->next->prev = current->prev;
                        if (current == tail) tail = current->prev;
                        
                        current->next = head;
                        current->prev = nullptr;
                        if (head) head->prev = current;
                        head = current;
                        if (!tail) tail = current;
                    }
                    
                    cout << "Обновлено " << key << ":" << value << endl;
                    break;
                }
                current = current->next;
            }
            
            if (!current) {
                // Новый элемент
                Node* newNode = new Node{key, value, nullptr, head};
                
                if (head) head->prev = newNode;
                head = newNode;
                if (!tail) tail = newNode;
                size++;
                
                cout << "Добавлено " << key << ":" << value << endl;
                
                // Удаляем самый старый, если переполнение
                if (size > capacity) {
                    Node* old = tail;
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                    else head = nullptr;
                    
                    cout << "Удален (LRU): " << old->key << ":" << old->value << endl;
                    delete old;
                    size--;
                }
            }
        }
        else if (cmd == "GET") {
            int key;
            cin >> key;
            
            Node* current = head;
            while (current) {
                if (current->key == key) {
                    cout << "Найдено: " << current->key << ":" << current->value << endl;
                    
                    // Перемещаем в начало
                    if (current != head) {
                        if (current->prev) current->prev->next = current->next;
                        if (current->next) current->next->prev = current->prev;
                        if (current == tail) tail = current->prev;
                        
                        current->next = head;
                        current->prev = nullptr;
                        if (head) head->prev = current;
                        head = current;
                        if (!tail) tail = current;
                    }
                    break;
                }
                current = current->next;
            }
            
            if (!current) {
                cout << "Не найдено: " << key << endl;
            }
        }
        else if (cmd == "PRINT") {
            cout << "LRU кэш: ";
            Node* current = head;
            while (current) {
                cout << current->key << ":" << current->value;
                if (current->next) cout << " -> ";
                current = current->next;
            }
            if (!head) cout << "пусто";
            cout << endl;
        }
        else if (cmd == "EXIT") {
            // Очистка
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            break;
        }
    }
}
