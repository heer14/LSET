#include<iostream>
#include<stdlib.h>
using namespace std;
int *a;
int n;
int *lis;
void printLis(){
  for(int i=0;i<n;i++)cout << lis[i] << " ";
  cout << endl;
}

int LIS(){

lis= (int *)malloc(n*sizeof(int));
for(int i=0 ; i < n;i++) lis[i] = 1;
printLis();
for(int i=1 ; i<n;i++)
{
  for(int j=0;j< i;j++){
    if(a[i] > a[j]){
      lis[i] = max(lis[i] , lis[j] + 1);
    }
printLis();
  }

}
int ans = lis[n-1];
free(lis);
return ans;
}


int main(){
  cout << "enter size of array : ";
  cin >> n;
  cout << "enter array :" <<endl;
a= (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) cin >> a[i];
  cout << "Longest common subsequance is : " << LIS() << endl;
free(a);

  return 0;
}
