/*
题目：https://vjudge.net/contest/441637#problem/K
思路：和普通总迷宫不同的是，这个迷宫有炮塔，所以你每走一步都要判断是否有子弹落在这里，但子弹像跳跳球一样，每v个格子落一次，且炮塔可以挡子弹
所以我们每走一步就判断上下左右方向离我们最近的一个炮塔，如果不是射向我们这边就不用管，如果设向我们这边，判断我们到该点时，炮塔是否有子弹落在这里
且时间不能超过规定时间，可以原地不走，但也会消耗时间
*/
//代码实现
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
bool book[105][105][1005];
int s[5][2] = { {0,0},{1,0},{-1,0},{0,1},{0,-1} };
typedef struct node
{
    int x, y;
    int time;
} node;
typedef struct turret
{
    char fx;//方向
    int v, t;//速度和周期
} turret;
queue<node> q;
turret pao[105][105];
int n, m, k, d;
void bfs()
{
    while (!q.empty())
    {
        //cout<<"yyy"<<endl;
        node g = q.front();
        if (g.x == n && g.y == m)
        {
            cout << g.time << endl;
            return;
        }
        //cout<<111111<<endl;
        for (int i = 0; i < 5; i++)
        {
            int nx = g.x + s[i][0];
            int ny = g.y + s[i][1];
            int ns = g.time + 1;

            if (nx > n || nx<0 || ny>m || ny<0 || ns>d||pao[nx][ny].v != 0 || book[nx][ny][ns] == 1 )
                continue;
            int flag = 1;
            //cout<<22222222<<endl;
            for (int j = nx - 1; j >= 0; j--)
            {
                if (pao[j][ny].v != 0 && pao[j][ny].fx == 'S')
                {
                    int dx = nx - j;
                    if (dx % pao[j][ny].v != 0)break;
                    int tt = ns - (dx / pao[j][ny].v);
                    if (tt < 0)break;
                    if (tt % pao[j][ny].t == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                else if (pao[j][ny].v != 0 && pao[j][ny].fx != 'S')
                {
                    break;
                }
            }
            if (flag == 0)
            {
                continue;
            }
           // cout<<555555555<<endl;
            //----------------------------------
            for (int j = nx + 1; j <= n; j++)
            {
                if (pao[j][ny].v != 0 && pao[j][ny].fx == 'N')
                {
                    int dx = j - nx;
                    if (dx % pao[j][ny].v != 0)break;
                    int tt = ns - (dx / pao[j][ny].v);
                    if (tt < 0)break;
                    if (tt % pao[j][ny].t == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                else if (pao[j][ny].v != 0 && pao[j][ny].fx != 'N')
                {
                    break;
                }
            }
            if (flag == 0)
            {
                continue;
            }
            //cout<<666666<<endl;
            //----------------------------------
            for (int j = ny - 1; j >= 0; j--)
            {
                if (pao[nx][j].v != 0 && pao[nx][j].fx == 'E')
                {
                    int dx = ny - j;
                    if (dx % pao[nx][j].v != 0)break;
                    int tt = ns - (dx / pao[nx][j].v);
                    if (tt < 0)break;
                    if (tt % pao[nx][j].t == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                else if (pao[nx][j].v != 0 && pao[nx][j].fx != 'E')
                {
                    break;
                }
            }
            if (flag == 0)
            {
                continue;
            }
            //cout<<77777<<endl;
            //----------------------------------
            for (int j = ny + 1; j <= m; j++)
            {
                if (pao[nx][j].v != 0 && pao[nx][j].fx == 'W')
                {
                    int dx = j - ny;
                    if (dx % pao[nx][j].v != 0)break;
                    int tt = ns - (dx / pao[nx][j].v);
                    if (tt < 0)break;
                    if (tt % pao[nx][j].t == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                else if (pao[nx][j].v != 0 && pao[nx][j].fx != 'W')
                {
                    break;
                }
            }
            if (flag == 0)
            {
                continue;
            }
            //cout<<8888<<endl;
            node next;
            next.time = ns;
            next.x = nx;
            next.y = ny;
            //cout<<nx<<ny<<ns<<endl;
            book[nx][ny][ns] = true;
            q.push(next);
            //cout<<99999<<endl;
        }
        q.pop();
        //cout<<6666<<endl;
    }
    cout << "Bad luck!" << endl;
}

int main()
{
    while (cin >> n >> m >> k >> d)
    {
      //  cout<<"1"<<endl;
        while (!q.empty())
        {
            q.pop();
        }
      //  cout<<"2"<<endl;
        memset(book, false, sizeof(book));
        memset(pao, 0, sizeof(pao));
        for (int i = 0; i < k; i++)
        {
            char f;
            int a, b, c, x;
            cin >> f;
            cin >> a >> b >> c >> x;
            pao[c][x].fx = f;
            pao[c][x].v = b;
            pao[c][x].t = a;
        }
    //    cout<<"3"<<endl;
        book[0][0][0] = true;
        node k;
        k.time = 0;
        k.x = 0;
        k.y = 0;
        q.push(k);
       // cout<<"5"<<endl;
        bfs();
        //cout<<"4"<<endl;
    }
}
