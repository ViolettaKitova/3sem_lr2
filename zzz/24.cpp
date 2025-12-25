#include <iostream>
#include <string>
using namespace std;

struct Array{
  string elements[100];
  int size;
};

void printAllSubjects(Array arr){
  int n = arr.size;
  int total = 1 << n; // 2^n
  cout << "Все подмножества массива: ";
  for (int i = 0; i < n; i++){
    cout << arr.elements[i];
    if (i < n - 1) cout << ", ";
  }
  cout << endl;
  
  for (int i = 0; i < total; i++){
    cout << "{";
    bool first = true;
    for (int j = 0; j < n; j++){
      if (i & (1 << j)){
        if (!first) cout << ", ";
        cout << arr.elements[j];
        first = false;
      }
    }
    cout << "}" << endl;
  }
}

int main(){
  Array arr;
  
  cout << "Введите количество элементов: ";
  cin >> arr.size;
  
  cout << "Введите элементы:" << endl;
  for (int i = 0; i < arr.size; i++) {
    cout << "Элемент " << i + 1 << ": ";
    cin >> arr.elements[i];
  }
  
  printAllSubjects(arr);
  return 0;
}
