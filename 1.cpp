#include <stdio.h>
#include <string.h>

#define MAXN 200005

int arr[MAXN];
int n;
int leftArr[MAXN], rightArr[MAXN];

void computed()
{
  int i, left;
  memset(leftArr, 0, sizeof(leftArr));
  memset(rightArr, 0, sizeof(rightArr));
  leftArr[0] = 1;
  left = 0;
  for (i = 1; i < n; ++i)
  {
    if (arr[i] > arr[i - 1])
    {
      ++leftArr[left];
      if (i == n - 1)
        rightArr[i] = leftArr[left];
    }
    else
    {
      rightArr[i - 1] = leftArr[left];
      left = i;
      leftArr[i] = 1;
      if (i == n - 1)
        rightArr[i] = 1;
    }
  }
  for (i = 1; i < n; ++i)
  {
    if (leftArr[i])
      continue;
    leftArr[i] = leftArr[i - 1] - 1;
  }
  for (i = n - 1; i >= 0; --i)
  {
    if (rightArr[i])
      continue;
    rightArr[i] = rightArr[i + 1] - 1;
  }

  // output
  for (i = 0; i < n; ++i)
    printf("%2d ", arr[i]);
  putchar('\n');
  for (i = 0; i < n; ++i)
    printf("%2d ", leftArr[i]);
  putchar('\n');
  for (i = 0; i < n; ++i)
    printf("%2d ", rightArr[i]);
  putchar('\n');
}

int main()
{
  int t, i;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arr[i]);
    computed();
  }
  return 0;
}