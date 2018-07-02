#include<iostream>
#include<string>
using namespace std;
bool nestParen(string str)
{
//cout << str << endl;
if(str.length() == 0)   return true ;
if(str[0] == '(' && str[str.length()-1] == ')') return nestParen(str.substr(1, str.length()-2)) ;

return false;
}




int main(){
  string input[] ={"(())","((()))","(((x))","((())","((()()","()","","(YY)" ,"(yy)","(())","(((y))","((y)))","((()))","(())))","((yy())))","(((())))" };
  for(int i=0;i<16;i++) cout << "nestParen { "  << input[i] << " } -> "<< nestParen(input[i]) << endl ;
  //cout << nestParen("((qwe(ab(heer)c))p)");
  return 0;
}
