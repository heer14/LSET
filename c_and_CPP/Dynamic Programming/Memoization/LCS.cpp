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
      if(i == 0 || j == 0 ) matrix[i][j] = 0;
      else if(str1[i-1] == str2[j-1]) matrix[i][j] = matrix[i-1][j-1] + 1;
      else{
        matrix[i][j] = max(matrix[i-1][j] , matrix[i][j-1]);
      }
    //  cout << matrix[i][j] << " ";
    }
    //cout << endl;
  }
  cout << matrix[n][m] << endl;

  return 0;
}
