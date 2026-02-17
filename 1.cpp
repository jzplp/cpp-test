#include <stdio.h>

// 目标状态
int goal[3][3];
// 当前空白位置
int empty[2];
// 当前状态
// stateArr[i][j]为一个立方体的状态 最后一个下标的值表示顶面/上面/右侧面三个颜色值
int stateArr[3][3][3];

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

// 判断当前状态是否符合终点状态
bool judge()
{
  int i, j;
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      if (goal[i][j] == 0)
      {
        if (i != empty[0] && j != empty[1])
          return false;
        continue;
      }
      if (goal[i][j] != stateArr[i][j][0])
        return false;
    }
  }
  return true;
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
bool loop(int n)
{
  printf("qqq %d\n", n);
  int i, j, k;
  int a, b;
  if (n == 0)
    return judge();
  // 四个方向遍历
  for (i = 0; i < 4; ++i)
  {
    // 正向旋转过去
    // a,b 要转的位置
    a = steps[i][0] + empty[0];
    b = steps[i][1] + empty[1];
    if (a < 0 || a > 2 || b < 0 || b > 2)
      continue;
    for (j = 0; j < 3; ++j)
      stateArr[empty[0]][empty[1]][j] = stateArr[a][b][stepChange[i][j]];
    empty[0] = a;
    empty[1] = b;
    if (loop(n - 1))
      return true;

    // 反向旋转回来
    k = stepsRe[i];
    a = empty[0] + steps[k][0];
    b = empty[0] + steps[k][1];
    for (j = 0; j < 3; ++j)
      stateArr[empty[0]][empty[1]][j] = stateArr[a][b][stepChange[i][j]];
    empty[0] = a;
    empty[1] = b;
  }
  return false;
}

int main()
{
  int i, j, k;
  char c;
  while (scanf("%d %d", &empty[1], &empty[0]) >= 2)
  {
    if (empty[0] == 0 && empty[1] == 0)
      return 0;
    empty[0]--;
    empty[1]--;
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
    if (judge())
    {
      printf("0\n");
      continue;
    }
    for (i = 1; i < 31; ++i)
    {
      printf("---%d\n", i);
      if (loop(i))
        break;
    }
    if (i == 31)
    {
      printf("-1\n");
    }
    else
    {
      printf("%d\n", i);
    }
  }
  return 0;
}
