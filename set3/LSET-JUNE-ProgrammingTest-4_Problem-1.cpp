/*
Problem1:													60Marks
Alice likes to shop online. The main reason is that she gets a lot of discounts! There are M online shops from where she purchases her items. The prices of the same item vary in both the shops. She needs to buy N items in all. And each she can buy each item in any one of the shops. All the shops offer certain discounts. If she buys the ith item in one shop, she gets a discount coupon for the i+1th item in the same shop. But if she purchases the i+1th item from a different shop, she cannot use the discount coupon.
For example, if she buys the ith item in Shop j and gets a discount of X rupees. Let the price of i+1th item be Y rupees in shop j and Z rupees in shop k. If she purchases the i+1th item from shop j she can use the discount coupon and hence, will have to pay Y-Xrupees. If she purchases the i+1th item from shop k she cannot use the discount coupon and hence, will have to pay Z rupees.

Note: If the discount given is more than price of the item in the shop, i.e. if Y-X < 0, the item is given free but she does NOT get any money back.

Alice wants to spend as less as possible and wants your help. She starts buying from item 1 and goes on till item N in that order. Your task is simple. Tell her the least amount to spend to get all the N items.
Input:
First line of input contains a single integer T, the number of test cases.

Each test case starts with a line consisting of two space separated integers N & M.
The next N lines consist of M space separated integers each. The jth number on the ithline denotes the price of ith item in the jth shop.

The next N lines consist of M space separated integers each. The jth number on the ithline denotes the value of discount coupon given after purchasing ith item in the jth shop.

Output:
For each test case, output on a separate line the least amount that has to be spent to get all the N items.

Constraints:
1 ≤ T ≤ 10
2 ≤ N, M ≤ 100000
0 ≤ Prices, Discounts ≤ 1000000
1 ≤ T * N * M ≤ 1000000
Example:
Input:
2
2 2
3 4
1 2
1 0
0 1
2 4
1 2 3 4
4 3 2 1
2 3 2 1
1 2 1 1
Output:
3
2
*/

#include<iostream>
using namespace std;
int main(){
  int t;
  std::cin >> t;
  int tn = 0;
  int sol[t];
  int last_shop = -99999;
  while(tn < t){
    int m,n;
    std::cin >> m >> n;
    int prize[n][m];
    int discount[n][m];
    int covered[m];
    for(int i=0;i<n;i++)
    {
      for(int j=0;j < m;j++)

      {
        std::cin >> prize[i][j];
        covered[j]  =0;
      }
    }
    for(int i=0;i<n;i++)
    {
      for(int j=0;j < m;j++) std::cin >> discount[i][j];
    }
    int ans =0;
    //logic
    // j -> items
    for(int i=0;i<n;i++)
    {
      if(i == 0 ){
        //choose least one
        int min = 0;
          for(int j = 1; j<m ;j++)
          {
              if(prize[i][j] < prize[min][j])
                min = j;
          }
          last_shop = min;
          covered[min] = 1;
          ans = prize[i][min];
          std::cout << prize[i][min]<< "is added" << endl  ;
      }
      else
      {
        int min = 9999999;
        int min_index = 0;
        int temp = 0;
        for(int j=0 ; j<m; j++)
        {
          if(!covered[j])
          {
            if(j == last_shop )
            {
              temp  = prize[i][j] - discount[i][j-1] ;
              if (temp < 0)
                temp = 0;
            }
            else
            {
              temp = prize[i][j];
            }
          if( temp  <  min )
              min = temp;
              min_index = i;
          }
        }
        last_shop = min_index;
        covered[min_index] = 1;
        ans =ans + min ;
        std::cout << min <<"is added"  << endl  ;
      }
    }
     sol[tn] = ans ;
     tn++;
   }
   for(int i=0;i<t;i++)
   std::cout << "solution" <<sol[i] << endl ;
  return 0;
}
