#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string str = "<tag1 value = \"HelloWorld\">";
    regex rgx("^<tag(( [[:w:]]+) = \"([[:w:]]+)\")*>$");
    smatch m;
    bool match = regex_search(str,m,e);
    for(int i=0;i<m.size();i++)
        cout << m[i].str() << endl;



    return 0;
}
