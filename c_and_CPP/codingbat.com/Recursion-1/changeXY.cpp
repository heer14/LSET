#include<iostream>
#include<string.h>
using namespace std;
string changeXY(string str){
  static int i = 0;
  if( i >= str.length()) { i=0; return str ; }
  else if (str.at(i) == 'x' ) { return changeXY(str.replace(i++ ,1,"y")); }
  else{i++; return changeXY(str); }
}

int main(){
string input[] = {"codex" , "xxhixx" , "xhixhix" , "hiy" , "h","x" ,"", "xxx", "yyhxyi" , "hihi"};
for(int i=0;i<10;i++){
  cout << "changeXY( " << input[i] << " ) -> "<<changeXY(input[i]) << endl ;
}
return 0;
}
