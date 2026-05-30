#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_DIFF 10e-8

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

int getNextIndex(int i)
{
  return (i % n) == 0 ? 1 : i % n;
}

int getRes(int topWhite, int topBlack, int bottomWhite, int bottomBlack, int line)
{
  int res1 = topWhite + bottomBlack + line;
  int res2 = topBlack + bottomWhite + line;
  return (res1 > res2 ? res1 : res2) + 1;
}

// 计算
int computedI()
{
  int i, j, i1, i2, j1, j2 = 0, ii, jj;
  int topWhite = 0, topBlack = 0, bottomWhite = 0, bottomBlack = 0, lineLeftWhite = 0, lineLeftBlack = 0, lineRightWhite = 0, lineRightBlack = 0;
  int maxRes = 0, res;
  // 计算起始个数
  // 计算0-180度的数量
  for (i = 1; i < n; ++i)
  {
    if (arr[i].angle < MIN_DIFF)
    {
      if (arr[i].t)
        ++lineLeftWhite;
      else
        ++lineLeftBlack;
      continue;
    }
    if (abs(arr[i].angle - M_PI) < MIN_DIFF)
      break;
    if (arr[i].t)
      ++topWhite;
    else
      ++topBlack;
  }
  i1 = lineLeftWhite + lineLeftBlack + 1;
  i2 = i;
  // 计算180-360度的数量
  for (; i < n; ++i)
  {
    if (abs(arr[i].angle - M_PI) < MIN_DIFF)
    {
      if (arr[i].t)
        ++lineRightWhite;
      else
        ++lineRightBlack;
      j1 = i;
      continue;
    }
    if (abs(arr[i].angle - 2 * M_PI) < MIN_DIFF)
    {
      if (!j2)
        j2 = j;
      if (arr[i].t)
        ++lineLeftWhite;
      else
        ++lineLeftBlack;
      continue;
    }
    if (arr[i].t)
      ++bottomWhite;
    else
      ++bottomBlack;
  }
  if (lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack > 0)
  {
    maxRes = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
  }
  // 准备工作结束，开始遍历
  i = i1;
  j = j1;
  while (i < j2)
  {
    ii = getNextIndex(i + 1);
    bottomWhite += lineLeftWhite;
    bottomBlack += lineLeftBlack;
    topWhite += lineRightWhite;
    topBlack += lineRightBlack;
    lineLeftWhite = 0;
    lineLeftBlack = 0;
    lineRightWhite = 0;
    lineRightBlack = 0;
    while (abs(arr[ii].angle - arr[i].angle) < MIN_DIFF)
    {
      if (arr[ii].t)
      {
        --topWhite;
        ++lineLeftWhite;
      }
      else
      {
        --topBlack;
        ++lineLeftBlack;
      }
      ii = getNextIndex(ii + 1);
    }
    jj = getNextIndex(j + 1);
    while (fmod(arr[jj].angle + 3 * M_PI - arr[i].angle, 2 * M_PI) > MIN_DIFF)
    {
      if (arr[jj].t)
      {
        --bottomWhite;
        ++topWhite;
      }
      else
      {
        --bottomBlack;
        ++topBlack;
      }
      jj = getNextIndex(jj + 1);
    }
    while (abs(fmod(arr[jj].angle + 3 * M_PI - arr[i].angle, 2 * M_PI)) < MIN_DIFF)
    {
      if (arr[jj].t)
      {
        --bottomWhite;
        ++lineRightWhite;
      }
      else
      {
        --bottomBlack;
        ++lineRightBlack;
      }
      jj = getNextIndex(jj + 1);
    }
    res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
    if (res > maxRes)
      maxRes = res;
  }
  return maxRes;
}

int computed()
{
  int i, j, k;
  int maxRes = 0, res;
  for (i = 0; i < n; ++i)
  {
    preI(i);
    res = computedI();
    if (res > maxRes)
      maxRes = res;
  }
  return maxRes;
}

int main()
{
  int i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 0; i < n; ++i)
      scanf("%d %d %d", &arrOrigin[i].x, &arrOrigin[i].y, &arrOrigin[i].t);
    printf("%d\n", computed());
  }
  return 0;
}