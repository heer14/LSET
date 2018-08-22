#include<iostream>
using namespace std;
int main(){
    int n;
    cout << "enter n: ";
    cin >> n;
    int table[n+1];
    table[1] = 1
  ;
    table[2] = 1;
    for(int i=3;i<=n;i++)
    {
      table[i] = table[i-1] + table[i-2];
    }
    cout << table[n];
  return 0;
}
