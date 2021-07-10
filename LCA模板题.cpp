/*
题目：https://www.luogu.com.cn/problem/P3379
思路：我们先求出每个点跳2^k距离的祖先是谁，求出每个点的深度，求a,b两个点的最近的公共祖先，(假设a的深度大于b)先将a上升到b同等高度，如果a==b返回b,然后找到a,b同时跳2^k倍不同的祖先，跳到该祖先的位置
返回lca[a][0];
*/
//代码实现
#include<stdio.h>
#include<string.h>
struct node
{
    int me, next;//邻接表
} e[1000010];
int sum = 0;//边数
int head[500010];
int deep[500010];//深度
int lca[500010][21];//lca[i][j]代表i的2^j倍祖先
void add(int x, int y)
{
    e[sum].me = y;
    e[sum].next = head[x];
    head[x] = sum;
    sum++;
}
void dfs(int son, int father)
{
    deep[son] = deep[father] + 1;
    lca[son][0] = father;
    for (int i = 1; (1 << i) <= deep[son]; i++)
    {
        lca[son][i] = lca[lca[son][i - 1]][i - 1];
    }
    for (int i = head[son]; i != -1; i = e[i].next)
    {
        int g = e[i].me;
        if (g != father)
        {
            dfs(g, son);//处理        }
        }
    }
}
int LCA(int a, int b)
{
    if (deep[a] < deep[b])//保证a的深度比b大，后面方便
    {
        int t;
        t = a;
        a = b;
        b = t;
    }
    int h = deep[a] - deep[b];
    for (int i = 20; i >= 0; i--)
    {
        if (h&(1<<i))//调整a和b同高度
        {
            a = lca[a][i];
            //printf("%d %d\n",a,i);
        }
    }
    //printf("\n");
    if (a == b)
    {
        return b;//代表a在b的下面
    }
    for (int i = 20; i >= 0; i--)
    {
        if (lca[a][i] == lca[b][i])
        {
            continue;
        }
        else
        {
            a = lca[a][i];//找到祖先不同，一起往上移
            b = lca[b][i];
        }
    }
    return lca[a][0];
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(deep, 0, sizeof(deep));
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(s, 0);
    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", LCA(l, r));
    }
    return 0;
}

