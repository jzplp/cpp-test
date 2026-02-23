#include <stdio.h>
#include <string.h>

char arr1[20];
int len1;
char arr2[20];
int len2;

unsigned long long resList[10000];
int resLenList[10000];
int resLen;

bool isNumber(char c) {
  if(c >= '0' && c<= '9') return true;
  return false;
}

void copyArr2()
{
  int i, j;
  for (i = 0, j = 0; i < len1 * 2; ++i)
  {
    if (arr1[i] != 0)
    {
      arr2[j++] = arr1[i];
    }
  }
  len2 = j;
}

// 判断是否符合前导0条件
bool judgeZero() {
  int i, j, k;
  // 首位0
  if(arr2[0] == '0') {
    if(isNumber(arr2[1])) return false;
  }
  for(i = 1; i < len2; ++i) {
    if(isNumber(arr2[i])) continue;
    if(arr2[i + 1] == 0 && i + 2 < len2) {
      if(isNumber(arr2[i + 2])) return false;
    }
  }
  return true;
}

// 必须有符号
bool hasSign() {
  int i, n = 0;
  for(i = 0; i < len2; ++i) {
    if(arr2[i] == '+' || arr2[i] == '-' || arr2[i] == '*') ++n;
  }
  return n ? true : false;
}

void judge()
{
  if(len1 <= 1) return;
  copyArr2();
  if(!hasSign()) return;
  if(!judgeZero()) return;

  // 判断等式是否等于2000
  // 加到结果中
}

void dfs(int n)
{
  if (n >= len1 - 1)
    judge();
  dfs(n + 1);
  arr1[n * 2 + 1] = '+';
  dfs(n + 1);
  arr1[n * 2 + 1] = '-';
  dfs(n + 1);
  arr1[n * 2 + 1] = '*';
  dfs(n + 1);
  arr1[n * 2 + 1] = 0;
}

int main()
{
  int t, i, j, k;
  char c;
  while (1)
  {
    memset(arr1, 0, sizeof(arr1));
    len1 = 0;
    resLen = 0;
    for (i = 0;; i = i + 2)
    {
      c = getchar();
      arr1[i] = c;
      if (c == '=')
        break;
    }
    if (i == 0)
      return 0;
    len1 = i;
    while (getchar() != '\n')
      ;
    dfs(0);
  }

  return 0;
}
