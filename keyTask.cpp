/*
题目：https://vjudge.net/contest/441637#problem/S
思路：和胜利大逃亡一样，也是要拿钥匙的bfs走迷宫，但它的钥匙字母不规律，要特殊判断，不然内存超限,且没有限时
*/
//代码实现
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
char mp[110][110];
int n, m, t;
int book[110][110][50];
int dd[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
typedef struct node
{
    int x, y;
    int key;
    int step;
} node;
queue<node> q;
int bfs()
{
    while (!q.empty())
    {
        node g = q.front();
        if (mp[g.x][g.y] == 'X')
        {
            return g.step;
        }
        for (int i = 0; i < 4; i++)
        {
            int gkey = g.key;
            int nx = g.x + dd[i][0];
            int ny = g.y + dd[i][1];
            if (mp[nx][ny] == '#' || nx < 0 || nx >= n || ny < 0 || ny >= m || book[nx][ny][gkey])
                continue;
            if (mp[nx][ny]=='b')
            {
                int ss = 0;
                if ((gkey & (1 << ss)) == 0)
                {
                    gkey += (1 << ss);
                }
            }
            else if (mp[nx][ny]=='y')
            {
                int ss = 1;
                if ((gkey & (1 << ss)) == 0)
                {
                    gkey += (1 << ss);
                }
            }
            else if (mp[nx][ny]=='r')
            {
                int ss = 2;
                if ((gkey & (1 << ss)) == 0)
                {
                    gkey += (1 << ss);
                }
            }
            else if (mp[nx][ny]=='g')
            {
                int ss = 3;
                if ((gkey & (1 << ss)) == 0)
                {
                    gkey += (1 << ss);
                }
            }
            else if (mp[nx][ny]=='B')
            {
                int ss = 0;
                if ((gkey & (1 << ss)) == 0)
                    continue;
            }
            else if (mp[nx][ny]=='Y')
            {
                int ss = 1;
                if ((gkey & (1 << ss)) == 0)
                    continue;
            }
            else if (mp[nx][ny]=='R')
            {
                int ss = 2;
                if ((gkey & (1 << ss)) == 0)
                    continue;
            }
            else if (mp[nx][ny]=='G')
            {
                int ss = 3;
                if ((gkey & (1 << ss)) == 0)
                    continue;
            }
            node h;
            h.x = nx;
            h.y = ny;
            h.key = gkey;
            h.step = g.step + 1;
            book[h.x][h.y][h.key] = 1;
            q.push(h);

        }
        q.pop();
    }
    return 0;
}
int main()
{
    while (cin >> n >> m)
    {
        if(n==0&&m==0)break;
        memset(book, 0, sizeof(book));
        while (!q.empty())
        {
            q.pop();
        }
        node st;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mp[i][j];
                if (mp[i][j] == '*')
                {
                    st.x = i;
                    st.y = j;
                }
            }
        }
        st.key = 0;
        st.step = 0;
        q.push(st);
        book[st.x][st.y][st.key] = 1;
        int ans = bfs();
        if (ans > 0)cout <<"Escape possible in "<<ans<<" steps."<< endl;
        else cout <<"The poor student is trapped!"<< endl;
    }
}
