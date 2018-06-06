/*Problem 2: Who is the winner?									60Marks
Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.
Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.
Example 1:
Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2.
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
Hence, player 1 will never be the winner and you need to return False.
Example 2:
Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
Conditions:
1.	1 <= length of the array <= 20.
2.	Any scores in the given array are non-negative integers and will not exceed 10,000,000.
3.	If the scores of both players are equal, then player 1 is still the winner.

Print the output for the following array inputs:
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
1,2,3,4,5,6,789,8,9,10000000,11,12,13,14,159,16,17,18,19,20
1,2,300000,14,515,6,789
10000000,2,369,14,459,6,70
*/
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <sstream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
  string s;
  cin >> s;
  int k=0;
  vector<int> arr;
  int player1=0,player2=0;
replace(s.begin() , s.end(),',',' ');
  stringstream stream(s);
  int i;

while(stream >> i){
    arr.push_back(i);
    //cout << arr[k]<<" ";
    k++;
}
  int end = arr.size()-1;
  int start=0;
  int chance = 1;
  int temp=0;
  while(start + 1 < end ){
  //cout << "start" <<start <<"end" <<end <<endl;
/*  int first = abs(arr[start]-arr[end]);
  int second = abs(arr[start+1]-arr[end]);
  int third = abs(arr[start]-arr[end-1]);
//  cout << first<<" 2nd" << second<<"3rd" << third <<endl;
temp=0;

  if(first < second && first < third || first == second || second == third || third == first )
  {
      if (arr[start] > arr[end]){
        temp=  arr[start];
        start++;
      }
      else if(arr[end] > arr[start]){
        temp = arr[end];
        end--;
      }
      else{
        if(arr[start+1] > arr[end-1])
        {
          temp = arr[end];
          end--;
        }
        else {
          temp=  arr[start];
          start++;
        }
      }

  }
  else if (second < first && second < third )
  {
    temp = arr[start];
    start++;
  }
  else {
    temp = arr[end];
    end--;
  }
  */
if(arr[start+1] > arr[end-1])
{
  temp = arr[end];
  end--;
}



  if(chance == 1) {player1 = player1+temp;chance=0;
  cout << "player1 " << temp<<endl ;
}
  else{player2= player2 + temp ; chance = 1;
cout << "player2 " << temp <<endl ;
  }
  //cout << player1 << "," <<player2<<endl; ;

}
int min , max;
if(arr[start] > arr[end]){
   max = arr[start];min = arr[end];
}
else {
   max = arr[end];min = arr[start];
}
if(chance == 1)
{
  player1 = player1 + max;
  player2 = player2 + min;
}
else {
  player1 = player1 + min;
  player2 = player2 + max;
}
if (player1 >= player2) cout <<"True";
else cout << "false";
  return 0;
}
