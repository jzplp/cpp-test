#include <stdio.h>
#include <stack>
#define MAXN 1000005
using namespace std;

int n, l;
int arr[MAXN];
int sumArr[MAXN];

struct Res
{
  int start, end;
  double value;
};

void init()
{
  int i, j;
  sumArr[0] = arr[0];
  for (i = 0; i < n; ++i)
    sumArr[i] = sumArr[i - 1] + arr[i];
  for (i = 0; i < n; ++i)
    printf("%d ", sumArr[i]);
  putchar('\n');
}

Res computed()
{
  int i, j, k;
  Res resMax = {0, l, 0}, res;
  stack<int> st;
  for (i = l; i < n; ++i)
  {
  }
}

int main()
{
  int t, i, j, k;
  char c;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &l);
    getchar();
    for (i = 0; i < n; ++i)
    {
      scanf("%c", &c);
      arr[i] = c - '0';
    }
    init();
  }
  return 0;
}