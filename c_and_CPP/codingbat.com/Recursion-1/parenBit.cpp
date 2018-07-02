#include<iostream>
#include<string>
using namespace std;
string parentBit(string str){
  if(str.length() <= 0 ) return str;
  else if (str[0] == '(' ){
    int i = 0;
    string temp;
    while(str[i-1] != ')'){
    temp = temp + str[i];
    i++;
    }
    return temp ;
  }

  else return parentBit(str.substr(1));
}
int main(){
    string input[] = {"xyz(abc)123" , "x(hello)" ,"(xy)1" ,"not really (possible)" ,"(abc)" ,"(abc)xyz" ,"(abc)x" , "(x)" ,"()" ,"res (ipsa) loquitor" ,
  "hello(not really)there" , "ab(ab)ab" };
    for(int i=0;i<12;i++)
    {
      cout <<"parentBit ( "  << input[i] << " ) -> "<< parentBit(input[i]) << endl ;

    }


  return 1;
}
