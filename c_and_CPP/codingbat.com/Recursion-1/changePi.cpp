#include<iostream>
#include<string.h>
using namespace std;
string changePi(string str){
  static int i = 0;
  if( i >= str.length()) { i=0; return str ; }
  else if (i+1 < str.length() && str.at(i) == 'p' && str.at(i+1) == 'i' ) { return changePi(str.replace(i++ ,2,"3.14")); }
  else{i++; return changePi(str); }
}

int main(){
string input[] = {"xpix" , "pipi" , "pip" ,"pi" ,"hip" , "p","x" ,"", "pixx", "xyzzy" };
for(int i=0;i<9;i++){
  cout << "changePi( " << input[i] << " ) -> "<<changePi(input[i]) << endl ;
}
return 0;
}
