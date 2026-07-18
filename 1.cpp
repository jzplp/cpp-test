#include <stdio.h>
#define MAXN 1000005

int n, l;
int arr[MAXN];
int sumArr[MAXN];

void init()
{
  int i, j;
  sumArr[0] = arr[0];
  for (i = 0; i < n; ++i)
    sumArr[i] = sumArr[i - 1] + arr[i];
  for (i = 0; i < n; ++i)
    printf("%d ", sumArr[i]);
  putchar('\n');
}

int main()
{
  int t, i, j, k;
  char c;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &l);
    getchar();
    for (i = 0; i < n; ++i)
    {
      scanf("%c", &c);
      arr[i] = c - '0';
    }
    init();
  }
  return 0;
}