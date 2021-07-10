/*
题目：https://www.luogu.com.cn/problem/P3865
思路：计算出每个点i到i+2^k-1的最大值，k取1，2，3...
stMax[i][j]代表从i-----i+2^j-1这个区间的最大值
状态转移时把区间拆成两个区间来转移
stMax[i][j]=max(stMAx[i][j-1],stMax[i+2^(j-1)][j-1]);
查询区间最大值时我们需要覆盖这个区间，第一个区间（l,l+2^t），第二个区间（r-2^t+1,r）;
t=log_2 (r-l+1);
输出这两个区间的值的最大值
*/
//代码实现
#include<stdio.h>
#define ll long long int
ll stMax[100010][21];//stMax[i][j]代表这i到2^j-1的最大值
ll cf[21];//cf[i],代表2的i次方
ll Log[100010];//Log[i]代表logi
ll a[100010];
ll max(ll x,ll y)
{
    return x>y?x:y;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    cf[0]=1;
    Log[0]=-1;
    for(int i=1;i<=20;i++)
    {
        cf[i]=cf[i-1]*2;
    }
    for(int i=1;i<=n;i++)
    {
        Log[i]=Log[i/2]+1;
    }
    for(int i=1;i<=n;i++)
    {
        stMax[i][0]=a[i];
    }
    for(int j=1;j<=Log[n];j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(i+cf[j]-1<=n)
            {
                stMax[i][j]=max(stMax[i][j-1],stMax[i+cf[j-1]][j-1]);//状态转移(l-----l+2^(j-1),r-2^(j-1)-----r)
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        ll l,r;
        scanf("%lld %lld",&l,&r);
        ll t=Log[r-l+1];
        printf("%lld\n",max(stMax[l][t],stMax[r-cf[t]+1][t]));
    }
}
