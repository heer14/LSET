#include<iostream>
#include<string.h>
using namespace std;
int countx(string str){
  if(str.length() == 0) return 0 ;
  else if (str[0] == 'x' ) return 1 + countx(str.erase(0,1)) ;
  else return 0 + countx(str.erase(0,1)) ;
}
int main(){
string input[] = {"xxhixx" , "xhixhix" , "hi" , "h" , "x", "hihi" , "hiAAhi12hi"};
for(int i=0;i<7;i++){
  cout << "countx(" << input[i] << " ) -> "<<countx(input[i]) << endl ;
}
return 0;
}
