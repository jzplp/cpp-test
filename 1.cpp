#include <stdio.h>
#define MAXN 100005

int arr[MAXN];
int arrFlag[MAXN];
int n;

bool computed()
{
  int i;
  int value = 0;
  for (i = n - 1; i >= 0; --i)
  {
    if (value > 0)
    {
      value -= arr[i];
      arrFlag[i] = -1;
    }
    else
    {
      value += arr[i];
      arrFlag[i] = 1;
    }
  }
  return value == 0;
}

int main()
{
  int i;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 0; i < n; ++i)
      scanf("%d", &arr[i]);
    if (!computed())
    {
      printf("No\n");
    }
    else
    {
      printf("Yes\n");
      for (i = 0; i < n; ++i)
      {
        if (i != 0)
          putchar(' ');
        printf("%d", arrFlag[i]);
      }
      putchar('\n');
    }
  }
  return 0;
}