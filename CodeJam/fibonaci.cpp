/*Description
The Fibonacci sequence is calculated by adding the previous two numbers of the sequence. The first two numbers in the Fibonacci number are 0 and 1.

The sequence Fn of Fibonacci numbers is defined by the recurrence relation: Fn = Fn-1 + Fn-2 (n ≥ 2).

Given an integer n, write a program which prints nth Fibonacci number.

Input
The first line contains one integer n. (1 ≤ n ≤ 90)

Output
Output one line of one integer, nth Fibonacci number.
*/

#include<iostream>
int main(){
int n;
long long  int t;
    scanf("%d", &n);
    long long  int f=1;
    long long int s= 1;
    if(n==1) t=1;
    else if(n==2) t=1;
    else{
    for(int i=3;i<=n;i++)
    {
        t = f+s;
   f=s;
        s=t;
    }
  }
    printf("%lld",t);
    return 0;
}
