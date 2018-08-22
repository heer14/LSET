/*
https://www.geeksforgeeks.org/edit-distance-dp-5

Given two strings str1 and str2 and below operations that can performed on str1. Find minimum number of edits (operations) required to convert ‘str1’ into ‘str2’.

Insert
Remove
Replace
All of the above operations are of equal cost.

Examples:

Input:   str1 = "geek", str2 = "gesek"
Output:  1
We can convert str1 into str2 by inserting a 's'.

Input:   str1 = "cat", str2 = "cut"
Output:  1
We can convert str1 into str2 by replacing 'a' with 'u'.

Input:   str1 = "sunday", str2 = "saturday"
Output:  3
Last three and first characters are same.  We basically
need to convert "un" to "atur".  This can be done using
below three operations.
Replace 'n' with 'r', insert t, insert a
*/
#include<iostream>

using namespace std;

int main(){
  cout << "enter string 1 : " ;
  string str1 , str2;
  cin >> str1;
  cout << endl << "enter string 2 :";
  cin >> str2;
  int n= str1.length();
  int m = str2.length();
  //cout << n << m << endl;

  int matrix[n+1][m+1];
  for(int i = 0; i<=n;i++)
  {
    for(int j=0; j <=m ;j++)
    {
      if(i==0 && j==0 ) matrix[i][j] = 0;
      else if(i == 0 ) matrix[i][j] = j;
      else if(j==0) matrix[i][j] = i;
      else if(str1[i-1] == str2[j-1]) matrix[i][j] = matrix[i-1][j-1];
      else{
        matrix[i][j] = min(min(matrix[i-1][j] , matrix[i][j-1]) , matrix[i-1][j-1]) + 1 ;
      }
    //  cout << matrix[i][j] << " ";
    }
    //cout << endl;
  }
  cout << matrix[n][m] << endl;

  return 0;
}
