/*
01背包问题
*/

#include <iostream>
#include <vector>
#include "Stack.h"
using namespace std;
void Input(int &N, int &V, int *&BagV, int *&BagValue);
void KnapSack(int N, int V, int *BagV, int *BagValue); // 若只考虑刚好装满背包
void Output(Stack<int> &st, int count, int N, int *BagV, int *BagValue);
void Output(int N, int V, int *BagV);
int Max(int a, int b);
void Advance_KnapSack(const int N, const int V, int *BagV, int *BagValue);
int main()
{
  int N, V;
  int *BagV, *BagValue; // 每个物品的体积和价值
  Input(N, V, BagV, BagValue);
  KnapSack(N, V, BagV, BagValue); // 当每件物品无价值之分时
  cout << "--------------------------------------------------";
  Advance_KnapSack(N, V, BagV, BagValue); // 若有价值，利用栈最坏时间复杂度可达O(2^n),故采用动态规划解决
  free(BagV), free(BagValue);             // 不要忘了free掉
}

void Input(int &N, int &V, int *&BagV, int *&BagValue)
{
  cout << "请输入物品个数和背包体积\n";
  cin >> N >> V;
  BagV = new int[N];
  BagValue = new int[N];
  cout << "请输入每个物品的体积和价值\n";
  for (int i = 0; i < N; i++)
  {
    cin >> BagV[i] >> BagValue[i];
  }
  cout << "输入完成\n";
}

void KnapSack(int N, int V, int *BagV, int *BagValue)
{
  cout << "无价值,仅考虑体积:\n";
  int V_sum = V; // 实时记录体积和
  int count = 0; // 记录解的个数
  Stack<int> st(N);
  int i = 1, k = 0;
  while (i < N)
  {
    if (V_sum >= BagV[k]) // 先放入一个到栈中,要判断是否符合体积
    {
      st.Push(k);
      V_sum -= BagV[k];
      break;
    }
    else
    {
      i++, k++;
    }; // i记录下一个目标，k记录第一个放入的
  }
  if (i == N)
  {
    cout << "No answer";
    return;
  }
  while (1) // 这里类似于二叉树利用堆栈实现先序遍历
  {
    while (V_sum > 0 && i < N)
    {
      if (V_sum >= BagV[i])
      {
        V_sum -= BagV[i];
        st.Push(i);
      }
      if (V_sum == 0)
      {
        count++;
        break;
      }
      i++;
    }
    if (V_sum == 0)
      Output(st, count, N, BagV, BagValue); // 找到合适的一组解并输出
    if (!st.IsEmpty())
    {
      if (st.Size() == 1) // 排除i==N-1的情况,以及判断是否筛选完成
      {
        i = st.Pop() + 1;
        V_sum += BagV[i - 1];
        if (i == N)
          break;
      }
      else if (i == N - 1)
      {
        V_sum += BagV[st.Pop()];
        i = st.Top() + 1;
        V_sum += BagV[st.Pop()];
      }
      else
      {
        i = st.Pop() + 1;
        V_sum += BagV[i - 1];
      }
    }
  }
  if (!count)
    cout << "No anwser";
  else
    cout << "总方案数:" << count << endl;
}

//时间、空间复杂度都是O(n)
void Output(Stack<int> &st, int count, int N, int *BagV, int *BagValue)
{

  int flag = 0;      
  Stack<int> rev(N); // 因为栈的先入后出，要用另外一个栈来翻转输出顺序
  while (!st.IsEmpty())
    rev.Push(st.Pop());
  cout << "第" << count << "组解:(";
  while (!rev.IsEmpty())
  {
    if (flag)
      cout << ",";
    cout << BagV[rev.Top()];
    st.Push(rev.Pop());
    flag = 1;
  }
  cout << ")\n";
}

// O(n^2)的时间复杂度
int dp[100][100] = {0};
void Advance_KnapSack(const int N, const int V, int *BagV, int *BagValue)
{
  for (int i = 1; i <= N; i++) // 只装入0件物品,价值一定为0
  {
    for (int j = 1; j <= V; j++) // 背包体积为0,价值一定为0
    {
      if (j < BagV[i - 1])
        dp[i][j] = dp[i - 1][j]; // 当前物品不能装入
      else                       // 可以装入
      {
        dp[i][j] = Max(dp[i - 1][j - BagV[i - 1]] + BagValue[i - 1], dp[i - 1][j]);
      }
    }
  }
  Output(N, V, BagV);
}
void Output(int N, int V, int *BagV) // O(n)的时间复杂度
{
  int n = N, v = V; // 保存N,V值
  int flag = 0;
  int i = N;
  Stack<int> st(N);
  while (i > 0)
  {
    if (dp[i][V] != dp[i - 1][V])
    {
      V = V - BagV[i - 1];
      st.Push(i);
    }
    i--;
  }
  cout << "\n同时考虑体积和价值的最优或近似最优解为:\n{";
  while (!st.IsEmpty())
  {
    if (flag)
      cout << ",";
    cout << BagV[st.Pop() - 1];
    flag = 1;
  }
  cout << "}\n";
  cout << "其总价值为:" << dp[n][v];
}

int Max(int a, int b)
{
  return a >= b ? a : b;
}
