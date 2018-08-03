#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int n,m;
int mat[999][999];
int visited[999][999];

void clear1()
{

            for(int i1 =0;i1<n;i1++)
            {
                for(int j1=0;j1<m;j1++)
                    visited[i1][j1] = 0;
            }
}
int dfs(int i , int j)
{

       //cout << i << j << endl ;
    int sum = 1 ;

    visited[i][j] = 1;

    if(visited[i][j+1] ==0   && mat[i][j+1]  == 1 )
         sum = sum +  dfs(i , j+1);
    else   if(visited[i+1][j] == 0  && mat[i+1][j]  == 1 )
        sum = sum +  dfs(i+1 , j);
    else   if(visited[i][j-1] == 0  && mat[i][j-1]  == 1 )
        sum = sum +  dfs(i , j-1);
    else   if(visited[i-1][j] == 0  && mat[i-1][j]  == 1 )
        sum = sum +  dfs(i-1, j );

    //cout << sum << " ";
    return sum ;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >> n>> m ;
    for(int i=0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
            cin >> mat[i][j];
    }
    int cnt  = 0,max1=0;
    for(int i =0 ;i< n ; i++)
    {

         for(int j = 0; j< m;j++)
        {
            if(mat[i][j] == 1 ){
                cnt  = dfs(i , j );
            clear1();
            if(cnt > max1)
                max1 = cnt;
            }

        }
    }
    cout << max1  ;
    return 0;
}
