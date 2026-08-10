#include <stdio.h>
#include <string.h>
#define MAXN 100005

int arrn[MAXN];
int s, n;
int arrs[MAXN];
int steps[MAXN];

void computed()
{
  int wnum, step;
  int i, j, k;
  int num2 = 0;
  for (wnum = 0;; ++wnum)
  {
    memset(arrs, 0, sizeof(arrs));
    memset(steps, 0, sizeof(steps));
    // 计算初始值
    num2 = 0;
    for (i = (wnum - 2) * s + 1; i <= (wnum - 1) * s; ++i)
    {
      if (i < 0)
        continue;
      if (i >= n)
        return;
      arrs[arrn[i]] += 1;
      if (arrs[arrn[i]] == 2)
        ++num2;
    }
    for (step = 1; step <= s; ++step)
    {
      i = step + (wnum - 1) * s;
      if (i - 1 >= n)
        return;
      // 减去前一个，增加下一个
      if (arrs[arrn[i - 1]] == 2)
        --num2;
      if (i + s - 1 < n)
      {
        ++arrs[arrn[i + s - 1]];
        if (arrs[arrn[i + s - 1]] == 2)
          ++num2;
      }
      if (num2 > 0)
        steps[step] = 1;
    }
  }
}

int main()
{
  int t, i, j;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &s, &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrn[i]);
    computed();
    j = 0;
    for (i = 1; i <= s; ++i)
    {
      if (steps[i] == 0)
        ++j;
    }
    printf("%d\n", j);
  }
  return 0;
}