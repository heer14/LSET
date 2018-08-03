
#include<stdio.h>
#include<conio.h>
#include<math.h>
void main()
{
    int n,i,j,sum1=0,sum2=0;
    int **array ;
    scanf("%d" , &n);
    array = (int **)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        *array[i] = (int *)malloc(n*sizeof(int));
    for(i =0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&array[i][j]);
        }
    }
    for(i=0,j=0;i<n,j<n;i++,j++)
    {
       sum1 = sum1 + array[i][j];
    }
    for(i=n,j=n;i>=0,j>=0;i--,j--)
    {
     sum2 = sum2 + array[i][j];
    }
    printf("%d",abs(sum1-sum2));
}
