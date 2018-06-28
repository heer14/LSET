#include<iostream>
#include<string>
using namespace std ;

int count11(string str)
{
  //cout << str << endl ;
  if(str.length() <= 1 ) return 0;
  else if(str[0] == '1' &&  str[1] == '1' ) return 1 + count11(str.substr(2));
  else return 0 + count11(str.substr(1));
}


int main(){
  string input[]={"11abc11" , "abc11x11x11" , "111" , "1111" , "1" , "" , "hi", "11x111x1111" ,"1x111","1hello1","hello"};
  for(int i=0;i<11;i++) cout << "count11( " << input[i] << " )-> "<< count11(input[i]) << endl ;
  return 0;
}
