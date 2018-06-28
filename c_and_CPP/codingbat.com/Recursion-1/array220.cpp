#include<iostream>

using namespace std;
bool array220(int arr[] , int n ){
if(n >= 8 || arr[n+1] == -1 ) return false;
else if(arr[n+1] == arr[n]*10  ) return true;
else return array220(arr , n+1 );
}
int main(){
  //input has padded with 1 to create equal length
int inputBase[14][9] = {{1,2,20,-1,-1,-1,-1,-1,-1} , {3,30,-1,-1,-1,-1,-1,-1,-1} , {3,-1,-1,-1,-1,-1,-1,-1,-1} ,
{-1,-1,-1,-1,-1,-1,-1,-1,-1} , {3,3,30,4,-1,-1,-1,-1,-1} , {2,19,4,-1,-1,-1,-1,-1,-1} ,{20,2,21,-1,-1,-1,-1,-1,-1} ,
 {20,2,21,210,-1,-1,-1,-1,-1},{2,200,2000,-1,-1,-1,-1,-1,-1},{0,0,-1,-1,-1,-1,-1,-1,-1},
{1,2,3,4,5,6,-1,-1,-1},{1,2,3,4,5,50,6,-1,-1},{1,2,3,4,5,51,6,-1,-1},{1,2,3,4,4,50,500,6,0} };
cout << "inputs are padded with 1 to create equal length" << endl;
for(int i=0;i<14;i++){
  cout << "array220({ " ;
  for(int i1=0;i1<9;i1++)
  {if(inputBase[i][i1] !=-1 )cout << inputBase[i][i1] << ",";
  else break;
 }
cout << " } , 0  ) -> ";
if(array220(inputBase[i] , 0))  cout << "True";
else cout << "false";
cout << endl ;
}
return 0;
}
