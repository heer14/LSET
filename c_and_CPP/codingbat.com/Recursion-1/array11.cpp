#include<iostream>

using namespace std;
int array11(int arr[] , int n ){
if(n >= 6  ) return 0;
else if(arr[n] == 11) return 1 + array11(arr , n+1);
else return array11(arr , n+1 );
}
int main(){
  //input has padded with 1 to create equal length
int inputBase[9][6] = {{1,2,11,-1,-1,-1} , {11,11,-1,-1,-1,-1} , {1,2,3,4,-1,-1} , {1,11,3,11,11,-1} , {11,-1,-1,-1,-1,-1} ,
{1,-1,-1,-1,-1,-1} ,{-1,-1,-1,-1,-1,-1} , {11,2,3,4,11,5},{11,5,11,-1,-1,-1} };
cout << "inputs are padded with -1 to create equal length" << endl;
for(int i=0;i<9;i++){
  cout << "array11(" ;
  for(int i1=0;i1<6;i1++) cout << inputBase[i][i1] << "," ;
cout << " , 0  ) -> "<< array11(inputBase[i] , 0) << endl ;
}
return 0;
}
