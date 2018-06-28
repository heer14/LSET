#include<iostream>
#include<string>
using namespace std ;

int countPair(string str)
{
  if(str.length() <= 2 ) return 0;
  else if(str[0] == str[2] ) return 1 + countPair(str.substr(1));
  else return 0 + countPair(str.substr(1));
}


int main(){
  string input[]={"axa" , "axax" , "axbx" , "hi" , "hihih" , "ihihhh" , "ihjxhh", "" ,"a","aa","aaa"};
  for(int i=0;i<11;i++) cout << "countPair( " << input[i] << " )-> "<< countPair(input[i]) << endl ;
  return 0;
}
