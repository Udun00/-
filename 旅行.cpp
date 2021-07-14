/*
题目：https://vjudge.net/contest/441637#problem/N
思路：因为最多只有10个点，可以暴搜，将每个点的遍历情况化成一个3进制数，
总共有3^10种情况找到一种每个点至少都遍历了一次且代价最小的一种状态，
dp[i+cf[k]][k]=min(dp[i+cf[k]][k],dp[i][j]+mp[j][k]);
cf[i]代表3的i次方，num[i][j]代表状态i的第j位数
dp[i][j]状态i以j位为终点的最小代价
*/
//代码实现
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int cf[11];//cf[i]代表3的i次方
int num[180010][11];//num[i][j]代表三进制数i的第j为是什么
int dp[180010][11];//dp[i][j]代表状态i，最后到j的最小代价
int mp[20][20];
int main()
{
    cf[0]=1;
    for(int i=1; i<=10; i++)cf[i]=cf[i-1]*3;
    for(int i=0; i<cf[10]; i++)
    {
        int x=i;
        for(int j=0; j<10; j++)
        {
            num[i][j]=x%3;
            x=x/3;
        }
    }
    int n,m;
    while(cin>>n>>m)
    {
        memset(mp,0x3f3f3f3f,sizeof(mp));
        for(int i=0; i<m; i++)
        {
            int x,y,c;
            cin>>x>>y>>c;
            mp[x-1][y-1]=mp[y-1][x-1]=min(mp[x-1][y-1],c);
        }
        memset(dp,0x3f3f3f3f,sizeof(dp));
        for(int i=0; i<n; i++)dp[cf[i]][i]=0;
        int flag=1;
        int sum=0x3f3f3f3f;
        for(int i=0; i<cf[n]; i++)
        {
            flag=1;
            for(int j=0; j<n; j++)
            {
                if(num[i][j]==0)
                {
                    flag=0;//有的点一次都没便利到
                }
                if(dp[i][j]==0x3f3f3f3f)
                {
                    continue;
                }

                for(int k=0; k<n; k++)
                {
                    if(j==k||mp[j][k]==0x3f3f3f3f||num[i][k]>=2)//不能从不走，且要有路，且遍历过的次数不能超过两次
                        continue;
                    dp[i+cf[k]][k]=min(dp[i+cf[k]][k],dp[i][j]+mp[j][k]);//其实就是从i状态转变为i状态加上走一遍k的状态(佛洛依德算法更新最小代价)
                }
            }
            if(flag==1)//如果每个点都遍历到了更新答案
            {
                for(int j=0; j<n; j++)
                {
                    sum=min(sum,dp[i][j]);
                }
            }
        }
        if(sum==0x3f3f3f3f)cout<<-1<<endl;
        else cout<<sum<<endl;
    }
}
