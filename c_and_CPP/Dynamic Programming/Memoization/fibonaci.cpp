#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n;
int *memo;

void init(){
for(int i=0;i<=n ; i++)
memo[i] = -1;

}
int fib(int n)
{
if(memo[n] == -1)
{
  if(n == 1)memo[n] = 1;
  else if(n == 2)memo[n] = 1
  ;
  else memo[n] = fib(n-1) + fib(n-2);
}
  return memo[n];
}


int main(){
  cout << "enter the n: "<<endl;
  cin >> n;
  memo = (int *)malloc((n+1) * sizeof(int));
  init();
  cout << fib(n) ;
}
