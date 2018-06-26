#include<iostream>
using namespace std;
int sumDigits(int n){
  if(n ==1) return 1;
  else if (n==0) return 0;
  else return  (n%10) +  sumDigits(n/10) ;
}
int main(){
int input[] = {126,49,12,10,1,0,730,1111,11111,10110,235};
for(int i=0;i<11;i++){
  cout << "sumDigits(" << input[i] << " ) -> "<<sumDigits(input[i]) << endl ;
}
return 0;
}
