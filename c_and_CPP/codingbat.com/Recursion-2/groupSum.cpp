#include<iostream>
#include<vector>

using namespace std;
bool groupSum(int start , vector<int> arr , int target) {

  if(arr.size() == start ) return (target == 0);
//if start is selected
  else if(groupSum(start+1 , arr , target - arr[start] )) return true;
//if start is NOT selected
  else if(groupSum(start+1 ,  arr , target )) return true;
  else return false;

}





int main(){
  vector< vector<int> > arr{{2,4,8},{2,4,8},{2,4,8},{2,4,8},{2,4,8},{2,4,8},{1},{9},{9},{},{10,2,2,5},{10,2,2,5},{10,2,2,5}};
  int target[] = {10,14,9,8,8,2,1,1,0,0,17,15,9};
  int start[] = {0,0,0,0,1,1,0,0,1,0,0,0,0} ;
  for(int i= 0 ; i <13 ; i++)
  {
    cout << "groupSum ( "<< start[i] << " , [ ";
    for(int j=0;j<arr[i].size() ; j++) cout << arr[i][j] << "," ;
    cout << " ] , "<< target[i] << ") -> "<<groupSum(start[i] , arr[i] , target[i]) << endl;

  }
  return 0;
}
