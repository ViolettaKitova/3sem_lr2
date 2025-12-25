//не доделано

#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right){ //слияние
  int n1 = mid - left + 1; //левая часть
  int n2 = right - mid; //правая
  int leftArr[n1], rightArr [n2];
  
  for (int i = 0; i<n1; i++){
    leftArr[i] = arr[left + i];
  }
  for (int j = 0; j<n2; j++){
    rightArr[j] = arr[mid + 1 + j];
  }
  int i = 0; 
  int j = 0;
  int k = left;
  while (i < n1 && j < n2){
    if (leftArr[i] <= rightArr[j]){
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }
  while (i < n1){
    arr[k] = leftArr;
    i++;
    k++;
  }
  while (j < n2){
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int left, int right){
  if (left < right){
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid, right + 1);
    merge(arr, left, mid, right);
  }
}

bool canSplit(int arr[], int n, int k, int targetSum){ 
  bool used[n];
  for (int i = 0; i<n; i++){
    used[i] = false;
  }
  int subsetsCreated = 0;
  for (int subset = 0; subset < k; subset++){
    int currentSum = 0;
    bool subsetComplete = false;
    while (!subsetComplete){
      bool foundElement = false;
      for (int i = 0; i < n; i++){
        if (!used[i] && currentSum + arr[i] <= targetSum){
          used[i] = true;
          currentSum += arr[i];
          foundElement = true;
          if (currentSum == targetSum){
            subsetComplete = true;
            subsetsCreated++;
            break;
          }
        }
      }
      if (!foundElement){
        break;
      }
    }
  }
  result = (subsetsCreated == k);
}





void splitToSet(int arr[], int n){
  mergeSort(arr, arr + n);
  int maxEl = arr[n-1];
  int sum = 0;
  
  for (int i = 0; i<n; i++){
    sum += arr[i];
  }
  if (sum - maxEl < maxEl){
    cout << "Ошибка! Нельзя разбить на подмножества" << endl;
    return;
  } else {
    for (int k = 2; k<n; k++){ //к - возможное колво подмножеств
      if (sum % k == 0){
        int targetSum = sum/k;
        if (maxEl <= targetSum){
        
        }
      }
    }
  }
}
