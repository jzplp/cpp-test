#include <stdio.h>
#define MAXN 1000005

int arrFloor[MAXN];   // 地板
int arrCeiling[MAXN]; // 天花板
int arrValue[MAXN];   // 当前水位
int n;

void computedFront()
{
  int i;
  arrValue[0] = arrCeiling[0];
  for (i = 1; i < n; ++i)
  {
    if (arrFloor[i] >= arrValue[i - 1])
    {
      arrValue[i] = arrFloor[i];
      continue;
    }
    if (arrCeiling[i] <= arrValue[i - 1])
    {
      arrValue[i] = arrCeiling[i];
      continue;
    }
    arrValue[i] = arrValue[i - 1];
  }
}

void computedBack()
{
  int i;
  for (i = n - 2; i >= 0; --i)
  {
    if (arrValue[i] <= arrValue[i + 1])
      continue;
    if (arrValue[i] >= arrCeiling[i + 1])
    {
      arrValue[i] = arrFloor[i] > arrValue[i + 1] ? arrFloor[i] : arrValue[i + 1];
      continue;
    }
    if (arrValue[i] > arrValue[i + 1])
    {
      if (arrValue[i] == arrFloor[i])
        continue;
      arrValue[i] = arrValue[i + 1];
    }
  }
}

int main()
{
  int z, i;
  long long sum;
  scanf("%d", &z);
  while (z--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrFloor[i]);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrCeiling[i]);
    computedFront();
    computedBack();
    sum = 0;
    for (i = 0; i < n; ++i)
    {
      sum += arrValue[i] - arrFloor[i];
    }
    printf("%lld\n", sum);
  }

  return 0;
}