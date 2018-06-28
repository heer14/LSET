#include<iostream>
#include<string>
using namespace std ;
string pairStar(string str)
{
  static int i = 0;
  if( str.length() <= 1 ) return str;
  else if( i > str.length()-1){i=0; return str ; }
  else if (str[i] == str[i+1] ) {
    string ans = str.insert(i+1 , "*");
    i = i+2;
    return pairStar(ans);
    }
    else
    {
      i++;
      return pairStar(str);
    }
}
int main(){

  string input[] = {"hello" , "xxyy" , "aaaa" , "aaab" , "aa" , "a" , "chocolate" , "abba" , "abbbba"};
  for(int i=0;i<9 ; i++) cout << "pairStar( " << input[i] << " ) ->" << pairStar(input[i]) << endl ;
  return 0;
}
