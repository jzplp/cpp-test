#include <stdio.h>
#include <map>
#define MAXN 100005
using namespace std;

int s1[MAXN];
int n, d;
int s2[MAXN];

// beg 起始位置 end 终点的下一个位置
struct Stru
{
  int beg, end;
};

void computed(int s2len, map<int, Stru> &mp)
{
  int i, j, k;
  int c1;
  bool flag;
  for (i = 0; i < n; ++i)
  {
    if (mp.count(s1[i]))
    {
      if (s2len - mp[s1[i]].end <= n - i)
        continue;
      mp[s1[i]].end = mp[s1[i]].end + 1;
      for (c1 = s1[i] - 1; c1 >= 0; --c1)
      {
        if (mp.count(c1))
          mp.erase(c1);
      }
    }
    else
    {
      flag = true;
      if (s1[i] == 9)
        mp[9] = {0, 1};
      else
      {
        for (c1 = s1[i] + 1; c1 <= 9; ++c1)
        {
          if (mp.count(c1))
          {
            if (s2len - mp[c1].end <= n - i)
            {
              flag = false;
              break;
            }
            mp[s1[i]] = {mp[c1].end, mp[c1].end + 1};
            break;
          }
        }
        if (c1 > 9)
          mp[s1[i]] = {0, 1};
      }
      if (flag)
        for (c1 = s1[i] - 1; c1 >= 0; --c1)
        {
          if (mp.count(c1))
            mp.erase(c1);
        }
    }
  }
}

int main()
{
  int i, s2len;
  while (scanf("%d %d", &n, &d) >= 2 && n > 0 && d > 0)
  {
    scanf("%s", s1);
    s2len = n - d;
    map<int, Stru> mp;
    for (i = 0; i < n; ++i)
      s1[i] = s1[i] - '0';
    computed(s2len, mp);
    putchar('\n');
  }
  return 0;
}