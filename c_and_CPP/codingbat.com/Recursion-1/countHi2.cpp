#include<iostream>
#include<string>
using namespace std;
int countHi2(string str)
{
  //cout << str <<endl;
  if(str.length() <= 0 ) return 0;
  else if(str.length() >= 3 && str[1] == 'h' && str[2] == 'i' && str[0] != 'x') return 1 + countHi2(str.substr(3)) ;
  else if(str.length() >= 3 && str[1] == 'h' && str[2] == 'i' && str[0] == 'x') return 0 + countHi2(str.substr(3)) ;
  else if(str.length() >=2  && str[0] == 'h' && str[1] == 'i') return 1 + countHi2(str.substr(2)) ;
  else return 0 + countHi2(str.substr(1)) ;
}
int main()
{
  string input[] = {"ahixhi","ahibhi","xhixhi","hixhi","hixhhi","hihihi","hihihix","xhihihix","xxhi","hixxhi","hi","xxxx","h" , "x","","Hellohi"};
  for(int i=0;i<16;i++) cout << "countHi2( "<< input[i] << " ) -> " << countHi2(input[i]) << endl;
//cout << countHi2("xhixhi");

  return 0;
}
