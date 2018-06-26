#include<iostream>
using namespace std;
long int count7(long int  n){
  if(n <= 1) return 0 ;
  else if ( (n%10) ==7 ) return 1 + count7(n/10) ;
  else return 0 + count7(n/10) ;
}
int main(){
long int input[] = {717,7,123,77,7123,771237,771737,47571,777777,70701277,777576197,999999,99799};
for(int i=0;i<13;i++){
  cout << "count7(" << input[i] << " ) -> "<<count7(input[i]) << endl ;
}
return 0;
}
