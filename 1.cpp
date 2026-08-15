#include <stdio.h>
#include <map>
#define MAXN 200005
using namespace std;

int arr[MAXN];
int last[MAXN];
int n;
map<int, int> mp;

void init()
{
  int i, j, k;
  mp.clear();
  for (i = 1; i <= n; ++i)
  {
    if (!mp[arr[i]])
      last[i] = 0;
    else
      last[i] = mp[arr[i]];
    mp[arr[i]] = i;
    // printf("%d ", last[i]);
  }
  // putchar('\n');
}

bool computed(int beg, int end)
{
  if (beg >= end)
    return true;
  int i;
  mp.clear();
  for (i = end; i >= beg; --i)
  {
    // printf("%d %d %d\n", i, arr[i], mp[arr[i]]);
    if (mp[arr[i]])
      continue;
    // printf("%d %d %d\n", i, arr[i], mp[arr[i]]);
    mp[arr[i]] = 1;
    if (last[i] < beg)
      break;
  }
  // printf("-- %d %d %d\n", beg, end, i);
  if (i < beg)
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