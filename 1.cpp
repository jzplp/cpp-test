#include <stdio.h>
#include <map>
#define MAXN 200005
using namespace std;

int arr[MAXN];
int prevArr[MAXN];
int nextArr[MAXN];
int n;
map<int, int> mp;

void init()
{
  int i, j, k;
  mp.clear();
  for (i = 1; i <= n; ++i)
  {
    if (!mp[arr[i]])
      prevArr[i] = 0;
    else
      prevArr[i] = mp[arr[i]];
    mp[arr[i]] = i;
  }
  mp.clear();
  for (i = n; i >= 1; --i)
  {
    if (!mp[arr[i]])
      nextArr[i] = n + 10;
    else
      nextArr[i] = mp[arr[i]];
    mp[arr[i]] = i;
  }
}

bool computed(int beg, int end)
{
  if (beg >= end)
    return true;
  int i;
  for (i = beg; i <= end; ++i)
  {
    if (prevArr[i] < beg && nextArr[i] > end)
      break;
  }
  // printf("-- %d %d %d\n", beg, end, i);
  if (i > end)
    return false;
  return computed(beg, i - 1) && computed(i + 1, end);
}

int main()
{
  int t, i, j;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
      scanf("%d", &arr[i]);
    init();
    if (computed(1, n))
      printf("non-boring\n");
    else
      printf("boring\n");
  }
  return 0;
}