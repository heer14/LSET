#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

void  sleepIn(int weekdays , int vacation){
    if(!weekdays || vacation)
        printf("True/n");
    else
        printf("False/n");

}
void main()
{
    int n=0;
    while(n != 30){
     system("cls");
    printf("select any one:\n1. sleepIn \n2. bigDiff\n3. centeredAverage\n4. sum13\n5. sum28\n6.more14 \n7. no14\n8.isEverywhere \n9.either24 \n10.matchUp \n11.has77 \n12. has12 \n13. modThree \n14.haveThree\n15.twoTwo \n16. sameEnds \n17.tripleUp \n18.shiftLeft\n19.tenRun\n20.pre4 \n21. post4\n22.notAlone \n23.zeroFront\n24.withoutTen \n25.zeroMax \n26.evenOdd \n27.fizzBuzz\n28. sum67 \n29.lucky13 \n30. exit\n" );
    scanf("%d",&n);
     system("cls");
    switch(n)
    {
        case 1 : sleepIn(0, 0);
        sleepIn(1, 0) ;
        sleepIn(0, 1) ;
        sleepIn(1, 1) ;
        break;
        case 2: bigDiff();break;
        case 3: centeredAverage();break;
        case 4:  sum13 ();break;
        case 5: sum28();break;
        case 6: more14();break;
        case 7:  no14();break;
        case 8: isEverywhere();break;
        case 9:either24();break;
        case 10:matchUp();break;
        case 11: has77();break;
        case 12: has12 ();break;
        case 13:modThree();break;
        case 14:haveThree();break;
        case 15:twoTwo();break;
        case 16: sameEnds();break;
        case 17: tripleUp();break;
        case 18: shiftLeft();break;
        case 19:  tenRun();break;
        case 20:  pre4();break;
        case 21:  post4();break;
        case 22: notAlone();break;
        case 23:zeroFront();break;
        case 24:withoutTen();break;
        case 25: zeroMax();break;
        case 26: evenOdd();break;
        case 27:fizzBuzz();break;
        case 28: sum67();break;
        case 29:lucky13();break;
        case 30:break;
        default:printf("select appropriate number : ");

    }
    printf("press any key to continue :) ");
    getch();
}
}
//1,1,50,15,30,1000,99,14
//

void lucky13(){
 int testCases[12][5] = {{0,2,4,999},{1,2,3,999},{1,3,4,999},{2,7,2,8,999},{2,7,1,8,999},{3,7,2,8,999},{2,7,2,1,999},{1,2,999},{2,2,999},{2,999},{3,999},{ 999}};
 for (int i=0;i<12;i++)
{
    printf("[");
    int cnt=0,cnt1=0;
    int a[8];
    int j;
    for(j=0; testCases[i][j] != 999 ; j++)
    {
        printf("%d , ", testCases[i][j]);
        a[j] = testCases[i][j];
    }
    int f=0;
    for(int k=0;k<j;k++)
    {
        if(a[k] == 3 || a[k] == 1){
            f=1;
            break;
        }
    }

     printf("]->%s \n" ,(f==0 )?"True":"False");
}


}

