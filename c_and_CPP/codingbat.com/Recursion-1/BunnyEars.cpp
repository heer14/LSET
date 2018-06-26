#include<iostream>
using namespace std;
int bunny(int n){
if(n == 0) return 0;
else if(n == 1) return 2;
else return  2 + bunny(n-1) ;
}
int main(){
int input[] = {0,1,2,3,4,5,12,50,234};
for(int i=0;i<9;i++){
  cout << "bunnyEars(" << input[i] << " ) -> "<<bunny(input[i]) << endl ;
}
return 0;
}
