#include <stdio.h>
#include <string.h>

int arr[35][35];
int n, k;
// 下标从1开始
int groups[30];
int groupsFind[30];

bool judge() {}

bool computeRect(int x, int y, int r) {
  int a, b, c, d;
  int groupIndex = arr[x][y];
  int c = groups[groupIndex] / a;

  int xmin = x / a;

  for(a = 0)
}


bool computed(int x, int y) {
  if(y == n) {
    return computed(x + 1, y);
  }
  if (x == n) {
    return judge();
  }
  if(arr[x][y] == 0) {
    return computed(x, y + 1);
  }
  int groupIndex = arr[x][y];
  if(groupsFind[groupIndex]) {
    return computed(x, y + 1);
  }
  int a, b,c, d;
  for(a = 1; a <= groups[groupIndex]; ++a) {
    if(groups[groupIndex] % a) continue;

  }


}


int main()
{
  int i, j, kt;
  char c;
  while (scanf("%d %d", &n, &k) == 2 && n > 0 & k > 0)
  {
    memset(groupsFind, 0, sizeof(groupsFind));
    kt = 1;
    for (i = 0; i < n; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        c = getchar();
        if (c == '.')
          arr[i][j] = 0;
        else
        {
          groups[kt] = c - '0';
          arr[i][j] = kt;
          ++kt;
        }
      }
    }
    computed(0, 0);
  }

  return 0;
}
