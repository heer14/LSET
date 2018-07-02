#include<iostream>
#include<string>

using namespace std;
bool strCopies(string str , string sub , int num){
//cout << str << endl ;
int n1 = str.length();
int n2 = sub.length();
  if( n1 <= 0){
    if(num == 0) return true;
    else return false;
  }
  if(str.find(sub)!=  string::npos ) return strCopies(str.substr(str.find(sub)+1) , sub  , num-1);
  else return strCopies(str.substr(1), sub , num);


}


int main(){
  string input[] = {"catcowcat" , "catcowcat" ,"catcowcat","iiijjj",
                    "iiijjj","iiijjj","iiijjj","iiijjj","iiijjj",
                    "iiiiij","iiiiij","ijiiiiij","ijiiiiij","dogcatdogcat"};
  string copy[] = {"cat" , "cow" , "cow","i",
                   "i" , "ii" ,"ii", "x" ,"x",
                   "iii" , "iii" ,"iiii","iiii","dog"};
  int num[] = {2,2,1,3,4,2,3,3,0,3,4,2,3,2};
  for(int i=0;i<14;i++ ) cout <<"strCopies( " << input[i] << "," << copy[i] << "," << num[i] << " )-> " << strCopies(input[i] , copy[i] , num[i]) << endl;
  return 0 ;
}
