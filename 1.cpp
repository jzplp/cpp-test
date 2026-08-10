#include <stdio.h>
#include <string.h>
#define MAXN 100005
#define MAXM 200005

int arrInput[2 * MAXM]; // 所有门的入口
int n, m;
int arrm[MAXM];
int arrnOnei;    // 入口值开始变为1的编号
int outM;        // 出口门编号
int zeroV, oneV; // 全0和全1时的值

void init()
{
  int i, j;
  // 找到出口元素
  memset(arrm, 0, sizeof(arrm));
  for (i = 1; i <= 2 * m; ++i)
    if (arrInput[i] > 0)
      arrm[arrInput[i]] = 1;
  for (i = 1; i <= m; ++i)
  {
    if (arrm[i] == 0)
      break;
  }
  outM = i;
}

int getDeepValue(int i)
{
  if (i < 0)
  {
    if (-i <= arrnOnei)
      return 1;
    return 0;
  }
  if (getDeepValue(arrInput[2 * i]) && getDeepValue(arrInput[2 * i - 1]))
    return 0;
  return 1;
}

void getInitValue()
{
  int i, j, k;
  // 计算入口值全0
  arrnOnei = 0;
  zeroV = getDeepValue(outM);
  arrnOnei = n+1;
  oneV = getDeepValue(outM);
}

int computed(int beg, int end)
{
  int mid = (beg + end) / 2;
  // printf("--- %d %d %d\n", beg, mid, end);
  if (beg >= mid || beg == end)
    return end;
  int v;
  arrnOnei = mid;
  v = getDeepValue(outM);
  // printf("--- %d\n", v);
  if (v == zeroV)
    beg = mid;
  else
    end = mid;
  return computed(beg, end);
}

int main()
{
  int d, i, j;
  scanf("%d", &d);
  while (d--)
  {
    scanf("%d %d", &n, &m);
    for (i = 1; i <= 2 * m; ++i)
      scanf("%d", &arrInput[i]);
    init();
    // printf("%d\n", outM);
    getInitValue();
     // printf("%d %d \n", zeroV, oneV);
    if (zeroV == oneV)
    {
      for (i = 1; i <= n; ++i)
        printf("0");
      putchar('\n');
      continue;
    }
    j = computed(0, n+1);
    // printf("%d\n", j);
    for (i = 1; i <= n; ++i)
    {
      if (i < j)
        printf("1");
      else if (i > j)
        printf("0");
      else
        printf("x");
    }
    putchar('\n');
  }
  return 0;
}