void  sum67(){
    int testcases[14][12]={{1,2,2,999},{1, 2, 2, 6, 99, 99, 7,999},{1,1,6,7,2,999},{1, 6, 2, 2, 7, 1, 6, 99, 99, 7,999},{1, 6, 2, 6, 2, 7, 1, 6, 99, 99, 7,999},{2, 7, 6, 2, 6, 7, 2, 7,999},{2, 7, 6, 2, 6, 2, 7,999},{1, 6, 7, 7,999},{6, 7, 1, 6, 7, 7,999},{6, 8, 1, 6, 7,999},{999},{6,7,11,999},{11,6,7,11,999},{2,2,6,7,7,999}};
    for(int i=0;i<14;i++)
    {
        printf("[ ");
        int *a = (int *)malloc(12*sizeof(int));
        int j;
        for(j=0;testcases[i][j] != 999 ;j++)
        {
            a[j]= testcases[i][j];
            printf("%d ,",testcases[i][j]);
        }
        printf(" ] -> ");
        int sum = 0;
        for(int k=0;k<j;k++)
        {
            if(a[k] == 6)
            {
                while(a[k] != 7) k++;
            }
            else
            {
                sum  = sum + a[k];
            }
        }
        printf("%d\n",sum);

    }


}
void fizzBuzz(){
int s[12] = {1,1,1,1,1,1,50,15,30,1000,99,14};
int e[12] = {6,8,11,16,4,2,56,17,36,1006,102,20};
char string[999][8];

for(int i=0;i<12;i++)
{
    printf("[%d ,%d] -> [",s[i],e[i]);
    for(int j=s[i]; j<e[i]; j++)
    {
        if((j % 3 == 0) && (j% 5==0)) strcpy(string[j], "FizzBuzz");
        else if (j % 3 == 0) strcpy(string[j], "Fizz");
        else if (j % 5 == 0) strcpy(string[j], "Buzz");
        else itoa(j, string[j],10) ;
        printf("%s , ",string[j]);
    }
    printf("]\n");

}
}

void evenOdd(){
    int testCases[9][8] ={{1, 0, 1, 0, 0, 1, 1,999},{3,3,2,999},{2,2,2,999},{3,2,2,999},{1,1,0,1,0,999},{1,999},{1,2,999},{2,1,999},{999}};

    for (int i=0;i<9;i++){
        printf("[ ");
        int a[999];
        int j,k,cnt=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);
        }
     printf("]-> [ ");
     int a2[j];
     int n=0;
     for(int k=0;k<j;k++)
     {
        if(a[k] % 2 == 0){
            a2[n] = a[k];
             printf("%d ,",a2[n]);
            n++;
        }

     }
      for(int k=0;k<j;k++)
     {
        if(a[k] % 2 != 0){
            a2[n] = a[k];
            printf("%d ,",a2[n]);
            n++;
        }

     }
     printf("]\n");
     }

}

void zeroMax(){
    int testCases[12][7] ={{0,5,0,3,999},{0,4,0,3,999},{0,1,0,999},{0,1,5,999},{0,2,0,999},{1,999},{0,999},{999},{7,0,4,3,0,2,999},{7,0,4,3,0,1,999},{7,0,4,3,0,0,999},{7,0,1,0,0,7,999}};

    for (int i=0;i<12;i++){
        printf("[ ");
        int a[999];
        int j,k,cnt=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
     printf("]-> [ ");
     cnt = 0;
     int max;
     for(int     k=0;k<j;k++)
     {
        if(a[k] == 0){
            max= -1;
            for(int h=k+1 ; h<j ; h++)
            {
                if( (a[h]!=0) && (a[h] % 2 != 0) && (a[h] > max)){
                    max=a[h];
                    printf("%d ,",a[h]);
                }
            }
            if(max == -1 ) printf("%d ,",a[k]);
        }
        else printf("%d ,",a[k]);
    }
     printf(" ]\n");
     }


}

void withoutTen(){
    int testCases[10][7] ={{1, 10, 10, 2,999},{10,2,10,999},{1,99,10,999},{10,13,10,14,999},{10,13,10,14,10,999},{10,10,3,999},{1,999},{13,1,999},{10,999},{999}};

    for (int i=0;i<10;i++){
        printf("[ ");
        int a[999];
        int j,k,cnt=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
     printf("]-> [ ");
     cnt = 0;
     for(int k=0;k<j;k++)
     {
        if(a[k] != 10) printf("%d ,",a[k]);
        else cnt++;
     }
     for(int k=0;k<cnt;k++)
     {
        printf("0 ,");
     }
     printf("]\n");
     }

}


void zeroFront(){
int testCases[11][7] ={{1, 0, 0, 1,999},{0, 1, 1, 0, 1,999},{1,0,999},{0,1,999},{1,1,1,0,999},{2,2,2,2,999},{0,0,1,0,999},{-1,0,0,-1,0,999},{0,-3,0,-3,999},{999},{9,9,0,9,0,9,999}};

    for (int i=0;i<11;i++){
        printf("[ ");
        int a[999];
        int j,k,cnt=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);
            if(a[j] == 0) cnt++;

        }
     printf("]-> [ ");
     for(int k=0;k<cnt;k++)
     {
        printf("0 ,");
     }
     for(int k=0;k<j;k++)
     {
        if(a[k] != 0) printf("%d ,",a[k]);
     }
     printf("]\n");
     }

}

