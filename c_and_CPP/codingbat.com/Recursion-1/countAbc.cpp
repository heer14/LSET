#include<iostream>
#include<string>
using namespace std ;

int countAbc(string str)
{
  if(str.length() <= 2 ) return 0;
  else if(str[0] == 'a' && str[1] == 'b' && (str[2] == 'c' || str[2] == 'a' ) ) return 1 + countAbc(str.substr(1));
  else return 0 + countAbc(str.substr(1));
}


int main(){
  string input[]={"abc" , "abcxxabc" , "abaxxaba" , "ababc" , "abxbc" , "aaabc" , "hellow", "" ,"ab","aba","aca" , "aaa"};
  for(int i=0;i<12;i++) cout << "countAbc( " << input[i] << " )-> "<< countAbc(input[i]) << endl ;
  return 0;
}
