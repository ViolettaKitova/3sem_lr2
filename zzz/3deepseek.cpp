#include <iostream>
using namespace std;

// Функция слияния двух отсортированных частей
void sortMerge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int leftArr[n1], rightArr[n2];
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Основная функция сортировки
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        sortMerge(arr, left, mid, right);
    }
}

// Простая и понятная функция canSplit
void canSplit(int arr[], int n, int k, int targetSum, bool& result) {
    // Создаем массив для отметки использованных элементов
    bool used[n];
    for (int i = 0; i < n; i++) {
        used[i] = false;
    }
    
    // Пытаемся создать k подмножеств
    int subsetsCreated = 0;
    
    for (int subset = 0; subset < k; subset++) {
        int currentSum = 0;
        bool subsetComplete = false;
        
        // Пытаемся набрать текущее подмножество
        while (!subsetComplete) {
            bool foundElement = false;
            
            // Ищем подходящий элемент для добавления в подмножество
            for (int i = 0; i < n; i++) {
                if (!used[i] && currentSum + arr[i] <= targetSum) {
                    // Если нашли подходящий элемент - используем его
                    used[i] = true;
                    currentSum += arr[i];
                    foundElement = true;
                    
                    // Если достигли нужной суммы - подмножество готово
                    if (currentSum == targetSum) {
                        subsetComplete = true;
                        subsetsCreated++;
                        break;
                    }
                }
            }
            
            // Если не нашли подходящий элемент - выходим
            if (!foundElement) {
                break;
            }
        }
    }
    
    // Если создали все k подмножеств - успех
    result = (subsetsCreated == k);
}

void printPartition(int arr[], int n, int k, int targetSum) {
    cout << "Найдено разбиение на " << k << " подмножеств с суммой " << targetSum << endl;
    
    bool used[n];
    for (int i = 0; i < n; i++) {
        used[i] = false;
    }
    
    // Для каждого подмножества находим элементы
    for (int subset = 1; subset <= k; subset++) {
        cout << "Подмножество " << subset << ": {";
        int currentSum = 0;
        bool firstElement = true;
        
        // Собираем элементы для текущего подмножества
        for (int i = 0; i < n; i++) {
            if (!used[i] && currentSum + arr[i] <= targetSum) {
                if (!firstElement) {
                    cout << ", ";
                }
                cout << arr[i];
                used[i] = true;
                currentSum += arr[i];
                firstElement = false;
                
                if (currentSum == targetSum) {
                    break;
                }
            }
        }
        cout << "}" << endl;
    }
}

void splitToSet(int arr[], int n) {
    // Сначала сортируем массив по убыванию
    mergeSort(arr, 0, n - 1);
    
    // Переворачиваем для сортировки по убыванию
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
    
    int maxEl = arr[0];
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    if (sum - maxEl < maxEl) {
cout << "Ошибка! Нельзя разбить на подмножества" << endl;
        return;
    } 
    else {
        // Ищем возможные k
        for (int k = 2; k <= n; k++) {
            if (sum % k == 0) {
                int targetSum = sum / k;
                if (maxEl <= targetSum) {
                    bool found = false;
                    canSplit(arr, n, k, targetSum, found);
                    if (found) {
                        printPartition(arr, n, k, targetSum);
                        return;
                    }
                }
            }
        }
        cout << "Не удалось найти разбиение" << endl;
    }
}

// Простой пример
int main() {
    int n;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    int arr[n];
    cout << "Введите " << n << " элементов: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Исходное множество: ";
    for (int i = 0; i < n; i++) 
        cout << arr[i] << " ";
    cout << endl;
    
    splitToSet(arr, n);
    
    return 0;
}
