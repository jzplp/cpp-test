#include <stdio.h>
#include <list>
#define MAXN 10005

using namespace std;

int n, m;
list<int> edgeArr[MAXN];
int colorArr[MAXN];
int degree;

void init()
{
  int i;
  for (i = 0; i < MAXN; ++i)
  {
    edgeArr[i].clear();
    colorArr[i] = 0;
  }
}

void setDegree()
{
  int i, j;
  degree = 0;
  for (i = 1; i <= n; ++i)
    if (edgeArr[i].size() > degree)
      degree = edgeArr[i].size();
  if (degree % 2 == 0)
    ++degree;
}

bool dfs(int a, list<int>::const_iterator ai)
{
  if (ai == edgeArr[a].end())
    return true;
  if (colorArr[*ai])
  {
    if (colorArr[*ai] == colorArr[a])
      return false;
    return true;
  }

  for (int i = 1; i <= degree; ++i)
  {
    if(i == colorArr[a]) continue;
    colorArr[*ai] = i;
    if (dfs(v))
      continue;
    colorArr[v] = 0;
  }
  return false;
}
return false;
}

int main()
{
  int t = 0, i;
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
    setDegree();
    colorArr[1] = 1;
    dfs(1, 1);
  }
  return 0;
}