#include <stdio.h>
#define MAXMN 1005

int arr[MAXMN][MAXMN];
int m, n;

void outputArr()
{
  int i, j;
  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
      printf("%d", arr[i][j]);
    putchar('\n');
  }
  putchar('\n');
}

int main()
{
  int t;
  int i, j;
  char c;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        scanf("%c", &c);
        if (c == '.')
          arr[i][j] = 1;
        else
          arr[i][j] = 0;
      }
    }
    outputArr();
  }

  return 0;
}