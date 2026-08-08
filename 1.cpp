#include<stdio.h>
#define MAXN 100005
#define MAXM 200005

int arrInput[2 * MAXN];
int n, m;

int main() {
  int d, i;
  scanf("%d", &d);
  while(d--) {
    scanf("%d %d", &n, &m);
    for(i = 1; i <= 2*m; ++i) {
      scanf("%d", &arrInput[i]);
    }
  }
  return 0;
}