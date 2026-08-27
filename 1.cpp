#include <stdio.h>
#define MAXN 1030

int group[MAXN][MAXN];
int n;

int main()
{
  int i, j;
  while (scanf("%d", &n) > 0)
  {
    for (i = 1; i <= n; ++i)
    {
      for (j = 1; j <= n; ++j)
        scanf("%d", &group[i][j]);
    }
  }
  return 0;
}