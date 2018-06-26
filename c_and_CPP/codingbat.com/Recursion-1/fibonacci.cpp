#include<iostream>
using namespace std;
int fibo(int n){
  if(n == 0) return 0;
  else if(n==1 || n==2) return 1;
  else return  fibo(n-1) + fibo(n - 2) ;
}
int main(){
int input[] = {0,1,2,3,4,5,6,7,8};
for(int i=0;i<9;i++){
  cout << "fibonacci(" << input[i] << " ) -> "<<fibo(input[i]) << endl ;
}
return 0;
}
