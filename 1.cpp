#include <stdio.h>
#include <string.h>
#include <list>
#define MAXN 1030

using namespace std;

int group[MAXN][MAXN];
int used[MAXN];
int usedt[MAXN];
int n;
list<int> lst;

int history[MAXN * MAXN][2];
int hisn;

bool judge()
{
  int i;
  for (i = 2; i <= n; ++i)
    if (!used[i])
      return false;
  return true;
}

void beat(list<int>::iterator &it, list<int>::iterator &it2)
{
  if (group[*it][*it2])
    used[*it2] = 1;
  else
    used[*it] = 1;
  history[hisn][0] = *it;
  history[hisn][1] = *it2;
  ++hisn;
  it = lst.erase(it);
  // 避免删除it2后，it也不存在了
  if(it == it2) {
    it2 = lst.erase(it2);
    it = it2;
  } else {
    it2 = lst.erase(it2);
  }
}

void computed()
{
  list<int>::iterator it3;
  bool flag;
  // 第一步消灭所有直接消灭的黑色
  for (auto it = lst.begin(); it != lst.end();)
  {
    if (group[1][*it])
    {
      ++it;
      continue;
    }
    flag = false;
    for (auto it2 = lst.begin(); it2 != lst.end();)
    {
      if (group[*it][*it2] || it == it2)
      {
        ++it2;
        continue;
      }
      beat(it, it2);
      flag = true;
      break;
    }
    if (!flag)
      ++it;
  }

  // 第二步 1和另一个
  for (auto it = lst.begin(); it != lst.end();)
  {
    if (!group[1][*it])
    {
      ++it;
      continue;
    }
    used[*it] = 1;
    history[hisn][0] = 1;
    history[hisn][1] = *it;
    ++hisn;
    it = lst.erase(it);
    break;
  }

  // 第三步 黑黑对决
  for (auto it = lst.begin(); it != lst.end();)
  {
    if (group[1][*it])
    {
      ++it;
      continue;
    }
    flag = false;
    for (auto it2 = it; it2 != lst.end();)
    {
      if (group[1][*it2] || it == it2)
      {
        ++it2;
        continue;
      }
      beat(it, it2);
      break;
    }
    if (!flag)
      ++it;
  }

  // 第四步 剩下混战
  for (auto it = lst.begin(); it != lst.end();)
  {
    it3 = it;
    if (++it != lst.end())
    {
      beat(it3, it);
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
      lst.clear();
      for (i = 2; i <= n; ++i)
        if (!used[i])
          lst.push_back(i);
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