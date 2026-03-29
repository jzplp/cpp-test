#include <stdio.h>
#include <string.h>

int arr[35][35];
int n, k;

struct Group
{
  int x, y;
  int num;
};

// 下标从1开始
Group groups[30] = {};
int glen;

bool computed(int index);

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
        printf("%3d", groups[arr[i][j]].num);
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
bool computeRect(int index, int r)
{
  int x = groups[index].x, y = groups[index].y, num = groups[index].num;
  int i, j;
  int c = num / r;
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
      setRect(xmin, ymin, xmax, ymax, index);
      if (computed(index + 1))
        return true;
      setRect(xmin, ymin, xmax, ymax, 0);
      arr[x][y] = index;
    }
  }
  return false;
}

bool computed(int index)
{
  if(index >= glen) return true;
  int x = groups[index].x, y = groups[index].y, num = groups[index].num;
  int a, b, c, d;
  for (a = 1; a <= num; ++a)
  {
    if (num % a)
      continue;
    if (computeRect(index, a))
      return true;
  }
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
    memset(groups, 0, sizeof(groups));
    memset(arr, 0, sizeof(arr));
    glen = 0;
    kt = 1;
    for (i = 0; i < n; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        c = getchar();
        if (c != '.')
        {
          groups[kt] = {i, j, c - '0'};
          arr[i][j] = kt;
          ++kt;
        }
      }
    }
    glen = kt;
    if (!computed(1))
    {
      printf("xxx\n");
      continue;
    }
    output();
  }
  return 0;
}
