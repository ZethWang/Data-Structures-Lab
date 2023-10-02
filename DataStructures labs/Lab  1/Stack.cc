
#include <iostream>
#include "Stack.h"
using namespace std;
template <class Elem>
Stack<Elem>::Stack(int size) : maxsize(size), top(0) // 列表初始化
{
  data = new Elem[maxsize];
  if (data == NULL)
  {
    cout << "分配内存失败";
    exit(0);
  }
}

template <class Elem>
bool Stack<Elem>::IsEmpty() const
{
  if (top == 0)
    return true;
  else
    return false;
}

template <class Elem>
bool Stack<Elem>::IsFull()
{
  if (top == maxsize)
    return true;
  else
    return false;
}

template <class Elem>
Elem Stack<Elem>::Pop()
{
  if (!IsEmpty())
    return data[--top];
  else
    cout << "栈已空";
}

template <class Elem>
void Stack<Elem>::Push(Elem x)
{
  if (!IsFull())
    data[top++] = x;
  else
    cout << "栈已满";
}

template class Stack<int>;