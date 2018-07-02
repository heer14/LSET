#include<iostream>
#include<string>

using namespace std;
int strDist(string str , string sub){
//cout << str << endl ;
int n1 = str.length();
int n2 = sub.length();
//cout <<"first "<< str.substr(0,n2) <<endl;
//cout <<"second "<< str.substr(n1-n2) <<endl;
  if( n1 < n2) return 0;
  if(str.substr(0,n2) == sub && str.substr(n1-n2) == sub  ) return n1;
  if(str.substr(0,n2) != sub) return strDist(str.substr(1) , sub );
  return strDist(str.substr(0 , n1 - 1 ) , sub);


}


int main(){
  string input[] = {"catcowcat" , "catcowcat" ,"cccatcowcatxx","abccatcowcatcatxyz","xyx",
  "xyx","xyx","z","x","","hiHellohihihi","hiHellohihihi","hiHellohihihi","hiHellohihihi"};
  string copy[] = {"cat" , "cow" , "cat","cat" , "x" ,"y","z","z" , "z","z" , "hi" ,"hih","o","ii"};
  for(int i=0;i<14;i++ ) cout <<"strDist( " << input[i] << "," << copy[i] << " )-> " << strDist(input[i] , copy[i]) << endl;
//strDist("catcowcat" , "cat");
  return 0 ;
}
