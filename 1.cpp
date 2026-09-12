#include <stdio.h>
#define MAXN 1000005

int arrFloor[MAXN];
int arrCeiling[MAXN];
int n;

int main()
{
  int z, i;
  scanf("%d", &z);
  while (z--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrFloor[i]);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrCeiling[i]);
  }

  return 0;
}