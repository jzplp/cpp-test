#include <stdio.h>
#define MAXN 305

int arr[MAXN];
int arrIndex[MAXN];
int n;

int main()
{
  int i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 0; i < n; ++i)
    {
      // 直接变为从乱排列到 1,2...,n的排列的问题
      scanf("%d", &arrIndex[i]);
      arr[arrIndex[i]] = i;
    }


  }
  return 0;
}