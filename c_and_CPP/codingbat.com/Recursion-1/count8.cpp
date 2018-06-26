#include<iostream>
using namespace std;
long int count8(long int  n){
  if(n <= 1) return 0 ;
  else if ( (n%100) == 88 ) return 2 + count8(n/10) ;
  else if((n%10) == 8 )return 1 + count8(n/10);
  else return 0 + count8(n/10) ;
}
int main(){
long int input[] = {8,818,8818,8088,123,81238,88788,8234,2348,23884,0,1818188,8818181,1080,188,88888,9898,78};
for(int i=0;i<18;i++){
  cout << "count8(" << input[i] << " ) -> "<<count8(input[i]) << endl ;
}
return 0;
}
