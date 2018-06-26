#include<iostream>
using namespace std;
int powerN(int  base , int power ){
  if(power == 1) return base ;
  else if (power == 0) return 1;
  else return base * powerN(base , power - 1);
}
int main(){
int inputBase[] = {3,3,3,2,2,2,2,2,10,10,10};
int inputPower[] ={1,2,3,1,2,3,4,5,1,2,3};
for(int i=0;i<11;i++){
  cout << "powerN(" << inputBase[i] << " , "<<inputPower[i] << " ) -> "<<powerN(inputBase[i] , inputPower[i]) << endl ;
}
return 0;
}
