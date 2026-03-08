#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;

int n;
int arr[10000];
int maxn, sumn;
int num;
set<int> se;


bool judge(int t)
{
  if (t == n)
    return true;
  if (arr[t] == 0 || arr[t] == num)
    return judge(t + 1);
  int a1, a2;
  int i;
  for (i = t + 1; i < n; ++i)
  {
    if (arr[i] == 0 || arr[i] + arr[t] > num)
      continue;
    a1 = arr[t];
    a2 = arr[i];
    if (arr[i] + arr[t] == num)
    {
      arr[i] = 0;
      arr[t] = 0;
      if(judge(t + 1)) return true;
      else return false;
    } else if(arr[i] + arr[t] < num) {
      arr[i] += arr[t];
      arr[t] = 0;
      if(judge(t + 1)) return true;
    }
    arr[t] = a1;
    arr[i] = a2;
  }
  return false;
}

// 拿到可能的木棍长度
void getNums(int t)
{
  if(t == n) return;
  int i, j, k;
  if(arr[t] == 0) return getNums(t + 1);
  // 不处理
  getNums(t + 1);
  for(i = t + 1; i < n; ++i) {
    j = arr[t] + arr[i];
    if(j > sumn / 2) continue;
    if(!se.count(j) && !(sumn % j)) se.insert(j);
    k = arr[i];
    arr[i] = j;
    getNums(t + 1);
    arr[i] = k;
  }
}

int compute()
{
  int i, j, k;
  for (auto ip = se.begin(); ip != se.end(); ++ip)
  {
    num = *ip;
    if (judge(0))
      return *ip;
  }
  return sumn;
}

int main()
{
  int i;
  while (scanf("%d", &n) == 1 && n != 0)
  {
    se.clear();
    maxn = 0;
    sumn = 0;
    for (i = 0; i < n; ++i)
    {
      scanf("%d", &arr[i]);
      sumn += arr[i];
      if (arr[i] > maxn)
        maxn = arr[i];
    }
    if(!(sumn % maxn)) se.insert(maxn);
    getNums(0);
    // printf("%d\n", compute());
  }
  return 0;
}