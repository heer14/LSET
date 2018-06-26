#include<iostream>
#include<string.h>
using namespace std;
int countHi(string str){
  if(str.length() == 0) return 0 ;
  else if (str[0] == 'h' && str[1] == 'i' ) return 1 + countHi(str.erase(0,2)) ;
  else return 0 + countHi(str.erase(0,1)) ;
}
int main(){
string input[] = {"xxhixx" , "xhixhix" , "hi" , "h" , "ihihihihih", "ihihihihihi" , "hiAAhi12hi","xhixhxihihhih","ship"};
for(int i=0;i<9;i++){
  cout << "countHi(" << input[i] << " ) -> "<<countHi(input[i]) << endl ;
}
return 0;
}
