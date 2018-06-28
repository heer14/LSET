#include<iostream>

using namespace std;
bool array6(int arr[] , int n ){
if(n >= 5  ) return false;
else if(arr[n] == 6) return true;
else return array6(arr , n+1 );
}
int main(){
  //input has padded with 1 to create equal length
int inputBase[8][5] = {{1,6,4,1,1} , {1,4,1,1,1} , {6,1,1,1,1} , {1,1,1,1,1} , {6,2,2,1,1} , {2,5,1,1,1,} ,{1,9,4,6,6} , {2,5,6,1,1} };
cout << "inputs are padded with 1 to create equal length" << endl;
for(int i=0;i<8;i++){
  cout << "array6(" ;
  for(int i1=0;i1<5;i1++) cout << inputBase[i][i1] << ",";
cout << " , 0  ) -> ";
if(array6(inputBase[i] , 0))  cout << "True";
else cout << "false";
cout << endl ;
}
return 0;
}
