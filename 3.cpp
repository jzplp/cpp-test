#include <stdio.h>
#include <string.h>
#include <math.h>

int n, k;
int arr[30][30];

struct Group
{
  int x, y;
  int num;
  int xmin;
  int ymin;
  int xmax;
  int ymax;
};

// 下标从0开始
Group groups[30] = {};
int glen;

bool computed(int index);

// 判断单个矩形是否符合要求
bool judgeRect(int index)
{
  int i, j;
  int leftx, rightx, lefty, righty;
  int xmin = groups[index].xmin;
  int ymin = groups[index].ymin;
  int xmax = groups[index].xmax;
  int ymax = groups[index].ymax;
  for (i = 1; i < index; ++i)
  {
    leftx = abs(xmin + xmax - groups[i].xmin - groups[i].xmax);
    rightx = xmax - xmin + groups[i].xmax - groups[i].xmin;
    lefty = abs(ymin + ymax - groups[i].ymin - groups[i].ymax);
    righty = ymax - ymin + groups[i].ymax - groups[i].ymin;
    if (leftx <= rightx && lefty <= righty)
      return false;
  }
  return true;
}

// 对与队长坐标（x,y）x方向长度为r的进行计算
bool computeRect(int index, int r)
{
  int x = groups[index].x, y = groups[index].y, num = groups[index].num;
  int i, j;
  int c = num / r;
  int xmin, xmax, ymin, ymax;
  if (x - r + 1 < 0)
    i = -(x - r + 1);
  else
    i = 0;
  for (; i < r; ++i)
  {
    xmax = x + i;
    xmin = xmax - r + 1;
    if (xmax >= n)
      break;
    if (y - c + 1 < 0)
      j = -(y - c + 1);
    else
      j = 0;
    for (; j < c; ++j)
    {
      ymax = y + j;
      ymin = ymax - c + 1;
      if (ymax >= n)
        break;
      groups[index].xmin = xmin;
      groups[index].ymin = ymin;
      groups[index].xmax = xmax;
      groups[index].ymax = ymax;
      if (!judgeRect(index))
        continue;
      if (computed(index + 1))
        return true;
    }
  }
  return false;
}

bool computed(int index)
{
  if (index >= k)
    return true;
  int num = groups[index].num;
  int a;
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
  int i, j, x, y;
  // 先把每个队铺到数组中
  for (i = 0; i < k; ++i)
  {
    for (x = groups[i].xmin; x <= groups[i].xmax; ++x)
    {
      for (y = groups[i].ymin; y <= groups[i].ymax; ++y)
      {
        arr[x][y] = i;
      }
    }
  }
  // 然后分配字母
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
    kt = 0;
    for (i = 0; i < n; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        c = getchar();
        if (c != '.')
        {
          groups[kt] = {i, j, c - '0', 0, 0, 0, 0};
          ++kt;
        }
      }
    }
    if (!computed(0))
    {
      printf("xxx\n");
      continue;
    }
    output();
  }
  return 0;
}
