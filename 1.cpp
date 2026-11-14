#include <stdio.h>
#include <string.h>
#include <list>
#define MAXN 10005

using namespace std;

int n, m;
list<int> edgeArr[MAXN];
int colorArr[MAXN];
int colorUse[MAXN];

// 获取度，注意实际染色的值可能小于度，但是这里还是要按照题目要求输出度的值或+1
int getK()
{
  int i;
  int k = 0;
  for (i = 1; i <= n; ++i)
  {
    if (k < edgeArr[i].size())
      k = edgeArr[i].size();
  }
  if (k % 2 == 0)
    ++k;
  return k;
}

void init()
{
  int i;
  for (i = 0; i < MAXN; ++i)
  {
    edgeArr[i].clear();
    colorArr[i] = 0;
  }
}

// 只需要看a的临近点中已经染色的点，选一个没有重复的点即可，未染色的点无需考虑
void setNode(int a)
{
  memset(colorUse, 0, sizeof(colorUse));
  for (auto ip = edgeArr[a].begin(); ip != edgeArr[a].end(); ++ip)
  {
    if (colorArr[*ip])
      colorUse[colorArr[*ip]] = 1;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!colorUse[i])
    {
      colorArr[a] = i;
      return;
    }
  }
}

void dfs(int a)
{
  if (colorArr[a])
    return;
  setNode(a);
  for (auto ip = edgeArr[a].begin(); ip != edgeArr[a].end(); ++ip)
  {
    dfs(*ip);
  }
}

int main()
{
  int i;
  int a, b;
  while (scanf("%d %d", &n, &m) > 0 && n > 0)
  {
    init();
    for (i = 0; i < m; ++i)
    {
      scanf("%d %d", &a, &b);
      edgeArr[a].push_back(b);
      edgeArr[b].push_back(a);
    }
    dfs(1);
    printf("%d\n", getK());
    for (i = 1; i <= n; ++i)
    {
      printf("%d\n", colorArr[i]);
    }
    printf("\n");
  }
  return 0;
}