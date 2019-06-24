#include <stdio.h>
#include <stdlib.h>

void calculate(int array[] , int n){

    int i=n;
    int start = 0;
    int end = n-1;
    int player1 = 1,player2=0;
    int score1 = 0, score2=0;
    while( start!= end ){
        if(player1)
        {
            if(array[start] > array[end])
            {
                score1 = score1+array[start];
                start++;
            }
            else{
               score1 = score1 + array[end];
                end--;
            }
            player1 = 0;
            player2= 1;
        }
        else{
            if(array[start] > array[end])
            {
                score2 = score2+array[start];
                start++;
            }
            else{
               score2 = score2 + array[end];
                end--;
            }
            player1 = 1;
            player2= 0;
        }
    }
    //printf("%d %d\n " , score1 , score2);
        if(score1 >= score2 )
            printf("true");
        else printf("false");

}


int main()
{
    int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int arr2[] = {1,2,3,4,5,6,7,789,8,9,10000000,11,12,13,14,159,16,17,18,19,20};
    int arr3[] = {1,2,300000,14,515,6,789};
    int arr4[] = {10000000 ,2,369,14,459,6,70} ;
    calculate(arr1 , 20);
        calculate(arr2 , 20);
            calculate(arr3 , 7);
                calculate(arr4 , 7);


    return 0;
}
