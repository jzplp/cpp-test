#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_DIFF 10e-8

/*
  点type的分类
  1 原点
  2 在左侧线上的点
  3 在右侧线上的点
  4 在左侧点
  5 在右侧点
*/

struct Item
{
  int x, y;
  int t;
  double angle;
  int type;
};

// 原始数据
Item arrOrigin[1010];
int n;

Item arr[1010];

int compare(const void *left, const void *right)
{
  return ((const Item *)left)->angle - ((const Item *)right)->angle;
}

bool getEqualAngle(double angle1, double angle2) {
  return abs(fmod(angle1 - angle2 + 2 * M_PI, 2 * M_PI)) < MIN_DIFF;
}


// 预处理，变为以a点做起点
void preI(int a)
{
  int i, j = 0;
  int x = arrOrigin[a].x, y = arrOrigin[a].y;
  for (i = 0; i < n; ++i)
  {
    if (i == a)
      continue;
    // 以第a个点为零点转换坐标系
    arr[j].x = arrOrigin[i].x - x;
    arr[j].y = arrOrigin[i].y - y;
    arr[j].t = arrOrigin[i].t;
    // 求atan2角度，最小角度0
    arr[j].angle = fmod(atan2(arr[j].y, arr[j].x) + 2 * M_PI, 2 * M_PI);
    ++j;
  }
  // 从小到大排序
  qsort(arr, n - 1, sizeof(Item), compare);
  // 输出排序结果
  /*
  for (i = 0; i < n-1; ++i)
    printf("%d %d %lf\n", arr[i].x, arr[i].y, arr[i].angle);
  */
}

int getNextIndex(int i)
{
  return i % (n - 1);
}

bool getState(int i, int j) {
  double anglei = arr[i].angle + M_PI, anglej = arr[j].angle;
  if(getEqualAngle(anglei, anglej)) return false;
  if(anglei > anglej) {
    if(anglei - anglej < M_PI) return true;
    return false;
  }
  if(anglei + 2 * M_PI - anglej < M_PI) return true;
  return false; 
} 

int getRes(int topWhite, int topBlack, int bottomWhite, int bottomBlack, int line)
{
  int res1 = topWhite + bottomBlack;
  int res2 = topBlack + bottomWhite;
  return (res1 > res2 ? res1 : res2) + 1 + line;
}

// 计算
int computedI()
{
  int i, j, i1, i2, j1, j2 = 0, ii, jj, preAngle = 0, t;
  int topWhite = 0, topBlack = 0, bottomWhite = 0, bottomBlack = 0, lineLeftWhite = 0, lineLeftBlack = 0, lineRightWhite = 0, lineRightBlack = 0;
  int maxRes = 0, res;
  // 计算起始个数
  // 计算0-180度的数量
  for (i = 0; i < n - 1; ++i)
  {
    if (abs(arr[i].angle) < MIN_DIFF)
    {
      if (arr[i].t)
        ++lineLeftWhite;
      else
        ++lineLeftBlack;
      continue;
    }
    if (abs(arr[i].angle - M_PI) < MIN_DIFF || arr[i].angle > M_PI)
      break;
    if (arr[i].t)
      ++topWhite;
    else
      ++topBlack;
  }

  i1 = lineLeftWhite + lineLeftBlack + 1;
  i2 = i;
  // 计算180-360度的数量
  for (; i < n - 1; ++i)
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
  maxRes = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
  // 准备工作结束，开始遍历
  i = i1;
  j = j1 + 1;
  while (i < n - 1)
  {
    if (abs(fmod(preAngle - arr[i].angle + 2 * M_PI, 2 * M_PI) - M_PI) < MIN_DIFF)
    {
      t = lineLeftWhite;
      lineLeftWhite = lineRightWhite;
      lineRightWhite = t;
      t = lineRightBlack;
      lineRightBlack = lineLeftBlack;
      lineLeftBlack = t;
      t = topWhite;
      topWhite = bottomWhite;
      bottomWhite = t;
      t = topBlack;
      topBlack = bottomBlack;
      bottomBlack = t;
      preAngle = arr[i].angle;

      res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
      if (res > maxRes)
        maxRes = res;
      if (i > j)
        break;
      t = i;
      i = j;
      j = t;
    }
    else if (fmod(preAngle - arr[i].angle + 2 * M_PI, 2 * M_PI) < M_PI)
    {
      bottomWhite += lineLeftWhite;
      bottomBlack += lineLeftBlack;
      topWhite += lineRightWhite;
      topBlack += lineRightBlack;
      lineLeftWhite = 0;
      lineLeftBlack = 0;
      lineRightWhite = 0;
      lineRightBlack = 0;
      ii = getNextIndex(i + 1);
      while (getEqualAngle(arr[ii].angle, arr[i].angle))
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
      while (getState(i, jj))
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
      preAngle = arr[i].angle;
      res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
      if (res > maxRes)
        maxRes = res;
      if (ii < i)
        break;
      i = ii;
      j = jj;
    }
    else if (fmod(preAngle - arr[i].angle + 2 * M_PI, 2 * M_PI) > M_PI)
    {
      t = topWhite;
      topWhite = bottomWhite;
      bottomWhite = t;
      t = topBlack;
      topBlack = bottomBlack;
      bottomBlack = t;
      topWhite += lineLeftWhite;
      topBlack += lineLeftBlack;
      bottomBlack += lineRightBlack;
      bottomWhite += lineRightWhite;

      lineLeftWhite = 0;
      lineLeftBlack = 0;
      lineRightWhite = 0;
      lineRightBlack = 0;
      ii = getNextIndex(i + 1);
      while (getEqualAngle(arr[ii].angle, arr[i].angle))
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
      preAngle = arr[i].angle;
      res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
      if (res > maxRes)
        maxRes = res;
      if (ii < i)
        break;
      i = ii;
      j = (i + (n - 1) + 1) % (n - 1);
    }
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