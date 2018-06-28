#include<iostream>
#include<string>
using namespace std ;
string allStar(string str)
{
  static int i = 0;
  if( str.length() <= 1 ) return str;
  else if( i > str.length()-1){i=0; return str ; }
  else if (i * 2 !=0  ){
    string ans = str.insert(i , "*");
    i = i+2;
    return allStar(ans);
    }
    else
    {
      i++;
      return allStar(str);
    }
}





int main(){

  string input[] = {"hello" , "abc" , "ab" , "a" , "" , "3.14" , "chocolate" , "1234"};
  for(int i=0;i<8 ; i++) cout << "allStar( " << input[i] << " ) ->" << allStar(input[i]) << endl ;
  return 0;
}
