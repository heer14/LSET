#include<iostream>
#include<string>

using namespace std ;

string stringClean(string str)
{
  if(str.length() <= 0 ) return str;
  else if(str.length() >=3  && str[0] == str[1] && str[1] == str[2] )return str[1] + stringClean(str.substr(3));
  else if(str[0] == str[1] ) return str[1] + stringClean(str.substr(2));
  else return str[0] + stringClean(str.substr(1));
}




int main(){
  string input[] = {"yyzzza" , "abbbcdd" , "hello" ,"XXabcYY" ,"112ab445" , "Hello Bookkeeper"};
  for(int i=0;i<6;i++) cout << "stringClean ( " << input[i] << " )-> " << stringClean(input[i]) << endl;
  return 0;
}
