/*
题目：https://www.luogu.com.cn/problem/P2880
思路：利用ST表模板，求出stMAx,stMin;区间最大值，区间最小值，输出两个值相减
*/
//代码实现
#include<stdio.h>
int stMax[50010][20];
int stMin[50010][20];
int cf[20];
int LOG[50010];
int a[50010];
int max(int x,int y)
{
    return x>y?x:y;
}
int min(int x,int y)
{
    return x<y?x:y;
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    cf[0]=1;
    LOG[0]=-1;
    for(int i=1; i<20; i++)
    {
        cf[i]=cf[i-1]*2;
    }
    for(int i=1; i<=n; i++)
    {
        LOG[i]=LOG[i/2]+1;
    }
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1; i<=n; i++)
    {
        stMax[i][0]=a[i];
        stMin[i][0]=a[i];
    }
    for(int j=1; j<=LOG[n]; j++)
    {
        for(int i=1; i<=n; i++)
        {
            if(i+cf[j]-1<=n)
            {
                stMax[i][j]=max(stMax[i][j-1],stMax[i+cf[j-1]][j-1]);
                stMin[i][j]=min(stMin[i][j-1],stMin[i+cf[j-1]][j-1]);
            }
        }
    }
    for(int i=0; i<q; i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int t=LOG[r-l+1];
        int ma=max(stMax[l][t],stMax[r-cf[t]+1][t]);
        int mi=min(stMin[l][t],stMin[r-cf[t]+1][t]);
        printf("%d\n",ma-mi);
    }
}
