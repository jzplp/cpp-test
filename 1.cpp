#include <stdio.h>
#include <string.h>
#define MAXN 1030

int group[MAXN][MAXN];
int used[MAXN];
int usedt[MAXN];
int n;
int history[MAXN * MAXN][2];
int hisn;

void print()
{
  int i;
  printf("used\n");
  for (i = 1; i <= n; ++i)
  {
    printf("%d ", used[i]);
  }
  printf("\n usedt\n");
  for (i = 1; i <= n; ++i)
  {
    printf("%d ", usedt[i]);
  }
  putchar('\n');
}

bool judge()
{
  int i;
  for (i = 2; i <= n; ++i)
    if (!used[i])
      return false;
  return true;
}

void beat(int i, int j)
{
  if (group[i][j])
    used[j] = 1;
  else
    used[i] = 1;
  usedt[i] = 1;
  usedt[j] = 1;
  history[hisn][0] = i;
  history[hisn][1] = j;
  ++hisn;
}

void computed()
{
  int i, j, k;
  // 第一步消灭所有直接消灭的黑色
  for (i = 2; i <= n; ++i)
  {
    if (used[i] || usedt[i] || group[1][i])
      continue;
    for (j = 2; j <= n; ++j)
    {
      if (used[j] || usedt[j] || group[i][j] || i == j)
        continue;
      beat(i, j);
      break;
    }
  }
  // 第二步 1和另一个
  for (i = 2; i <= n; ++i)
  {
    if (used[i] || usedt[i] || !group[1][i])
      continue;
    beat(1, i);
    break;
  }
  // 第三步 黑黑对决
  for (i = 2; i <= n; ++i)
  {
    if (used[i] || usedt[i] || group[1][i])
      continue;
    for (j = i + 1; j <= n; ++j)
    {
      if (used[j] || usedt[j] || group[1][j])
        continue;
      beat(i, j);
      break;
    }
  }
  // 第四步 剩下混战
  for (i = 2; i <= n; ++i)
  {
    if (used[i] || usedt[i])
      continue;
    for (j = i + 1; j <= n; ++j)
    {
      if (used[j] || usedt[j])
        continue;
      beat(i, j);
      break;
    }
  }
}

int main()
{
  int i, j;
  char c;
  while (scanf("%d", &n) > 0)
  {
    for (i = 1; i <= n; ++i)
    {
      getchar();
      for (j = 1; j <= n; ++j)
      {
        scanf("%c", &c);
        group[i][j] = c - '0';
      }
    }
    memset(used, 0, sizeof(used));
    memset(history, 0, sizeof(history));
    hisn = 0;
    while (1)
    {
      memset(usedt, 0, sizeof(usedt));
      computed();
      if (judge())
        break;
    }
    for (i = 0; i < hisn; ++i)
    {
      printf("%d %d\n", history[i][0], history[i][1]);
    }
    // putchar('\n');
  }
  return 0;
}