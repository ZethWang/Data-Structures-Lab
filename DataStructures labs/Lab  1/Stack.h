// Stack.h  用于存放常量，函数的声明部分，类的声明部分
#ifndef HEAD_H
#define HEAD_H 1
template <class Elem>
class Stack
{
public:
  Stack(int size);
  ~Stack() { delete[] data; }
  bool IsEmpty() const;
  bool IsFull();
  Elem Pop();
  void Push(Elem x);
  inline Elem Top() { return data[top - 1]; }
  int Size() { return top; }

private:
  int maxsize;
  int top;
  Elem *data;
};
#endif