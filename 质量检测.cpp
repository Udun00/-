/*
题目：https://www.luogu.com.cn/problem/P2251
思路：利用ST表模板预处理，查询(i,i+m-1)的最小值
*/
//代码实现
#include<stdio.h>
int cf[30];
int LOG[1000100];
int a[1000100];
int stmin[1000100][30];
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
    for(int i=1;i<=30;i++)
    {
        cf[i]=cf[i-1]*2;
    }
    for(int i=1;i<=n;i++)
    {
        LOG[i]=LOG[i/2]+1;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        stmin[i][0]=a[i];
    }
    for(int j=1;j<=LOG[n];j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(i+cf[j]-1<=n)
            {
                stmin[i][j]=min(stmin[i][j-1],stmin[i+cf[j-1]][j-1]);
            }
        }
    }    for(int i=1;i<=n-q+1;i++)
    {
        int l=i,r=i+q-1;
        int t=LOG[r-l+1];
        printf("%d\n",min(stmin[l][t],stmin[r-cf[t]+1][t]));
    }
}
