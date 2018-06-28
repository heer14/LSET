#include<iostream>
#include<string.h>
using namespace std;
string noX(string str){
  static int i = 0;
  if(i >= str.length() ){i=0; return str ;}
  else if (str[i] == 'x' ){ return noX(str.erase(i,1)); }
  else {i++; return noX(str);}
}
int main(){
string input[] = {"xxhixx" , "xhixhix" , "hi" , "h" , "x", "hihi" , "hiAAhi12hi"};
for(int i=0;i<7;i++){
  cout << "noX(" << input[i] << " ) -> "<<noX(input[i]) << endl ;
}
return 0;
}
