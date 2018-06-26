#include<iostream>
using namespace std;
int triangle(int n){
  if(n ==1) return 1;
  else if (n==0) return 0;
  else return  n +  triangle(n-1) ;
}
int main(){
int input[] = {1,2,3,4,5,6,7};
for(int i=0;i<7;i++){
  cout << "triangle(" << input[i] << " ) -> "<<triangle(input[i]) << endl ;
}
return 0;
}
