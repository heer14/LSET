#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the matrixRotation function below.
void matrixRotation(vector<vector<int>> matrix, int rotation) {
int r = matrix.size()-1;
int c = matrix[0].size()-1;
int ans[r+1][c+1];
    int l =0;
    int rot;
    for(int i=0;i<=r;i++)
    {
        for(int j=0;j<=c;j++){
            int r1 = i;
            int c1 = j;
            ans[r1][c1] = 0;
            rot = rotation;
            if(r1 == r || c1 == c || r1 == 0 || c1 == 0 )
                l = 0;
            else if(r1== c1 && ((c-c1) > c1)) l = r1 ;
            else l = min(r-r1 , c-c1) ;
            cout << l << endl;
            while(rot > 0){
                if(r1 == 0+l && c1 == 0+l)
                {
                    r1++;
                }
                else if(r1 == 0+l && c1 > 0+l)
                {
                    c1--;
                }
                else if(c1 == 0 && r1 < r - l )
                {
                    r1++;
                }
                else if(r1 == r -l  && c1 == c-l )
                {
                    r1--;
                }
                else if(r1 == r - l)
                {
                    c1++;
                }
                else if(c1==c-l)
                {
                    r1--;
                }
                ans[r1][c1] = matrix[i][j];
                for(int i1=0;i1<=r;i1++){
         for(int j1=0;j1<=c;j1++)
             cout << ans[i1][j1]<< " ";
        cout << endl;
    }
                //cout << r1 << c1 << "->" << i << j  << endl ;
                rot--;

            }
        }
    }

}

int main()
{
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);

    int n = stoi(mnr[1]);

    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
