#include <stdio.h>
#include <stdlib.h>

long int fib(long int n){

   int n1 = 1;
   int n2 = 1;
   int n3=1;
   for(int i = 2 ;i<= n ; i++ )
   {
        n3 = n1+n2;
        n1 = n2;
        n2=n3;
   }
   return n3;
}

int main()
{
    long int input[] = {1,2,3,10,25,30,999,3000,4096,1000000};
    for(int i =0 ;  i< 9;i++)
    {
        printf("%d -> %d \n" , input[i] , fib(input[i]));
    }
   return 0;
}
