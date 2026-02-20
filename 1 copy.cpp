#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#define MAXLEN 10000
using namespace std;

int n, m, s, t;
vector<int> graph[20];
// 0 空白 1 石头 2 机器人
int vertices[20];
int mp[40000][16];

int stepsMin[MAXLEN];
int stepsMinLen;
int steps[MAXLEN];
int stepsLen;

void copyStepMin()
{
  for (int i = 0; i < stepsLen; ++i)
    stepsMin[i] = steps[i];
  stepsMinLen = stepsLen;
}

void printVertices()
{
  for (int i = 0; i < n; ++i)
    printf("%d ", vertices[i]);
  putchar('\n');
}

bool hasMap()
{
  int num = 0;
  for (int i = 0; i < n; ++i)
  {
    if (vertices[i] == 1)
      num = num * 2 + 1;
    else
      num = num * 2;
  }

  if (mp[num][s] && mp[num][s] <= stepsLen)
    return true;
  mp[num][s] = stepsLen;
  return false;
}

void loop(int preStep)
{
  if (stepsMinLen != 0 && stepsLen >= stepsMinLen)
    return;
  if (s == t)
  {
    copyStepMin();
    return;
  }
  if (hasMap())
    return;
  int preBeg = preStep % 20, preEnd = preStep / 20;
  int i, jp, k, j;
  for (i = 0; i < n; ++i)
  {
    if (vertices[i] == 0)
      continue;

    for (jp = 0; jp < graph[i].size(); ++jp)
    {
      j = graph[i][jp];
      if (vertices[j])
        continue;
      // 走回去
      if (i == preEnd && j == preBeg)
        continue;
      vertices[j] = vertices[i];
      vertices[i] = 0;
      k = j * 20 + i;
      if (i == s)
        s = j;
      steps[stepsLen] = k;
      stepsLen++;
      loop(k);

      // 恢复原状
      stepsLen--;
      if (j == s)
        s = i;
      vertices[i] = vertices[j];
      vertices[j] = 0;
    }
  }
}

int main()
{
  int T, i, j, k = 0, a, b;
  scanf("%d", &T);
  while (++k <= T)
  {
    for (i = 0; i < 20; ++i)
      graph[i].clear();
    memset(vertices, 0, sizeof(vertices));
    memset(stepsMin, 0, sizeof(stepsMin));
    memset(steps, 0, sizeof(steps));
    stepsMinLen = 0;
    stepsLen = 0;
    memset(mp, 0, sizeof(mp));
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s = s - 1;
    t = t - 1;
    for (i = 0; i < m; ++i)
    {
      scanf("%d", &a);
      vertices[a - 1] = 1;
    }
    vertices[s] = 2;
    for (i = 1; i < n; ++i)
    {
      scanf("%d %d", &a, &b);
      a = a - 1;
      b = b - 1;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    if (s == t)
    {
      printf("Case %d: 0\n\n", k);
      continue;
    }
    loop(-1);
    printf("Case %d: %d\n", k, (stepsMinLen == 0 ? -1 : stepsMinLen));
    if (stepsMinLen != MAXLEN)
    {
      for (i = 0; i < stepsMinLen; ++i)
        printf("%d %d\n", stepsMin[i] % 20 + 1, stepsMin[i] / 20 + 1);
    }
    putchar('\n');
  }

  return 0;
}
