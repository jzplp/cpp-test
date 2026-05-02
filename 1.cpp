#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;

struct Rect
{
  int xl, yl, xr, yr;
  int num;
  int x, y;
};
Rect arr[5500];

int compareX(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  if (l->xr != r->xr)
  {
    return l->xr - r->xr;
  }
  return l->xl - r->xl;
}

bool computedX()
{
  int i;
  int curX = 0;
  qsort(arr, n, sizeof(Rect), compareX);
  for(i = 0 ; i < n; ++i) {
    printf("%d %d\n", arr[i].xl, arr[i].xr);
  }
  for (i = 0; i < n; ++i)
  {
    if (arr[i].xr < curX)
    {
      // printf("-- %d %d\n", arr[i].xr, curX);
      return false;
    }
    if (curX < arr[i].xl)
    {
      curX = arr[i].xl;
      arr[i].x = arr[i].xl;
    }
    else
    {
      arr[i].x = curX;
    }
    printf("---- %d\n", arr[i].x);
    ++curX;
  }
  return true;
}

int compareY(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  if (l->yr != r->yr)
  {
    return l->yr - r->yr;
  }
  return l->yl - r->yl;
}

bool computedY()
{
  int i, j;
  int curY = 0;
  qsort(arr, n, sizeof(Rect), compareY);
  for(i = 0 ; i < n; ++i) {
    printf("%d %d\n", arr[i].yl, arr[i].yr);
  }
  for (i = 0; i < n; ++i)
  {
    if (arr[i].yr < curY)
      return false;
    if (curY < arr[i].yl)
    {
      curY = arr[i].yl;
      arr[i].y = arr[i].yl;
    }
    else
    {
      arr[i].y = curY;
    }
    printf("---- %d\n", arr[i].y);
    ++curY;
  }
  return true;
}

int compareIndex(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  return l->num - r->num;
}

int main()
{
  int xl, yl, xr, yr, i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    memset(arr, 0, sizeof(arr));
    for (i = 0; i < n; ++i)
    {
      scanf("%d %d %d %d", &xl, &yl, &xr, &yr);
      arr[i] = {xl - 1, yl - 1, xr - 1, yr - 1, i, -1, -1};
    }
    if (!computedX() || !computedY())
    {
      printf("IMPOSSIBLE\n");
      continue;
    }
    qsort(arr, n, sizeof(Rect), compareIndex);
    for (i = 0; i < n; ++i)
    {
      printf("%d %d\n", arr[i].x + 1, arr[i].y + 1);
    }
  }

  return 0;
}