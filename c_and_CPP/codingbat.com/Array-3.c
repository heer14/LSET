#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
void main(){
    int n=0;
    while(n != 10){
     system("cls");
    printf("select any one:\n1.maxSpan \n2.fix34\n3.fix45\n4.canBalance \n5.linearIn \n6.squareUp  \n7.seriesUp \n8.maxMirror  \n9.countClumps \n10.exit\n" );
    scanf("%d",&n);
     system("cls");
    switch(n)
    {
        case 1 :maxSpan();break;
        case 2:fix34();break;
        case 3:fix45();break;
        case 4:canBalance();break;
        case 5:linearIn();break;
        case 6:squareUp();break;
        case 7:seriesUp();break;
        case 8:maxMirror();break;
        case 9:countClumps();break;
        case 10:break;
        default:printf("select appropriate number : ");

    }
    printf("press any key to continue :) ");
    getch();
}
}
void countClumps(){
 int t[9][14] = {{1, 2, 2, 3, 4, 4,999},{1, 1, 2, 1, 1,999},{1, 1, 1, 1, 1,999},{1,2,3,999},{2, 2, 1, 1, 1, 2, 1, 1, 2, 2,999},{0, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2,999},{0, 0, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2,999},{0, 0, 0, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2,999},{999}};
    int a[13];
    int max;
    for(int i=0; i < 9 ;i++){
         printf("[");
        int j;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
        }
        printf("] -> ");
        //actual logic
        int fc = 0,cnt=0;;
        for(int k=0;k < j ;k++){
            int temp=0;
            cnt=1;
            int f=1;
            for(int l=k+1 ; l<j;l++)
            {
                int temp =k;
                if(a[temp] == a[l])
                {
                    f=0;
                    k++;
                    cnt++;
                }
                else break;
            }
            if(cnt > 1) fc++;

        }
        (j>0) ? printf("%d \n",fc) : printf("0\n");
    }

}
void maxMirror(){
int t[15][17] = {{1, 2, 3, 8, 9, 3, 2, 1,999},{1, 2,1,4,999},{7, 1, 2, 9, 7, 2, 1,999},{21, 22, 9, 8, 7, 6, 23, 24, 6, 7, 8, 9, 25, 7, 8, 9,999},{1, 2, 1, 20, 21, 1, 2, 1, 2, 23, 24, 2, 1, 2, 1, 25,999},{1, 2, 3, 2, 1,999},{1, 2, 3, 3, 8,999},{1, 2, 7, 8, 1, 7, 2,999},{1, 1, 1,999},{1,999},{999},{9, 1, 1, 4, 2, 1, 1, 1,999},{5, 9, 9, 4, 5, 4, 9, 9, 2,999},{5, 9, 9, 6, 5, 4, 9, 9, 2,999},{5, 9, 1, 6, 5, 4, 1, 9, 5,999}};
    int a[7];

    int max;
    for(int i=0; i < 15 ;i++)
    {
         printf("[");
        int j;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
        }
        printf("] -> ");
        //actual logic
        max= -1;
        int cnt;
        for(int k=0;k < j ;k++){
            for(int l=k ;l<j;l++){
                cnt=0;
                if(a[k] == a[l])
                {
                    int s=k+1,e=l-1;
                    cnt =  1;
                    while(s<j && e >=0 && a[s] == a[e])
                    {
                        s++;e--;
                        cnt++;

                    }
                    if(cnt > max) max = cnt;
                }
            }
        }
        (j>0) ? printf("%d \n",max) : printf("0\n");
    }
}
void seriesUp(){
    int tc[6] = {3,4,2,1,0,6};
    int n,n1=0;
    int *a;
    for(int i=0; i<6;i++){
    n=tc[i];
    n1=0;
    //actual logic
    while(n > 0)
    {
        n1 = n1 + n;
        n--;
    }
    printf("%d ",n1);
    a= (int *)malloc(n1*sizeof(int));
    printf("%d -> [ ",tc[i]);
    int j=0;
       for(int lc = 1; lc <=tc[i];lc++)
       {
           for(int i1=1;i1<=lc;i1++)
           {
               a[j] = i1;
               j++;

           }
       }
    for(int j= 0;j<n1;j++) printf("%d , ",a[j]);
    printf("]\n");
}
}
void squareUp(){
int tc[6] = {3,2,4,1,0,6};
int n;
int *a;
for(int i=0; i<6;i++){
    n= tc[i]*tc[i];
    a= (int *)malloc(n*sizeof(int));
    printf("%d -> [ ",tc[i]);
    //actual logic
    for(int j = 0 ; j< n ;j++)
    {
        a[j] = 0;
        for(int k=1 ;k<= tc[i] ; k++)
        {
               if(tc[i] * (tc[i]-1) == j ) a[j] = tc[i];
               if(((j+k) % tc[i]) == 0 && j > (tc[i]*(k-1)) )
               {
                   a[j] = k;
               }
        }

    }
    for(int j= 0;j<n;j++) printf("%d , ",a[j]);
    printf("]\n");
    }
}
void linearIn(){
   int out[13][8] = {{1,2,4,6,999},{1,2,4,6,999},{1,2,4,4,6,999},{2,2,4,4,6,6,999},{2,2,2,2,2,999},{2,2,2,2,2,999},{2,2,2,2,4,999},{1, 2, 3,999},{1, 2, 3,999},{1, 2, 3,999},{-1, 0, 3, 3, 3, 10, 12,999},{-1, 0, 3, 3, 3, 10, 12,999},{-1, 0, 3, 3, 3, 10, 12,999}};
   int in[13][8] = {{2,4,999},{2,3,4,999},{2,4,999},{2,4,999},{2,2,999},{2,4,999},{2, 4,999},{2,999},{-1,999},{999},{-1, 0, 3, 12,999},{0, 3, 12, 14,999},{-1, 10, 11,999}};
   int a1[8],a2[8];
   int n1=0,n2=0;
   for(int i=0;i<13;i++)
   {
       for(n1=0;out[i][n1] != 999 ;n1++)
       {
           a1[n1] = out[i][n1];
       }
       for(n2=0;in[i][n2] != 999 ;n2++)
       {
           a2[n2] = in[i][n2];
       }
        //actual logic
        int f=0;
        for(int j = 0; j< n2 ;j++)
        {
            int f1=1;

            for(int i1 = 0; i1 < n1 ; i1++)
            {
                if(a1[i1] == a2[j] ){

                        f1=0;break;}
            }
            if(f1 == 1)
            {f=1; break;
            }
        }
        printf("%s \n",(f==1) ? "False" : "True" );

   }

}
void canBalance(){
 int t[11][8] = {{1, 1, 1, 2, 1,999},{2, 1, 1, 2, 1,999},{10,10,999},{10, 0, 1, -1, 10,999},{1,1,1,1,4,999},{2,1,1,1,4,999},{2, 3, 4, 1, 2,999},{1, 2, 3, 1, 0, 2, 3,999},{1, 2, 3, 1, 0, 1, 3,999},{1,999},{1, 1, 1, 2, 1,999}};
    int a[7];
    for(int i=0; i < 11 ;i++)
    {
         printf("[");
        int j;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
        }
        printf("] -> ");
        //actual logic
        int f=1;
        int sum1 = 0,sum2=0;
       for(int k=0; k < j ; k++)
       {
         sum1 = sum1 + a[k];
         sum2 = 0;
         for(int l = k+1 ;l <j ; l++)
         {
             sum2 = sum2 + a[l];
         }
         if(sum1==sum2){
            f=0;break;
         }
       }


    printf("%s \n",(f==0) ? "True" : "False");
}
}
void fix45(){
int t[18][10] = {{5, 4, 9, 4, 9, 5,999},{1,4,1,5,999},{1, 4, 1, 5, 5, 4, 1,999},{4, 9, 4, 9, 5, 5, 4, 9, 5,999},{5, 5, 4, 1, 4, 1,999},{4, 2, 2, 5,999},{4, 2, 4, 2, 5, 5,999},{4, 2, 4, 5, 5,999},{1,1,1,999},{4,5,999},{5,4,1,999},{999},{5,4,5,4,1,999},{4, 5, 4, 1, 5,999},{3,4,5,999},{4,1,5,999},{5,4,1,999},{2,4,2,5,999}};
    int a[8];
     for(int i=0; i < 18 ;i++)
    {
         printf("[");
        int j,n;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
            if(a[j] == 4) n++;
        }
        printf("] -> [ ");
        //actual logic
        int Fives[n],index=0;
        for(int k=0;index <= n ;k++)
        {
            if(a[k] == 5 ){Fives[index] = k ;index++;}

        }
        index=0;
        for(int k=0;k<j-1;k++)
        {
            if(a[k] == 4 && a[k+1] != 5){
               int temp = a[k+1];
               a[k+1] = a[Fives[index]];
               a[Fives[index]] = temp;
               index++;
               k++;
            }
        }
        for(int k=0;k<j;k++) printf("%d ,",a[k]);
    printf("]\n");
    }
}
void fix34(){
 int t[14][13] = {{1, 3, 1, 4,999},{1, 3, 1, 4, 4, 3, 1,999},{3, 2, 2, 4,999},{3, 2, 3, 2, 4, 4,999},{2, 3, 2, 3, 2, 4, 4,999},{5, 3, 5, 4, 5, 4, 5, 4, 3, 5, 3, 5,999},{3, 1, 4,999},{3,4,1,999},{1,1,1,999},{1,999},{999},{7, 3, 7, 7, 4,999},{3, 1, 4, 3, 1, 4,999},{3, 1, 1, 3, 4, 4,999}};
    int a[8],a2[12];
     for(int i=0; i < 14 ;i++)
    {
         printf("[");
        int j,n;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
            if(a[j] == 3) n++;
        }
        printf("] -> [ ");
        //actual logic
        int Fours[n],index=0;
        for(int k=0;index <= n ;k++)
        {
            if(a[k] == 4 ){Fours[index] = k ;index++;}

        }
        index=0;
        for(int k=0;k<j-1;k++)
        {
            if(a[k] == 3 && a[k+1] != 4){
               int temp = a[k+1];
               a[k+1] = a[Fours[index]];
               a[Fours[index]] = temp;
               index++;
               k++;
            }
        }
        for(int k=0;k<j;k++) printf("%d ,",a[k]);
    printf("]\n");
    }
}
void maxSpan(){
    int t[10][8] = {{1, 2, 1, 1, 3,999},{1, 4, 2, 1, 4, 1, 4,999},{1, 4, 2, 1, 4, 4, 4,999},{3,3,3,999},{3,9,3,999},{3,9,9,999},{3,9,999},{3,3,999},{999},{1,999}};
    int a[7];

    int max;
    for(int i=0; i < 10 ;i++)
    {
         printf("[");
        int j;
        for(j=0;t[i][j] != 999 ; j++)
        {
            printf("%d , ",t[i][j]);
            a[j] = t[i][j];
        }
        printf("] -> ");
        //actual logic
        max= -1;
        for(int k=0;k < j ;k++){

            for(int l=j-1 ; l> k; l--){
                if(a[k] == a[l])
                {
                    if(max<(l-k+1)) max = l-k+1 ;
                }
            }
        }
        if(max == -1) max=1;
        (j>0) ? printf("%d \n",max) : printf("0\n");
    }

}
