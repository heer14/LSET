#include<iostream>
#include<string>
using namespace std;

string endX(string str){
if(str.length() <=0 ) return str ;
else if(str[0] == 'x' ) return endX(str.substr(1)) + "x";
else return str[0] + endX(str.substr(1));


}
int main(){
  string input[] = {"xxre" , "xxhixx" , "xxhixhixx","hiy","h","x","xx"," " , "bxxb" , "baxx" , "aaaxxx","xhixxx"};

  for(int i = 0; i < 12 ; i++)
  cout << "endX ( " << input[i] << ") -> " << endX(input[i]) << endl;
  return 0;
}