void notAlone(){
int t1[10][7] ={{1,2,3,999},{1,2,3,2,5,2,999},{3,4,999},{3,3,999},{1,3,1,2,999},{3,999},{999},{7,1,6,999},{1, 1, 1,999},{1, 1, 1,2,999}};
    int t2[10] = {2,2,3,3,1,3,3,1,1,1};
    int a[999];
    for (int i=0;i<10;i++)
    {
         printf("[ ");
         int j=0;
         for(j=0; t1[i][j] !=999; j++)
        {
            a[j] = t1[i][j];
            printf("%d , ", a[j]);

        }
        if(j>0){
            printf(" (%d) ]-> [%d, " , t2[i],a[0]);
            for(int i1=1; i1<j-1;i1++)
            {
              if(a[i1] == t2[i])
              {
                    if( (a[i1-1] != a[i1]) && (a[i1+1] != a[i1]) )
                       printf("%d, ", a[i1-1] > a[i1+1] ? a[i1-1] : a[i1+1]) ;
                    else{
                        printf("%d,",a[i1]);continue;
                    }

              }
              else printf("%d,",a[i1]);
            }
            printf("%d]\n",a[j-1]);
        }
        else printf("]->[]\n");
    }
}

void post4()
{
int testCases[10][7] ={{2,4,1,2,999},{4,1,4,2,999},{4,4,1,2,3,999},{4,2,999},{4,4,3,999},{4,4,999},{4,999},{2,4,1,4,3,2,999},{4,1,4,2,2,2,999},{3,4,3,2,999}};

    for (int i=0;i<10;i++){
        printf("[ ");
        int a[999];
        int j,k;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
     printf("]-> [ ");
     for(k=j;k>=0;k--)
     {
       if(a[k] == 4) break;
     }
     for(int i1=k+1;i1 < j;i1++)
     {
     printf("%d , ",a[i1]);
     }
     printf("]\n");
     }
}

void pre4(){
int testCases[10][7] ={{1,2,4,1,999},{3,1,4,999},{1,4,4,999},{1,4,4,2,999},{1,3,4,2,4,999},{4,4,999},{3,3,4,999},{1,2,1,4,999},{2,1,4,2,999},{2,1,2,1,4,2,999}};

    for (int i=0;i<10;i++){
        printf("[ ");
        int a[999];
        int j;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
     printf("]-> [ ");
     int a2[j];
     for(int k=0;k<j;k++)
     {
        if(a[k] != 4 ) a2[k] = a[k];
        else break;
        printf("%d , " , a2[k]);
     }
     printf("]\n");
     }
}
void  tenRun(){
int testCases[11][11] ={{2, 10, 3, 4, 20, 5,999},{10, 1, 20, 2,999},{10, 1, 9, 20,999},{1, 2, 50, 1,999},{1, 20, 50, 1,999},{10,10,999},{10,2,999},{0,2,999},{1,2,999},{1,999},{999}};

    for (int i=0;i<11;i++){
        printf("[ ");
        int a[999];
        int j;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
     printf("]-> [ ");
     int index =-1;
     int a2[j];
     for(int k=0;k<j;k++)
     {
        if(a[k]% 10 == 0 ){
            a2[k] = a[k];
            index = k;}
        else if(index !=-1){
            a2[k] = a[index];
        }
        else a2[k] = a[k];
        printf("%d , " , a2[k]);
     }
     printf("]\n");
     }
}
void shiftLeft(){
int testCases[7][11] ={{6, 2, 5, 3,999},{1,2,999},{1,999},{999},{1,1,2,2,4,999},{1,1,1,999},{1,2,3,999}};

    for (int i=0;i<7;i++){
        printf("[ ");
        int a[999];
        int j,f=1;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
        int a2[j];
     printf("]-> [ ");
     for(int k=0;k<j-1;k++)
     {
        a2[k] = a[k+1];
        printf("%d , " , a2[k]);
     }
     if(j>0){a2[j] = a[0];
     printf("%d ]\n",a2[j]);
     }
     else{
        printf("]\n");
     }

}
}

