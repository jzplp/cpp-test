#include <stdio.h>
#include <map>
#define MAXN 31

using namespace std;

// 目标状态
int goal[3][3];
// 当前空白位置
int emptyPos[2];
// 当前状态
// stateArr[i][j]为一个立方体的状态 最后一个下标的值表示顶面/上面/右侧面三个颜色值
int stateArr[3][3][3];

map<unsigned long long, int> mp;

// 四个方向移动
int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// 四个方向的反向 改回去使用
int stepsRe[4] = {1, 0, 3, 2};
// 四个方向的原值如何覆盖为新值的对应关系
int stepChange[4][3] = {
    {1, 0, 2},
    {1, 0, 2},
    {2, 1, 0},
    {2, 1, 0}};

// 判断当前结构是否存在过。如果没存在过或者存在过但变化的次数更多，则加入map中，否则返回false
bool setMap(int n)
{
  int i, j, k;
  unsigned long long num = 0;
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      if (i == emptyPos[0] && j == emptyPos[1])
        num *= 100;
      else
      {
        num = num * 10 + stateArr[i][j][0];
        num = num * 10 + stateArr[i][j][1];
      }
    }
  }
  if (mp.count(num) && mp[num] >= n)
    return false;
  mp[num] = n;
  return true;
}

// 判断当前状态是否符合终点状态
int judge()
{
  int n = 0;
  int i, j;
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      if (goal[i][j] == 0)
      {
        if (i != emptyPos[0] || j != emptyPos[1])
          return ++n;
        continue;
      }
      if (goal[i][j] != stateArr[i][j][0])
        return ++n;
    }
  }
  return n;
}

// 输出数组，调试用
void printArr()
{
  int i, j;
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
      printf("%d ", goal[i][j]);
    putchar('\n');
  }
}

bool loop(int n, int preStep)
{
  // printf("qqq %d\n", n);
  int i, j, k;
  int a, b;
  int jnum = judge();
  if (n <= 0)
    return jnum == 0;
  if (n + 1 < jnum)
    return false;
  if (!setMap(n))
    return false;
  // 四个方向遍历
  for (i = 0; i < 4; ++i)
  {
    if (preStep != -1 && i == stepsRe[preStep])
      continue;
    // 正向旋转过去
    // a,b 要转的位置
    a = steps[i][0] + emptyPos[0];
    b = steps[i][1] + emptyPos[1];
    if (a < 0 || a > 2 || b < 0 || b > 2)
      continue;
    for (j = 0; j < 3; ++j)
      stateArr[emptyPos[0]][emptyPos[1]][j] = stateArr[a][b][stepChange[i][j]];
    emptyPos[0] = a;
    emptyPos[1] = b;

    if (loop(n - 1, i))
      return true;

    // 反向旋转回来
    k = stepsRe[i];
    a = emptyPos[0] + steps[k][0];
    b = emptyPos[1] + steps[k][1];
    for (j = 0; j < 3; ++j)
      stateArr[emptyPos[0]][emptyPos[1]][j] = stateArr[a][b][stepChange[k][j]];
    emptyPos[0] = a;
    emptyPos[1] = b;
  }
  return false;
}

int main()
{
  int i, j, k;
  char c;

  while (scanf("%d %d", &emptyPos[1], &emptyPos[0]) == 2)
  {
    if (emptyPos[0] == 0 || emptyPos[1] == 0)
      return 0;
    mp.clear();
    emptyPos[0]--;
    emptyPos[1]--;
    // 读入换行符
    getchar();
    for (i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        scanf("%c", &c);
        // 白色1 蓝色2 红色3 空0
        switch (c)
        {
        case 'W':
          k = 1;
          break;
        case 'B':
          k = 2;
          break;
        case 'R':
          k = 3;
          break;
        case 'E':
          k = 0;
          break;
        }
        goal[i][j] = k;
        // 读入一个分隔符
        getchar();
      }
    }
    // 初始化当前状态
    for (i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        stateArr[i][j][0] = 1;
        stateArr[i][j][1] = 3;
        stateArr[i][j][2] = 2;
      }
    }
    if (judge() == 0)
    {
      printf("0\n");
      continue;
    }
    for (i = 1; i < MAXN; ++i)
    {
      // printf("---%d\n", i);
      if (loop(i, -1))
        break;
    }
    if (i == MAXN)
      printf("-1\n");
    else
      printf("%d\n", i);
  }
  return 0;
}
