#include <iostream>
#include <string>
using namespace std;

struct Stack{
  int elements[100];
  int top;
};

void push(Stack& st, int el){
  if (st.top >= 99){  
    cout << "Ошибка! Нельзя добавить элемент" << endl;
  } else {
    st.top++;  
    st.elements[st.top] = el;
  }
}

int pop(Stack& st){
  if (st.top < 0){  
    cout << "Ошибка! Нельзя удалить элемент" << endl;
    return 0; 
  } else {
    int value = st.elements[st.top]; //удаляем верхний эл
    st.top--;
    return value;
  }
}

bool isEmpty(Stack& st){
  return st.top<0;
}

int getPriority(char op){ //приоритет операций
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

string reversePolishNote(string str){
  Stack st;
  st.top = -1;
  string result = "";
  
  if (str.length() > 0) {
    char lastChar = str[str.length() - 1];
    if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') {
      cout << "Ошибка! Последний элемент не может быть знаком операции" << endl;
      return "";
    }
  }
  
  for (int i = 0; i < str.length(); i++){
    char c = str[i];
    if (c >= '0' && c<='9'){
      while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
        result += str[i];
        i++;
      }
      i--;
      result += ' ';
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/'){
      while (!isEmpty(st) && getPriority(st.elements[st.top]) >= getPriority(c)) {
        result += st.elements[st.top];
        result += ' ';
        pop(st);
      }
      push(st, c);
    }
  }
  while (!isEmpty(st)) {
    result += pop(st);
    result += ' ';
  }
  return result;
}

int calculateRPN(string polish){ //вычисление обратной польской записи
  Stack nums;
  nums.top = -1;
  
  for (int i=0; i < polish.length(); i++){
    char c = polish[i]; //текущий символ
    
    if (c >= '0' && c <= '9') {
      int num = 0;
      while (i < polish.length() && polish[i] >= '0' && polish[i] <= '9') {
        num = num * 10 + (polish[i] - '0');
        i++;
      }
      i--; 
      push(nums, num);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/'){
      int num2 = pop(nums);
      int num1 = pop(nums);
      if (c == '+') push(nums, (num1 + num2));
      else if (c == '-') push(nums, (num1 - num2));
      else if (c == '*') push(nums, (num1 * num2));
      else if (c == '/') push(nums, (num1 / num2));
    }
  }
  return pop(nums);
}

int main(){
  string str;
  cout << "Введите выражение: ";
  cin >> str;
  string polish = reversePolishNote(str);
  if (polish == "") {  
    return 0;
  }
  cout << "Выражение в польской записи: " << polish << endl;
  int result = calculateRPN(polish);
  cout << "Результат: " << result << endl;
  return 0;
}