void tripleUp(){
    int testCases[12][11] ={{1, 4, 5, 6, 2,999},{1,2,3,999},{1,2,4,999},{1, 2, 4, 5, 7, 6, 5, 6, 7, 6,999},{1, 2, 4, 5, 7, 6, 5, 7, 7, 6,999},{1,2,999},{1,999},{999},{10, 9, 8, -100, -99, -98, 100,999},{10, 9, 8, -100, -99, 99, 100,999},{-100, -99, -99, 100, 101, 102,999},{2, 3, 5, 6, 8, 9, 2, 3,999}};

    for (int i=0;i<12;i++){
        printf("[ ");
        int a[999];
        int j,f=1;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
        int cnt=0;
        for(int i=0;i<j-2;i++)
        {
          if(a[i+1]== a[i]+1){
            if(a[i+2] == a[i]+2){
                f=0;break;
            }
          }
        }
     printf("]->%s \n" , ((f==0)?"True":"False"));

}
}

void  sameEnds(){
int t1[14][10] ={{5, 6, 45, 99, 13, 5, 6,999},{5, 6, 45, 99, 13, 5, 6,999},{5, 6, 45, 99, 13, 5, 6,999},{1, 2, 5, 2, 1,999},{1, 2, 5, 2, 1,999},{1, 2, 5, 2, 1,999},{1, 2, 5, 2, 1,999},{1, 1, 1,999},{1, 1, 1,999},{1, 1, 1,999},{1, 1, 1,999},{1,999},{999},{4,2,4,5,999}};
    int t2[14] = {1,2,6, 2, 5, 33,1,2,0,5,0,1,2,3,1,0,1};
    int f=0;
    int a[999];
    for (int i=0;i<14;i++)
    {
         printf("[ ");
         int j;
         f=0;
         for(j=0; t1[i][j] !=999; j++)
        {
            a[j] = t1[i][j];
            printf("%d , ", a[j]);

        }
        for(int i1=0;i1<t2[i];i1++)
        {
            //printf("\n%d and %d\n ",a[i1] ,a[j-t2[i]+i1] );
            if(a[i1] != a[j-t2[i]+i1])
            {
            f = 1;
            break;
            }

        }
    printf(" (%d) ]->%s \n" , t2[i] , ((f==0)?"True":"False"));
    }
}

void  twoTwo(){
      int testCases[17][9] ={{4,2,2,3,999},{2,2,4,999},{2,2,4,2,999},{1,3,4,999},{1,2,2,3,4,999},{1,2,3,4,999},{2,2,999},{2,2,7,999},{2,2,7,2,1,999},{4,2,2,2,999},{2,2,2,999},{1,2,999},{2,999},{1,999},{999},{5,2,2,3,999},{2,2,5,2,999}};

    for (int i=0;i<17;i++){
        printf("[ ");
        int a[999];
        int j,f=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
        int cnt=0;
        for(int i=0;i<j;i++)
        {
          if(a[i] == 2){
            if((a[i+1]==2 && i+1 <= j) || (i-1 > 0 && a[i-1] == 2)){
                i++;
            }
            else{
                f=1;
                break;
            }
          }
        }
     printf("]->%s \n" , ((f==0)?"True":"False"));

}
}

