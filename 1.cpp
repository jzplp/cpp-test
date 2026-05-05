#include<stdio.h>

struct Item {
  int x, y;
  int t;
};

Item arr[10010];
int n;


void computed() {
  
}


int main() {
  int i, j;
  while(scanf("%d", &n) > 0 && n > 0) {
    for(i = 0; i < n; ++i)
      scanf("%d %d %d", arr[i].x, arr[i].y, arr[i].t);
  }
  computed();

  return 0;
}