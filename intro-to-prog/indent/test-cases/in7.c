int cnt=0;
int add(int a, int b) {cnt++;return a+b;}
#include    <stdio.h>
int main(void) {
#define N        50
int i
; int
t=0; for(i=0;i<N;i++) t+= add(i,i+1);
printf("%d %d\n",cnt,t); return 0;}