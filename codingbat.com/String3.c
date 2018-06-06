#include<conio.h>
#include<stdio.h>
#include<ctype.h>
void main(){
    int n=0;
    while(n != 8){
     system("cls");
    printf("select any one:\n1.countYZ  \n2.withoutString \n3.equalIsNot \n4.gHappy \n5.sumDigits  \n6. mirrorEnds   \n7.maxBlock \n8. exit\n" );
    scanf("%d",&n);
     system("cls");
    switch(n)
    {
        case 1 :countYZ();break;
        case 2:withoutString();break;
        case 3:equalIsNot();break;
        case 4:gHappy();break;
        case 5:sumDigits();break;
        case 6: mirrorEnds();break;
        case 7:maxBlock();break;
        case 8:break;
        default:printf("select appropriate number : ");

    }
    printf("press any key to continue :) ");
    getch();
}
}

void maxBlock(){
char tc[10][20] = {{"hoopla"},{"abbCCCddBBBxx"},{""},{"xyz"},{"xxyz"},{"abbbcbbbxbbbx"},{"XXBBBbbxx"},{"XXBBBBbbxx"},{"XXBBBbbxxXXXX"},{"XX2222BBBbbXX2222"}};
    for(int i=0;i<10;i++)
    {
    char *a;
    a = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(a,tc[i]);
    int max= -1;
    //actualcode
    for(int i=0;i < strlen(a) ;i++)
    {
        int cnt = 1;
        while(a[i] == a[i+1])
        {
            i++;
            cnt++;
        }
        if(cnt > max ) max = cnt;
    }
    printf("{%s} -> %d\n" , tc[i] , max );
    }

}
void  mirrorEnds(){

char tc[10][20] = {{"abXYZba"},{"abca"},{"aba"},{"abab"},{"xxx"},{"xxYxx"},{"Hi and iH"},{"X"},{""},{"123and then 321"},{"band andab"}};
    for(int i=0;i<10;i++)
    {
    char *a;
    a = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(a,tc[i]);
    int j,k;
     printf("{%s} ->" , tc[i] );
    for( j=0,k=strlen(a)-1 ;j < strlen(a),k>=0; j++,k--)
    {
        if(a[j] == a[k]) printf("%c",a[j]);
        else break;
    }
    printf("\n");
    }
}


void sumDigits(){
char tc[9][20] = {{"aa1bc2d3"},{"aa11b33"},{"Chocolate"},{"5hoco1a1e"},{"123abc123"},{" "},{"hello"},{"X1z9b2"},{"5432a"}};
    for(int i=0;i<9;i++)
    {
    char *a;
    a = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(a,tc[i]);
    int sum= 0;
    for(int i=0;i < strlen(a);i++)
    {
        if(isdigit(a[i])) sum = sum + (int)(a[i])-48;
    }
    printf("{%s} -> %d\n" , tc[i] , sum );
    }
}
void gHappy(){
char tc[12][20] = {{"xxggxx"},{"xxgxx"},{"xxggyygxx"},{"g"},{"gg"},{" "},{"xxgggxyz"},{"xxgggxyg"},{"xxgggxygg"},{"mgm"},{"mggm"},{"yyygggxyy"}};
    for(int i=0;i<12;i++)
    {
    char *a;
    a = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(a,tc[i]);
    int f=1;
    for(int i=1;i < strlen(a);i++)
    {
        if(a[i] == 'g')
        {
            if(a[i-1] != 'g' && a[i+1] != 'g')
            {
                f=0;
                break;
            }
        }
    }
    printf("{%s} -> %s\n" , tc[i] ,(f==1) ? "True" : "False" );
    }

}
void equalIsNot(){
char tc[10][20] = {{"This is not"},{"This is notnot"},{"noisxxnotyynotxisi"},{"noisxxnotyynotxsi"},{"xxxyyyzzzintint"},{" "},{"isisnotnot"},{"isisnotno7Not"},{"isnotis"},{"mis3notpotbotis"}};
    for(int i=0;i<10;i++)
    {
    char *a;
    a = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(a,tc[i]);
    //printf("%s\n",a);
    int cnt=0,cnt1=0;
    while(a=strstr(a,"is")){memmove(a,a+2,1+strlen(a+2));cnt++;}
    char *b;
    b = (int *)malloc(strlen(tc[i])*sizeof(int));
    strcpy(b,tc[i]);
    while(b=strstr(b,"not")){memmove(b,b+3,1+strlen(b+3));cnt1++;}
    printf("{%s} -> %s\n" , tc[i] ,(cnt == cnt1) ? "True" : "False" );
    }

}
void withoutString(){
    char base[19][16] = {{"Hello there"},{"Hello there"},{"Hello there"},{"This is a FISH"},{"This is a FISH"},{"This is a FISH"},{"abxxxxab"},{"abxxxab"},{"abxxxab"},{"xxx"},{"xxx"},{"xyzzy"},{" "},{"abcabc"},{"AA22bb"},{"1111"},{"1111"},{"MkjtMkx"},{"Hi HoHo"}};
  char remove[19][4] = {{"llo"},{"e"},{"x"},{"IS"},{"is"},{"Is"},{"xx"},{"xx"},{"x"},{"x"},{"xx"},{"Y"},{"x"},{"b"},{"2"},{"1"},{"11"},{"Mk"},{"Ho"}};
  for(int i=0;i<19;i++)
  {
      char *b = tolower(base[i]);
      char *r = tolower(remove[i]);
       printf("{%s , %s}",base[i] ,remove[i] );
    for(int j = 0; b[j]; j++) b[j] = tolower(b[j]);
    for(int j = 0; r[j]; j++) r[j] = tolower(r[j]);

    while( b=strstr(b,r) ) {memmove(b,b+strlen(r),1+strlen(b+strlen(r)));}

    printf("-> %s\n",base[i] );
  }
}
void countYZ(){
    char tc[11][13] = {{"fez day"},{"day fez"},{"day fyyyz"},{"day yak"},{"day:yak"},{"!!day--yaz!!"},{"yak zak"},{"DAY abc XYZ"},{"aaz yyz my"},{"y2bz"},{"zxyx"}};
    for(int i=0;i<11;i++)
    {
    char *a = tc[i];
    int cnt = 0;
    int i;
    for(i=1;i<strlen(a);i++)
    {
        if( !isalpha(a[i]) ) {
            if(a[i-1] == 'z' ||a[i-1] == 'Z' || a[i-1] == 'y' || a[i-1] == 'Y' )cnt++;
        }
    }
    i= strlen(a) ;
    if(a[i-1] == 'z' ||a[i-1] == 'Z' || a[i-1] == 'y' || a[i-1] == 'Y' ) cnt++;
    printf("{%s} -> %d\n" , a , cnt );
    }
}
