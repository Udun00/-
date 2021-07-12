/*
题目：https://vjudge.net/contest/441637#problem/U
思路：模拟全排列，从4个数中挑出两个数进行运算，再从3个数中挑出两个数进行运算，最后剩下两个数进行运算
运算有六种,a+b,a*b,a-b,b-a,a/b,b/a;(除法要判断是否能除尽)
*/
//代码实现
#include<stdio.h>
int num[10];
int read(char a)
{
    if(a=='A')
    {
        return 1;
    }
    else if(a=='J')
    {
        return 11;
    }
    else if(a=='Q')
    {
        return 12;
    }
    else if(a=='K')
    {
        return 13;
    }
    else if(a=='1')
    {
        return 10;
    }
    else
    {
        return a-'0';
    }
}
int dfs(int n)
{
    if(n==1)
    {
        if(num[1]==24)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    for(int i=1; i<n; i++)
    {
        for(int j=i+1; j<=n; j++)
        {
            int x=num[i],y=num[j];
            num[j]=num[n];//移到后面
            num[i]=x+y;
            if(dfs(n-1)==1)
            {
                return 1;
            }
            num[i]=x-y;
            if(dfs(n-1)==1)
            {
                return 1;
            }
            num[i]=y-x;
            if(dfs(n-1)==1)
            {
                return 1;
            }
            num[i]=x*y;
            if(dfs(n-1)==1)
            {
                return 1;
            }
            if(y!=0&&x%y==0)
            {
                num[i]=x/y;
                if(dfs(n-1)==1)
                {
                    return 1;
                }
            }
            if(x!=0&&y%x==0)
            {
                num[i]=y/x;
                if(dfs(n-1)==1)
                {
                    return 1;
                }
            }
            num[i]=x;
            num[j]=y;
        }
    }
    return 0;
}
int main()
{
    char a[3];
    while(scanf("%s",a)!=EOF)
    {
        num[1]=read(a[0]);
        for(int i=2; i<=4; i++)
        {
            scanf("%s",a);
            num[i]=read(a[0]);
        }
        if(dfs(4)==1)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}
