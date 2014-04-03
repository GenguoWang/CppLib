#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=20;
const int INF=0x3f3f3f3f;
int s[N][N];//记录图的邻接矩阵
int d[N];//记录图中各点的层次
int n,m;
int min(int a,int b)
{
	return a<b?a:b;
}
bool bfs()
{
	queue<int>Q;
	memset(d,-1,sizeof(d));//此处初始化要特别注意，以上版本的初始化就存在很大问题
	d[1]=0;//如果处理不慎就很容易死循环
	Q.push(1);
	while(!Q.empty()){
		int v=Q.front();Q.pop();
		for(int i=1;i<=n;i++){
			if(d[i]==-1&&s[v][i]){//此处应是s[v][i]!=0,而不是以上版本中的s[v][i]>0,因为dfs是可能会走错，这样可以对其进行修正。
				d[i]=d[v]+1;
				Q.push(i);
			}
		}
	}
	return d[n]!=-1;
}
int dfs(int v,int cur_flow)
{
	int dt=cur_flow;
	if(v==n)return cur_flow;
	for(int i=1;i<=n;i++){
		if(s[v][i]>0&&d[v]+1==d[i]){
			int flow=dfs(i,min(dt,s[v][i]));
			s[v][i]-=flow;
			s[i][v]+=flow;
			dt-=flow;
		}
	}
	return cur_flow-dt;
}
int dinic()
{
	int cur_flow,ans=0;
	while(bfs()){//一次bfs可以找到几条增广路
		while(cur_flow=dfs(1,INF))
			ans+=cur_flow;
	}
	return ans;
}
int main()
{
	int t,i,cas=0,u,v,w,newF;
	scanf("%d",&t);
	while(t--){
		memset(s,0,sizeof(s));
		scanf("%d %d",&n,&m);
		printf("Case %d:\n",++cas);
		for(i=1;i<=m;i++){
			scanf("%d %d %d",&u,&v,&w);
			if(u==v)continue;
			s[u][v]+=w;
			s[v][u]+=w;
			newF = dinic();   //每次执行的话，是在上一次的基础上增加流，而不是完全重新计算，所以newF就是增量
			if(newF > 0)printf("%d %d\n",i,newF);
		}
		//printf("\n");
	}
	return 0;
}
 
