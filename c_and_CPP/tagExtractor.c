#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
    int T,i;
    scanf("%d" , &T);
    while(T > 0)
    {
    Char *line;
    scanf("%s",line);
   for(i =0;i<strlen(line),i++ ){
       while(line[i] != '<') i++;
       if(i < strlen(line))
       {
           while(line[i] != '>'){
           tag[t] = line[i];
           t++;
           i++;
           }
       }
   }

    }

    T--;
    }
}
