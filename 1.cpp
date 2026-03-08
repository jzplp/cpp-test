#include <stdio.h>
#include <stdlib.h>

int n;
int arr[1000];
int arr2[1000];
int max, sum;
int num;

void copy()
{
  for (int i = 0; i < n; ++i)
    arr2[i] = arr[i];
}

void output()
{
  for (int i = 0; i < n; ++i)
  {
    printf("%d ", arr[i]);
  }
  putchar('\n');
}

bool judge(int t, int j)
{
  if (t == n)
    return false;
  if (arr2[t] == 0 || arr2[t] == num)
    return true;
  int a1, a2;
  int i;
  for (i = j; i < n; ++i)
  {
    if (arr2[i] == 0 || arr2[i] + arr2[t] > num)
      continue;
    if (arr2[i] + arr2[t] == num)
    {
      arr2[i] = 0;
      arr2[t] = 0;
      return true;
    }
    a1 = arr2[t];
    a2 = arr2[i];
    if (arr2[i] + arr2[t] < num)
    {
      arr2[t] += arr2[i];
      arr2[i] = 0;
      if (judge(t, i + 1))
        return true;
    }
    arr2[t] = a1;
    arr2[i] = a2;
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
    copy();
    for (j = 0; j < n; ++j)
    {
      if (!judge(j, j + 1))
        continue;
    }
    return i;
  }
  return sum;
}

int compare(const void *a, const void *b)
{
  return *(int *)b - *(int *)a;
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
    qsort(arr, n, sizeof(int), compare);
    printf("%d\n", compute());
  }
  return 0;
}