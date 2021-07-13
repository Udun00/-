/*
题目：https://vjudge.net/contest/441637#problem/O
思路：和普通走迷宫不同的是，这个题目需要拿钥匙去开门，那我们用二进制来记录是否拥有该钥匙，如果二进制下第i为1代表有第i把钥匙，否则没有该钥匙，
遇到钥匙更新钥匙状态，去重数组增加一维来记录钥匙情况，遇到门是判断是否有该门对应的钥匙，如果有就继续往这个方向走
*/
//代码实现
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
char mp[22][22];
int n, m, t;
int book[22][22][1050];
int dd[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
typedef struct node
{
    int x, y;
    int key;
    int step;
}node;
queue<node> q;
int bfs()
{
    while (!q.empty())
    {
        node g = q.front();
        if (mp[g.x][g.y] == '^')
        {
            return g.step;
        }
        for (int i = 0; i < 4; i++)
        {
            int gkey = g.key;
            int nx = g.x + dd[i][0];
            int ny = g.y + dd[i][1];
            if (mp[nx][ny] == '*' || nx < 0 || nx >= n || ny < 0 || ny >= m || g.step + 1 >= t || book[nx][ny][gkey])
                continue;
            if (mp[nx][ny] <= 'j' && mp[nx][ny] >= 'a')
            {
                int ss = mp[nx][ny] - 'a';
                if ((gkey & (1 << ss)) == 0)
                {
                    gkey += (1 << ss);
                }
            }
            else if (mp[nx][ny] <= 'J' && mp[nx][ny] >= 'A')
            {
                int ss = mp[nx][ny] - 'A';
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
    while (cin >> n >> m >> t)
    {
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
                if (mp[i][j] == '@')
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
        if (ans > 0&&ans<t)cout << ans << endl;
        else cout << -1 << endl;
    }
}