void haveThree(){
       int testCases[12][9] ={{3,1,3,1,3,999},{3,1,3,3,999},{3,4,3,3,4,999},{1,3,1,3,1,2,999},{1,3,1,3,1,3,999},{1,3,3,1,3,999},{1,3,1,3,1,3,4,3,999},{3,4,3,4,3,4,4,999},{3,3,3,999},{1,3,999},{3,999},{1,999}};

    for (int i=0;i<12;i++){
        printf("[ ");
        int a[999];
        int j,f=0;
        for(j=0; testCases[i][j] !=999; j++)
        {
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
        int cnt=0;
        int index=-1;
        for(int i=0;i<j;i++)
        {
           if(a[i] == 3)
           {
             if(cnt == 0) {
                index = i;
                cnt++;
             }
             else{
                if(i- index > 1){
                cnt++;
                index=i;
                }
                else cnt=0;
             }
             if(cnt == 3){
                f=1;
             }
            }
           }
     printf("]->%s \n" , ((f==1 && cnt == 3)?"True":"False"));
    }
}

void modThree(){
   int testCases[12][9] ={{2,1,3,5,999},{2,1,2,5,999},{2,4,2,5,999},{1,2,1,2,1,999},{9,9,9,999},{1,2,1,999},{1,2,999},{1,999},{999},{9,7,2,9,999},{9,7,2,9,2,2,999},{9,7,2,9,2,2,6,999}};
    for (int i=0;i<12;i++){
        printf("[ ");
        int a[999];
        int j,f=0;
        for(j=0; testCases[i][j] !=999; j++){
            a[j] = testCases[i][j];
            printf("%d , ", a[j]);

        }
        int cnt1=0,cnt=0;
        f=0;
        for(int i=0;i<j;i++)
        {
            if(a[i]%2 == 0)
            {
                cnt1++;
                if(cnt1 == 3)
                {
                    f=1;
                    break;
                }
                cnt = 0;
            }
            else if(a[i]%2 != 0){
                cnt++;
                if(cnt == 3)
                {
                    f=1;
                    break;
                }
                cnt1 =0 ;
            }
        }
     printf("]->%s \n" , ((f==1)?"True":"False"));
    }
}

void  has12(){
    int testCases[17][7] ={{1,3,2,999},{3,1,2,999},{3,1,4,5,2,999},{3,1,4,5,6,999},{3,1,4,1,6,2,999},{2,1,4,1,6,2,999},{2,1,4,1,6,999},{1,999},{2,1,3,999},{2,1,3,2,999},{2,999},{3,2,999},{3,1,3,2,999},{3,5,9,999},{3,5,1,999},{3,2,1,999},{1,2,999}};
    for (int i=0;i<17;i++){
        printf("[ ");
        int f=0,f1=0;
        for(int j=0; testCases[i][j] !=999; j++)
        {

            printf("%d , ", testCases[i][j]);
            if(testCases[i][j] == 1)
            {
                f=1;
            }
            if(f==1 && testCases[i][j] == 2)
            {
                f1=1;
                break;
            }
        }
     printf("]->%s \n" , ((f1==1)?"True":"False"));
    }
}

void has77(){
    int testCases[13][7] ={{1,7,7,999},{1,7,1,7,999},{1,7,1,1,7,999},{7,7,1,1,7,999},{2,7,2,2,7,2,999},{2,7,2,2,7,7,999},{7,2,6,2,2,7,999},{7,7,7,999},{7,1,7,999},{7,1,1,999},{1,2,999},{1,7,999},{7,999}};
     for (int i=0;i<13;i++)
    {
        printf("[ ");
        int f=0;
        for(int j=0; testCases[i][j] !=999; j++)
        {

            printf("%d , ", testCases[i][j]);
            if(testCases[i][j+1]!=999 && testCases[i][j] ==7 && (testCases[i][j+1]==7 || testCases[i][j+2] == 7 ) )
            {
                f=1;
            }


        }
         printf("]->%s \n" , ((f==1)?"True":"False"));
    }
}

void matchUp(){
    int t1[11][4] ={{1,2,3,999},{1,2,3,999},{1,2,3,999},{5,3,999},{5,3,999},{5,3,999},{5,3,999},{5,3,999},{5,3,999},{4,999},{4,999}};
    int t2[11][3] = {{2,3,10},{2,3,5},{2,3,3},{5,5},{4,4},{3,3},{2,2},{1,1},{0,0},{4},{5}};
    int cnt;
    for (int i=0;i<11;i++)
    {
        cnt =0;
        for(int j=0; t1[i][j] !=999; j++)
        {

           if((t1[i][j] != t2[i][j]) && (abs(t1[i][j] - t2[i][j] ) <= 2)) cnt++;

        }
         printf(" %d \n" , cnt);
    }
}

void either24(){
    int testCases[14][9] = {{1, 2,2,999},{4,4,1,999},{4,4,1,2,2,999},{1,2,3,4,999},{3,5,9,999},{1,2,3,4,4,999},{2,2,3,4,999},{1,2,3,2,2,4,999},{1,2,3,2,2,4,4,999},{1,2,999},{2,2,999},{4,4,999},{2,999},{999}};
     for (int i=0;i<14;i++)
    {
        printf("[ ");
        int f,f1;
        f=0;f1=0;
        for(int j=0; testCases[i][j] !=999; j++)
        {

            printf("%d , ", testCases[i][j]);
            if(f!=1 && testCases[i][j]==2  && testCases[i][j+1] == 2)
            {
               f=1;
            }
            if(f1!=1 &&  testCases[i][j]==4  && testCases[i][j+1] == 4)
            {
                f1=1;
            }

        }
         printf("]->%s \n" , ((f!=f1 )?"True":"False"));
    }
}

void isEverywhere(){

    int testCases[16][9] = {{1, 2, 1, 3,999},{1, 2, 1, 3,999},{1, 2, 1, 3,4,999},{2,1,2,1,999},{2,1,2,1,999},{2,1,2,3,1,999},{3,1,999},{3,1,999},{3,999},{999},{1,2,1,2,3,2,5,999},{1,2,1,1,1,2,999},{2, 1, 2, 1, 1, 2,999},{2, 1, 2, 2, 2, 1, 1, 2, 999},{2, 1, 2, 2, 2, 1, 2, 1,999},{2, 1, 2, 1, 2,999}};
     int nos[16] = {1,2,1,1,2,2,3,2,1,1,2,2,2,2,2,2};
     for (int i=0;i<16;i++)
    {
        printf("[%d , ",testCases[i][0]!= 999 ? testCases[i][0]: 0 );
       int f=0,j;
        for(j=1; testCases[i][j] !=999 && testCases[i][j-1]!=999 ; j++)
        {
            printf("%d , ", testCases[i][j]);
            if(testCases[i][j] != nos[i] && testCases[i][j-1] != nos[i])
            {
               f=1;
               break;
            }

        }

         printf("],%d->%s \n" , nos[i],(f==0)?"True":"False");
    }
}

void   no14(){
   int testCases[][8] = {{1,2,3,999},{1,2,3,4,999},{2,3,4,999},{1,1,4,4,999},{2,2,4,4,999},{2,3,4,1,999},{2,1,1,999},{1,4,999},{2,999},{2,1,999},{1,999},{4, 999},{999},{1,1,1,1,999},{9,4,4,4,1,999},{4,2,3,1,999},{4,2,3,5,999},{4,4,2,999},{1,4,4,999}};
 for (int i=0;i<19;i++)
{
    printf("[");
    int cnt=0,cnt1=0;
    for(int j=0; testCases[i][j] != 999 ; j++)
    {

        printf("%d , ", testCases[i][j]);
        if(testCases[i][j] == 1) cnt++;
        else if(testCases[i][j] == 4) cnt1++;
    }

     printf("]->%s \n" ,(cnt==0|| cnt1==0 )?"True":"False");
}
}

void more14(){
int testCases[][8] = {{1, 4, 1,999},{1, 4, 1,4,999},{1,1,999},{1,1,6,999},{1,999},{1,4,999},{6,1,1,999},{1, 6, 4,999},{1,1,4,4,1,999},{1,1,6,4,4,1,999},{999},{4,1,4,6,999},{4,1,4,6,1,999},{1,4,1,4,1,6,999}};

for (int i=0;i<14;i++)
{
    printf("[");
    int cnt=0,cnt1=0;
    for(int j=0; testCases[i][j] != 999 ; j++)
    {

        printf("%d , ", testCases[i][j]);
        if(testCases[i][j] == 1) cnt++;
        else if(testCases[i][j] == 4) cnt1++;
    }

     printf("]->%s \n" ,cnt>cnt1?"True":"False");
}
}

void sum28(){

    int testCases[][8] = {{2, 3, 2, 2, 4, 2,999},{2, 3, 2, 2, 4, 2,2 ,999},{1, 2, 3, 4,999},{2, 2, 2, 2,999},{1, 2, 2, 2, 2, 4,999},{999},{2,999},{8,999},{2, 2, 2,999},{2,2,2,2,999},{1, 2, 2, 1, 2, 2,999},{5, 2, 2, 2, 4, 2,999}} ;
for (int i=0;i<12;i++)
{
    printf("[");
    int cnt=0;
    for(int j=0; testCases[i][j] != 999 ; j++)
    {

        printf("%d , ", testCases[i][j]);
        if(testCases[i][j] == 2) cnt++;
    }

     printf("]->%s \n" ,cnt==4?"True":"False");
}
}

void sum13(){
int testCases[][8] = {{1, 2, 2, 1,999},{1,1,999},{1, 2, 2, 1, 13,999},{1, 2, 13, 2, 1, 13,999},{13, 1, 2, 13, 2, 1, 13,999},{999},{13,999},{13,13,999},{13,0,13,999},{13,1,13,999},{5,7,2,999},{5,13,2,999},{0,999},{13,0,999}};
for (int i=0;i<14;i++)
{
    printf("[");
    int sum=0;
    int f=0;
    for(int j=0; testCases[i][j] != 999 ; j++)
    {
    printf("%d , ", testCases[i][j]);
    if(testCases[i][j] != 13 && f==0){
    sum = sum + testCases[i][j];
    }
    else if(testCases[i][j] == 13 )
    f=1;
    else
    f=0;
    }
   printf("]-> %d\n",sum);
    }
}

void centeredAverage(){
    int testCases[16][8] = {{1,2,3,4,100,999},{1,1,5,5,10,8,7,999},{-10,-4,-2,-4,-2,0,999},{5, 3, 4, 6, 2,999},{5, 3, 4, 0, 100,999},{100, 0, 5, 3, 4,999},{4, 0, 100,999},{0, 2, 3, 4, 100,999},{1, 1, 100,999},{7, 7, 7,999},{1, 7, 8,999},{1, 1, 99, 99,999},{1000, 0, 1, 99,999},{4, 4, 4, 4, 5,999},{4, 4, 4, 1, 5,999},{6, 4, 8, 12, 3,999} } ;
for (int i=0;i<16;i++)
{
    printf("[");
    int min = 999;
    int max = -1;
    int j;
    int array[8];
    for(j=0; testCases[i][j] != 999 ; j++)
    {

        printf("%d , ", testCases[i][j]);
        array[j] = testCases[i][j];

    }
    // j= number of actual elements
    for(int i=0;i<j;i++)
    {
        for(int k=i;k<j;k++){
            if(array[i] > array[k])
            {
                int temp=array[i];
                array[i] = array[k];
                array[k] = temp;
            }
         }
    }
    int sum=0;
     for(int i=1;i<j-1;i++)
     {
        sum=sum+array[i];
     }
     printf("]->%f \n" , (float )(sum/(j-2)));
}
}

void bigDiff(){
int testCases[][8] = {{10,3,5,6,999},{7,2,10,9,999},{2,10,7,2,999},{2,10,999},{10,2,999},{10,0,999},{2,3,999},{2,2,999},{2,999},{5,1,6,1,9,9,999},{7,6,8,5,999},{7,7,6,8,5,5,6,999}};
for (int i=0;i<12;i++)
{
    printf("[");
    int min = 999;
    int max = -1;
    for(int j=0; testCases[i][j] != 999 ; j++)
    {

        printf("%d , ", testCases[i][j]);
        if(testCases[i][j] <  min ) min = testCases[i][j];
        if(testCases[i][j] > max ) max = testCases[i][j];
    }
   printf("]-> %d\n",max-min);
    }
}
