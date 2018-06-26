#include<iostream>
using namespace std;
int fact(int n){
  if(n <=1)
  {
    return 1;
  }
  else
    return  n * fact(n-1) ;
}
int main(){
int input[] = {1,2,3,4,5,6,7,8,12};
for(int i=0;i<9;i++){
  cout << "factorial(" << input[i] << " ) -> "<<fact(input[i]) << endl ;
}
return 0;
}
