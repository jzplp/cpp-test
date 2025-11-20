#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <set>

using namespace std;

#define MAXRESTI 10000

// 不能选的数字
unsigned long long restrictArr[MAXRESTI + 50];
// 最小的组合
set<unsigned long long> seMin;
// 当前组合
set<unsigned long long> seTemp;

// 求最大公约数 辗转相除法
unsigned long long gcd(unsigned long long x, unsigned long long y)
{
  unsigned long long t;
  while (x % y)
  {
    t = x % y;
    x = y;
    y = t;
  }
  return y;
}

// 计算 a/b - 1/egyp 的结果分数
void getSubFrac(unsigned long long a, unsigned long long b, unsigned long long egyp, unsigned long long &at, unsigned long long &bt)
{
  unsigned long long gcdV = gcd(b, egyp);
  unsigned long long tb, te;
  tb = b / gcdV;
  te = egyp / gcdV;
  at = a * te - tb;
  bt = b * te;
  if (at <= 0)
    return;
  /*
  at = a * egyp - b;
  bt = b * egyp;
  */
  unsigned long long gcdVt = gcd(bt, at);
  at = at / gcdVt;
  bt = bt / gcdVt;
}

// seTemp与当前seMin比较
bool compareSet()
{
  if (seMin.empty())
    return true;
  if (seMin.size() > seTemp.size())
    return true;
  if (seMin.size() < seTemp.size())
    return false;
  for (auto rm = seMin.rbegin(), rt = seTemp.rbegin(); rm != seMin.rend(); ++rm, ++rt)
  {
    if (*rm > *rt)
      return true;
    if (*rm < *rt)
      return false;
  }
  return false;
}

// 判断我们能否使用这个数字
bool judgeNum(unsigned long long i)
{
  if (i > MAXRESTI)
  {
    if (seTemp.count(i))
      return false;
    return true;
  }
  if (restrictArr[i] || seTemp.count(i))
    return false;
  return true;
}

// 分数 a/b, time还剩的循环次数, prev上次循环到的数字+1
void computed(unsigned long long a, unsigned long long b, unsigned long long time, unsigned long long prev)
{
  if (time < 0)
    return;
  if (time == 0)
  {
    /*
    if (a == 1 && judgeNum(b))
    {
      while(1);
      seTemp.insert(b);
      if (compareSet())
        seMin = seTemp;
      seTemp.erase(b);
    }
    */
    return;
  }
  // 获取比这个分数小的埃及分数中最大的那个 必须+1不然会出现负数
  unsigned long long minNum = b / a + 1;
  unsigned long long i = minNum > prev ? minNum : prev;
  unsigned long long at, bt;
  for (;; ++i)
  {
    // 比当前答案的最高数字更大
    if (!seMin.empty() && (i > *(seMin.rbegin())))
      return;
    // 循环最大值
    if (a * i > b * (time + 1))
      return;
    if (!judgeNum(i))
      continue;
    getSubFrac(a, b, i, at, bt);
    // 找到了
    seTemp.insert(i);
    if (at == 1)
    {
      if (!judgeNum(bt))
      {
        computed(at, bt, time - 1, i + 1);
        seTemp.erase(i);
        continue;
      }
      seTemp.insert(bt);
      if (compareSet())
        seMin = seTemp;
      seTemp.erase(bt);
      computed(at, bt, time - 1, i + 1);
    }
    else
      computed(at, bt, time - 1, i + 1);
    seTemp.erase(i);
  }
}

int main()
{
  unsigned long long a, b, step, k, t, ti = 0, i;
  scanf("%llu", &t);
  while (++ti <= t)
  {
    scanf("%llu %llu %llu", &a, &b, &k);
    memset(restrictArr, 0, sizeof(restrictArr));
    seMin.clear();
    seTemp.clear();
    while (k-- != 0)
    {
      scanf("%llu", &i);
      restrictArr[i] = 1;
    }
    for (step = 1;; ++step)
    {
      seMin.clear();
      seTemp.clear();
      computed(a, b, step, 2);
      if (!seMin.empty())
        break;
    }
    printf("Case %llu: %llu/%llu=", ti, a, b);
    for (auto it = seMin.begin(); it != seMin.end(); ++it)
    {
      if (it != seMin.begin())
        putchar('+');
      printf("1/%llu", *it);
    }
    putchar('\n');
  }
  return 0;
}