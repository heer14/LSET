/*Problem 1: Count the steps.										40Marks
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
Note: Given n will be a positive integer. Where 1 ≤ n ≤106
Example 1:
Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:
Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
Print the output for the following inputs:
1
10
25
999
3000
4096
1000000
*/



#include<iostream>
using namespace std;

long f(unsigned long long int n){
    unsigned long long int first=1,second=2,temp;
    for(unsigned long long int i=3;i<=n;i++)
    {
       temp= first + second;
       first = second;
       second = temp;
    }
    return second;
}
int main(){

    unsigned long long int n;
    cout << "enter no of staircase " ;
    cin >> n;
    cout << f(n) ;
    return 0;
}



