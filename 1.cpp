#include <stdio.h>
#include <string.h>

int arr[35][35];
int n, k;
// 下标从1开始
int groups[30];
int groupsFind[30];

bool computed(int x, int y);

void outArr1()
{
  int i, j;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      if (!arr[i][j])
        printf("  0");
      else
        printf("%3d", groups[arr[i][j]]);
    }
    putchar('\n');
  }
}
void outArr2()
{
  int i, j;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
      printf("%3d", arr[i][j]);
    putchar('\n');
  }
}

bool judge()
{
  return true;
}

// 判断单个矩形是否符合要求
bool judgeRect(int x, int y, int xmin, int ymin, int xmax, int ymax)
{
  int i, j;
  for (i = xmin; i <= xmax; ++i)
  {
    for (j = ymin; j <= ymax; ++j)
    {
      if (i == x && j == y)
        continue;
      if (arr[i][j])
        return false;
    }
  }
  return true;
}

// 对矩形设置值
void setRect(int xmin, int ymin, int xmax, int ymax, int v)
{
  int i, j;
  for (i = xmin; i <= xmax; ++i)
    for (j = ymin; j <= ymax; ++j)
      arr[i][j] = v;
}

// 对与队长坐标（x,y）x方向长度为r的进行计算
bool computeRect(int x, int y, int r)
{
  // printf("-- %d %d %d\n", x, y, r);
  int i, j;
  int groupIndex = arr[x][y];
  int c = groups[groupIndex] / r;
  int xmin, xmax, ymin, ymax;
  for (i = 0; i < r; ++i)
  {
    xmax = x + i;
    xmin = xmax - r + 1;
    if (xmax >= n)
      break;
    if (xmin < 0)
      continue;
    for (j = 0; j < c; ++j)
    {
      ymax = y + j;
      ymin = ymax - c + 1;
      if (ymax >= n)
        break;
      if (ymin < 0)
        continue;
      if (!judgeRect(x, y, xmin, ymin, xmax, ymax))
        continue;
      // printf("%d %d %d %d\n", xmin, xmax, ymin, ymax);
      setRect(xmin, ymin, xmax, ymax, groupIndex);
      if (computed(x, y + 1))
        return true;
      setRect(xmin, ymin, xmax, ymax, 0);
      arr[x][y] = groupIndex;
    }
  }
  return false;
}

bool computed(int x, int y)
{
  // outArr();
  if (y == n)
    return computed(x + 1, 0);
  if (x == n)
    return true;
  if (arr[x][y] == 0)
    return computed(x, y + 1);
  int groupIndex = arr[x][y];
  if (groupsFind[groupIndex])
    return computed(x, y + 1);
  int a, b, c, d;
  groupsFind[groupIndex] = 1;
  for (a = 1; a <= groups[groupIndex]; ++a)
  {
    if (groups[groupIndex] % a)
      continue;
    if (computeRect(x, y, a))
      return true;
  }
  groupsFind[groupIndex] = 0;
  return false;
}

void output()
{
  int i, j;
  int groupMap[30] = {};
  int gi = 0;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      if (!groupMap[arr[i][j]])
        groupMap[arr[i][j]] = ++gi;

      printf("%c", groupMap[arr[i][j]] + 'A' - 1);
    }
    putchar('\n');
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
    // outArr2();
    // outArr1();
    if (!computed(0, 0))
    {
      printf("xxx\n");
      continue;
    }
    // outArr();
    output();
  }
  return 0;
}
