#include <stdio.h>

int n;
int arr[10000];
int max, sum;
int num;

bool judge(int t)
{
  if (t == n)
    return true;
  if (arr[t] == 0 || arr[t] == num)
    return judge(t + 1);
  int a1, a2;
  int i;
  for (i = t + 1; i < n; ++i)
  {
    if (arr[i] == 0 || arr[i] + arr[t] > num)
      continue;
    a1 = arr[t];
    a2 = arr[i];
    if (arr[i] + arr[t] == num)
    {
      arr[i] = 0;
      arr[t] = 0;
      if(judge(t + 1)) return true;
    } else if(arr[i] + arr[t] < num) {
      arr[i] += arr[t];
      arr[t] = 0;
      if(judge(t + 1)) return true;
    }
    arr[t] = a1;
    arr[i] = a2;
  }
  return false;
}

int compute()
{
  int i, j, k;
  for (i = max; i < sum / 2 + 1; ++i)
  {
    // 筛选出能整除的i
    if (sum % i)
      continue;
    num = i;
    if (judge(0))
      return i;
  }
  return sum;
}

int main()
{
  int i;
  while (scanf("%d", &n) == 1 && n != 0)
  {
    max = 0;
    sum = 0;
    for (i = 0; i < n; ++i)
    {
      scanf("%d", &arr[i]);
      sum += arr[i];
      if (arr[i] > max)
        max = arr[i];
    }
    printf("%d\n", compute());
  }
  return 0;
}