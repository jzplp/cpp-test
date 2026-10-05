#include <stdio.h>
#include <map>
#define MAXN 100005
using namespace std;

// beg 起始位置 end 终点的下一个位置
struct Stru
{
  int beg, end;
};

char s1[MAXN];
int n, d;
int s2[MAXN];
int s2len;
map<int, Stru> mp;
map<int, int> mp2;

void outMap()
{
  printf("mp:\n");
  for (auto ip = mp.begin(); ip != mp.end(); ++ip)
  {
    printf("i:%d  beg:%d  end:%d \n", ip->first, ip->second.beg, ip->second.end);
  }
  printf("mp2:\n");
  for (auto ip = mp2.begin(); ip != mp2.end(); ++ip)
  {
    printf("v:%d  i:%d \n", ip->first, ip->second);
  }
  putchar('\n');
}

void computed()
{
  int i, j, k;
  int c1;
  for (i = 0; i < n; ++i)
  {
    // printf("%d %d %d\n", i, s1[i], int(mp.count(s1[i])));
    if (mp.count(s1[i]))
    {
      if (s2len - mp[s1[i]].end >= n - i)
      {
        mp2[s2len - (n - i)] = s1[i];
        for (j = i + 1; j < n; ++j)
        {
          mp2[s2len - (n - j)] = s1[j];
        }
        return;
      }
      mp[s1[i]].end = mp[s1[i]].end + 1;
      for (c1 = s1[i] - 1; c1 >= 0; --c1)
      {
        if (mp.count(c1))
          mp.erase(c1);
      }
    }
    else
    {
      for (c1 = s1[i] + 1; c1 <= 9; ++c1)
      {
        if (mp.count(c1))
        {
          if (s2len - mp[c1].end >= n - i)
          {
            mp2[s2len - (n - i)] = s1[i];
            for (j = i + 1; j < n; ++j)
            {
              mp2[s2len - (n - j)] = s1[j];
            }
            return;
          }
          mp[s1[i]] = {mp[c1].end, mp[c1].end + 1};
          break;
        }
      }
      if (c1 > 9)
      {
        if (s2len >= n - i)
        {
          // printf("---- %d %d\n", n-i, s2len - (n - i));
          mp2[s2len - (n - i)] = s1[i];
          for (j = i + 1; j < n; ++j)
          {
            mp2[s2len - n - j] = s1[j];
          }
          return;
        }
        else
          mp[s1[i]] = {0, 1};
      }
      for (c1 = s1[i] - 1; c1 >= 0; --c1)
      {
        if (mp.count(c1))
          mp.erase(c1);
      }
    }
    // outMap();
  }
}

void outputRes()
{
  int i, j, k = 0;
  for (i = 9; i >= 0; --i)
  {
    if (!mp.count(i))
      continue;
    for (j = mp[i].beg; j < mp[i].end; ++j)
    {
      if (mp2.count(j))
        putchar(mp2[j] + '0');
      else
        putchar(i + '0');
    }
    k = j;
  }
  if (k < s2len - 1)
  {
    for (; k < s2len; ++k)
    {
      if (mp2.count(k))
        putchar(mp2[k] + '0');
    }
  }
  putchar('\n');
}

int main()
{
  int i;
  while (scanf("%d %d", &n, &d) >= 2 && n > 0 && d > 0)
  {
    scanf("%s", s1);
    s2len = n - d;
    for (i = 0; i < n; ++i)
      s1[i] = s1[i] - '0';
    mp.clear();
    mp2.clear();
    computed();
    // outMap();
    outputRes();
  }
  return 0;
}