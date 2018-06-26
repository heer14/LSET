#include<iostream>
using namespace std;
int bunny2(int n){
if(n == 0) return 0;
else if(n == 1) return 2;
else if(n % 2 == 0 ) return  3 + bunny2(n-1) ;
else return 2 + bunny2(n-1);
}
int main(){
int input[] = {0,1,2,3,4,5,6,10};
for(int i=0;i<8;i++){
  cout << "bunnyEars2( " << input[i] << " ) -> "<<bunny2(input[i]) << endl ;
}
return 0;
}
