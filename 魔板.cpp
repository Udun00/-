/*
题目：https://vjudge.net/contest/441637#problem/R
思路：模拟从12345678开始变化的所有情况，记录下路径，去重用康托展开，因为我们都是从12345678开始，所以我们要将输入的起点和终点变换一下，等价于12345678到变化后的终点
利用状态的康托值找到路径输出
*/
//代码实现
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef struct node
{
    int state[10];
    int cnt;
    string step;
} node;
queue<node> q;
long int fff[] = { 1,1,2,6,24,120,720,5040,40320,362880 };
bool book[40322];
int uuuu=0;
string load[40322];
long long int contor(int x[])
{
    long long int sum = 0;
    for (int i = 0; i < 8; i++)
    {
        int y = 0;
        for (int j = i + 1; j < 8; j++)
        {
            if (x[j] < x[i])y++;
        }
        sum += y * fff[7 - i];
    }
    return sum;
}
node opA(node x)
{
    node k;
    for (int i = 0; i <= 7; i++)
    {
        k.state[i] = x.state[7 - i];
    }
    k.cnt = contor(k.state);
    k.step = x.step + "A";
    return k;
}
node opB(node x)
{
    node k;
    int h = x.state[3];
    for (int i = 3; i > 0; i--)
    {
        k.state[i] = x.state[i - 1];
    }
    k.state[0] = h;
    int y = x.state[4];
    for (int i = 4; i < 7; i++)
    {
        k.state[i] = x.state[i + 1];
    }
    k.state[7] = y;
    k.cnt = contor(k.state);
    k.step = x.step + "B";
    return k;
}
node opC(node x)
{
    node k;
    for (int i = 0; i <= 7; i++)
    {
        k.state[i] = x.state[i];
    }
    int t = k.state[1];
    k.state[1] = k.state[6];
    k.state[6] = k.state[5];
    k.state[5] = k.state[2];
    k.state[2] = t;
    k.cnt = contor(k.state);
    k.step = x.step + "C";
    return k;
}
void bfs()
{
    while (!q.empty())
    {
        node g = q.front();
        node k = opA(g);
        if (book[k.cnt] == false)
        {
            load[k.cnt] = k.step;
            book[k.cnt] = true;
            q.push(k);
        }
        k = opB(g);
        if (book[k.cnt] == false)
        {
            load[k.cnt] = k.step;
            book[k.cnt] = true;
            q.push(k);
        }
        k = opC(g);
        if (book[k.cnt] == false)
        {
            load[k.cnt] = k.step;
            book[k.cnt] = true;
            q.push(k);
        }
        q.pop();
    }
}
int main()
{
    node x;
    for (int i = 0; i <= 7; i++)
    {
        x.state[i] = i + 1;
    }
    x.cnt = contor(x.state);
    x.step = "";
    load[x.cnt] = x.step;
    book[x.cnt] = true;
    q.push(x);
    bfs();
    char s1[10], s2[10];
    while (cin >> s1)
    {
        int s[10];
        cin >> s2;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (s1[i] == s2[j]) { s[j] = i + 1; break; }//等价变换
            }
        }
        cout << load[contor(s)] << endl;
    }
}

