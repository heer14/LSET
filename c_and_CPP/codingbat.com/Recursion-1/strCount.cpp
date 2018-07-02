#include<iostream>
#include<string>

using namespace std;
int strCount(string str , string sub){
//cout << str << endl ;
int n1 = str.length();
int n2 = sub.length();
  if( n1 <= 0) return 0;
  else if(str.find(sub)!=  string::npos ) return 1 + strCount(str.substr(str.find(sub)+n2) , sub );
  else return strCount(str.substr(1), sub);


}


int main(){
  string input[] = {"catcowcat" , "catcowcat" ,"catcowcat","cacatcowcat","xyx",
  "iiiijj","iiiijj","iiiijj","iiiijj","iiiijj","aaabababab","aaabababab","aaabababab","aaabababab"};
  string copy[] = {"cat" , "cow" , "dog" , "cat" ,"x","i","ii" , "iii","j" , "jj" ,"ab","aa","a","b"};
  for(int i=0;i<14;i++ ) cout <<"strCount( " << input[i] << "," << copy[i] << " )-> " << strCount(input[i] , copy[i]) << endl;
  return 0 ;
}
