#include <bits/stdc++.h>

using namespace std;

int check(vector<string> c)
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(c[i][j]=='-')
                return 0;
    return 1;
}

vector< string > ans(10);
int over=0;
//    crosswordPuzzle(crossword,s,ans,0,count);
void crosswordPuzzle(vector <string> crossword, vector<string> s,vector<string> &ans,int k,vector<int> count)
{
  //  for(int i=0;i<10;i++)
  //   cout<<crossword[i]<<endl;
  // cout<<endl;


    if(k==s.size()&&check(crossword))
    {
        over=1;
        for(int i=0;i<10;i++)
            ans[i]=crossword[i];
        return;
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(over==1)
                return;
            int h_len=0,v_len=0,flag=0;
            if(crossword[i][j]=='-')
            {
                h_len=v_len=1;
                flag=1;
                //cout<<"CHECK -"<<endl;
            }
            if(crossword[i][j]!='+')
            {
                int hor=j+1,ver=i+1;
                while(hor<10&&crossword[i][hor]!='+')
                {
                    hor++;
                    h_len++;
                }
                while(ver<10&&crossword[ver][j]!='+')
                {
                    ver++;
                    v_len++;
                }
                if(crossword[i][j]!='+'&&crossword[i][j]!='-')
                {
                    h_len++;
                    v_len++;
                }
               // cout<<"CHECK LEN"<<endl;
            }

            //void crosswordPuzzle(vector <string> crossword, vector<string> s,vector<string> ans,int k,vector<int> count)
            for(int t=0;t<s.size();t++)
            {
                if(h_len==s[t].length()&&count[t]==0)
                {
                    if(flag==0&&s[t][0]!=crossword[i][j])
                        continue;
                   // cout<<"FIT HOR"<<endl;
                    int y=0;
                    if(crossword[i][j]==s[t][0])
                        y=1;
                    //for duplicate vector if some mismatchig beetwen mid position
                    vector<string> dup=crossword;
                    int f1=0;


                    while(y<s[t].length())
                    {
                        if(crossword[i][j+y]!='-'&&crossword[i][j+y]!=s[t][y])
                        {
                            f1=1;
                            break;
                        }
                        crossword[i][j+y]=s[t][y];
                        y++;
                    }
                    if(f1==1)
                    {
                        crossword=dup;
                        continue;
                    }
                    count[t]=1;
                    crosswordPuzzle(crossword,s,ans,k+1,count);
                    count[t]=0;
                }
            }
            for(int t=0;t<s.size();t++)
            {
                if(v_len==s[t].length()&&count[t]==0)
                {
                    if(flag==0&&s[t][0]!=crossword[i][j])
                        continue;
                    //cout<<"FIR VET"<<endl;
                    int y=0;
                    if(crossword[i][j]==s[t][0])
                        y=1;
                    //for mismatching
                    vector<string> dup=crossword;
                    int f1=0;



                    while(y<s[t].length())
                    {
                        if(crossword[i+y][j]!='-'&&crossword[i+y][j]!=s[t][y])
                        {
                      //      cout<<"VER NEW BREAK"<<endl;
                            f1=1;
                            break;
                        }
                        crossword[i+y][j]=s[t][y];
                        y++;
                    }
                    if(f1==1)
                    {
                        crossword=dup;
                        continue;
                    }
                    count[t]=1;
                    crosswordPuzzle(crossword,s,ans,k+1,count);
                    count[t]=0;
                }
            }
            if(over==1)
            {
             return;}
           //cout<<"outer"<<endl;

        }
        if(over==1)
            return;
    }
    if(over==1)
        return;
}

int main() {
    char change = '+';
    vector<string> crossword(10);
    for(int crossword_i = 0; crossword_i < 10; crossword_i++){
       cin >> crossword[crossword_i];
        for(int i=0;i<crossword[crossword_i].length();i++)
        {
            if(crossword[crossword_i][i] != '-' && crossword[crossword_i][i] != '+')
                change = crossword[crossword_i][i];
                crossword[crossword_i][i] = '+';

        }
    }
    for(int i=0;i<10;i++)
    cout<<crossword[i]<<endl;

    string hints;
    cin >> hints;
    vector<string> s;
    cout << change;
    for(int i=0;i<hints.length();)
    {
        string p="";
        while(hints[i]!=';'&&i!=hints.length())
        {
            p=p+hints[i];
            i++;
        }
        s.push_back(p);
        i++;
    }
    vector<int> count(s.size(),0);

    crosswordPuzzle(crossword,s,ans,0,count);



        for(int i=0;i<10;i++)
        cout<<ans[i]<<endl;
    return 0;
}
