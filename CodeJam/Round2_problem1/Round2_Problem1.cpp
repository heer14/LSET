#include <iostream>
#include <fstream>
#include<cmath>
using namespace std;
int mat[2][1000];
int index;
bool isAlreadyThere(int r,int c)
{
    bool result = false ;
    for(int i = 0 ; i < index ; i++)
    {

            if(mat[0][i] == r && mat[1][i] == c)
            {
                result = true;
                break;
            }

    }
    return result;
}
bool cheakInfestation()
{
    bool result = true ;
    int i =0 ;
    int i1 = index;
    for(int i =0;i<i1;i++)
    {
        for(int j=i;j < i1 ;j++)
        {   if((mat[0][i] == mat[0][j]) && ( abs(mat[1][i] - mat[1][j]) == 2 )  )
            {
                    mat[0][index] = mat[0][i];
                    mat[1][i] > mat[1][j] ? (mat[1][index] = mat[1][i]-1 ) : (mat[1][index] = mat[1][j]-1 );
                    if(!isAlreadyThere(mat[0][index] , mat[1][index] ))
                        index++;
            }
            else if ( (mat[1][i] == mat[1][j]) && ( abs(mat[0][i] - mat[0][j]) == 2 )  )
            {
                 mat[1][index] = mat[1][i];
                    mat[0][i] > mat[0][j] ? (mat[0][index] = mat[0][i]-1 ) : (mat[0][index] = mat[0][j]-1 );
                     if(!isAlreadyThere(mat[0][index] , mat[1][index] ))
                        index++;
            }
            else if ( (abs(mat[0][i] - mat[0][j]) == 1) && ( abs(mat[1][i] - mat[1][j]) == 1 ) )
            {
                    mat[0][index] = mat[1][i];
                    mat[1][index] = mat[0][j];
                     if(!isAlreadyThere(mat[0][index] , mat[1][index] ))
                        index++;
                    mat[0][index] = mat[1][j];
                    mat[1][index] = mat[0][i];
                     if(!isAlreadyThere(mat[0][index] , mat[1][index] ))
                        index++;

            }
        }

    }
    if(index == i1)
        result = false ;
return result;
}
int main()
{

 ifstream ifp;
ifp.open ("set1.in");
ofstream ofp;
ofp.open ("set1.out");
int T,i=0;
index = 0;
ifp >> T;
while(i < T)
{
    index= 0;
    int cnt =0,j=0,n,r,c;
    ifp >> n ;
    while(j < n )
    {
        ifp >> r;
        ifp >> c;
        mat[0][index] = r;
        mat[1][index] = c;
        index++;
        j++;
    }
    cnt=0;
    while(cheakInfestation())
        cnt ++ ;
    cout << cnt << "\n";
    ofp << cnt << "\n";
    i++;
}
ifp.close();
ofp.close();

return 0;
}
