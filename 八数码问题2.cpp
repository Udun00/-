/*
题目：https://vjudge.net/contest/441637#problem/I
思路：与八数码1不同的是，现在不是以12345678X为终点而是自己定终点，所以我们要以9种起点开始bfs并记录路径，利用康托展开值去重，并记录路径
*/
//代码实现
#include<iostream>
#include<queue>
#include<stack>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct k
{
    char option;
    int fa_contor;
} load[10][500005];
int ycl[9][9]= {{0,1,2,3,4,5,6,7,8},{1,0,2,3,4,5,6,7,8},{1,2,0,3,4,5,6,7,8},{1,2,3,0,4,5,6,7,8},{1,2,3,4,0,5,6,7,8},{1,2,3,4,5,0,6,7,8},{1,2,3,4,5,6,0,7,8},{1,2,3,4,5,6,7,0,8},{1,2,3,4,5,6,7,8,0}};
typedef struct node
{
    int state[9];
    int x,y;
} node;
int s[4][2]= {{1,0},{0,-1},{0,1},{-1,0}};
int fff[] = { 1,1,2,6,24,120,720,5040,40320,362880};
int book[500005];
int contor(int x[])
{
    int sum=0;
    for(int i=0; i<9; i++)
    {
        int y=0;
        for(int j=i+1; j<9; j++)
        {
            if(x[i]>x[j])y++;
        }
        sum+=y*fff[8-i];
    }
    return sum;
}
void bfs(int wz,node head)
{
    memset(book,0,sizeof(book));
    queue<node> q;
    q.push(head);
    book[contor(head.state)]=1;
    while(!q.empty())
    {
        node g=q.front();
        q.pop();
        int ct1=contor(g.state);
        for(int i=0; i<4; i++)
        {
            node k=g;
            k.x+=s[i][0];
            k.y+=s[i][1];
            if(k.x>=3||k.x<0||k.y>=3||k.y<0)
            {
                continue;
            }
            int z=g.x*3+g.y;
            int nz=k.x*3+k.y;
            swap(k.state[z],k.state[nz]);
            int ct2=contor(k.state);
            if(book[ct2]==0)
            {
                book[ct2]=1;
                if(i==0)
                {
                    load[wz][ct2].option='d';
                }
                else if(i==1)
                {
                    load[wz][ct2].option='l';
                }
                else if(i==2)
                {
                    load[wz][ct2].option='r';
                }
                else
                {
                    load[wz][ct2].option='u';
                }
                load[wz][ct2].fa_contor=ct1;
                q.push(k);
            }
        }
    }
}
int main()
{
    for(int i=0; i<9; i++)
    {
        node hh;
        for(int j=0;j<9;j++)
        {
            hh.state[j]=ycl[i][j];
        }
        hh.x=i/3;
        hh.y=i%3;
        bfs(i,hh);
    }
    int t;
    scanf("%d",&t);
    int o=1;
    while(t--)
    {
        int a[10],b[10],c[10];
        char s1[10],s2[10];
        scanf("%s%s",s1,s2);
        int ww=0;
        for(int i=0; i<9; i++)
        {
            if(s1[i]=='X')
            {
                a[i]=0;
                ww=i;
            }
            else
            {
                a[i]=s1[i]-'0';
            }
            if(s2[i]=='X')
            {
                b[i]=0;
            }
            else
            {
                b[i]=s2[i]-'0';
            }
        }
        int j=1;
        for(int i=0;i<9;i++)
        {
            if(a[i]==0)continue;
            c[a[i]]=j;
            a[i]=j;
            j++;
        }
        for(int i=0;i<9;i++)
        {
            if(b[i]==0)continue;
            b[i]=c[b[i]];
        }
        int c1=contor(a);
        int c2=contor(b);
        stack<char> ll;
        while(c1!=c2)
        {
            ll.push(load[ww][c2].option);
            c2=load[ww][c2].fa_contor;
        }
        printf("Case %d: %d\n",o++,ll.size());
        while(!ll.empty())
        {
            printf("%c",ll.top());
            ll.pop();
        }
        printf("\n");
    }
}
