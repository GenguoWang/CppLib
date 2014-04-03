#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define NUM 202
#define MAXINT 0x3fffffff
int flowMap[NUM][NUM];
int d[NUM];
vector<int> node[NUM];
int bfs(int s,int t)
{
    //first find a way to t
    memset((void*)d,-1,sizeof(d));
    queue<int> q; int now; q.push(s); d[s]=-2; int e;
    while(!q.empty())
    {
        now = q.front();q.pop();
        for(int i=0;i<node[now].size(); ++i)
        {
            e = node[now][i];
            if(d[e]==-1 && flowMap[now][e]>0)
            {
                d[e] = now; q.push(e);
                if(e==t)break;
            }
        }
    }
    //no way return 0
    if(d[t]==-1)return 0;
    //get the minimum flow on the path
    int flow = MAXINT;
    now = t;
    while(d[now]>=0)
    {
        flow = min(flowMap[d[now]][now],flow);
        now = d[now];
    }
    //update the path
    now = t;
    while(d[now]>=0)
    {
        flowMap[d[now]][now] -= flow;
        flowMap[now][d[now]] += flow;
        now = d[now];
    }
    return flow;
}
int maxflow(int s,int t)
{
    int sum=0,u;
    while(u=bfs(s,t)) { sum += u; }
    return sum;
}
int main()
{
    int T,n,m,x,y,w,c;
    cin >> T;
    for(int caseNumber=1;caseNumber<=T;++caseNumber)
    {
        cout << "Case #" << caseNumber << ":\n";
        cin >> n >> m;
        for(int i=1;i<=m;++i)
        {
            cin >> x >> y >> w;
            flowMap[x-1][y-1] = w;
            flowMap[y-1][x-1] = w;
            node[x-1].push_back(y-1);
            node[y-1].push_back(x-1);
            c = maxflow(0,n-1);
            if(c>0) cout << i << ' ' << c << '\n';
        }
        for(int i=0;i<n;++i) node[i].clear();
    }
    return 0;
}

