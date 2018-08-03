#include <iostream>
#include <queue>

using namespace std;

typedef struct grid{

    int x;
    int y;
    int t;
};
int main ()
{
    priority_queue <struct grid> gquiz;
    struct grid p;
    p.x =10;
    p.y = 20;
    p.t = 30;

    gquiz.push(p);
     struct grid q = gquiz.pop();
     cout << q.x << q.y << q.t ;


    return 0;
}
