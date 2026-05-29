#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Item
{
  int x, y;
  int t;
  double angle;
};
// 原始数据
Item arrOrigin[1010];
int n;

Item arr[1010];

int compare(const void *left, const void *right)
{
  return ((const Item *)left)->angle - ((const Item *)right)->angle;
}

// 预处理，变为以a点做起点
void preI(int a)
{
  int i;
  int x = arrOrigin[a].x, y = arrOrigin[a].y;
  for (i = 0; i < n; ++i)
  {
    // 以第a个点为零点转换坐标系
    arr[i].x = arrOrigin[i].x - x;
    arr[i].y = arrOrigin[i].y - y;
    arr[i].t = arrOrigin[i].t;
    // 求atan2角度，最小角度0
    arr[i].angle = fmod(atan2(arr[i].y, arr[i].x) + 2 * M_PI, 2 * M_PI);
  }
  // 从小到大排序
  qsort(arr, n, sizeof(Item), compare);
  // 输出排序结果
  /*
  for (i = 0; i < n; ++i)
    printf("%d %d %lf\n", arr[i].x, arr[i].y, arr[i].angle);
  */
}

// 计算
void computedI()
{
  int i, j, i1, j1, topWhite = 0, topBlack = 0, bottomWhite = 0, bottomBlack = 0, lineLeft = 0, lineRight = 0;
  // 计算起始个数
  // 计算0-180度的数量
  for (i = 1; i < n; ++i)
  {
    if (arr[i].angle - M_PI < 10e-8)
      break;
    if (arr[i].t)
      ++topWhite;
    else
      ++topBlack;
  }
  // 计算180-360度的数量
  for (; i < n; ++i)
  {
    if (arr[i].angle - M_PI < 10e-8)
      continue;
    if (arr[i].t)
      ++bottomWhite;
    else
      ++bottomBlack;
  }
}

void computed()
{
  int i, j, k;
  for (i = 0; i < n; ++i)
  {
    preI(i);
    computedI();
  }
}

int main()
{
  int i, j;
  printf("%lf --- \n", atan2(0, 0));
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 0; i < n; ++i)
      scanf("%d %d %d", &arrOrigin[i].x, &arrOrigin[i].y, &arrOrigin[i].t);
  }
  computed();

  return 0;
}