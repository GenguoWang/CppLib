#include "../Graph.h"
#include <fstream>
#include <cassert>
using namespace std;
#define MAX 0x3ffffff
void testTopo()
{
    int edges[7][2] = 
    {
        {0,1},
        {1,2},
        {2,3},
        {0,3},
        {1,3},
        {4,2},
        {4,5}
    };
	kingo::Graph graph(6);
    for(int i=0;i<7;++i) graph.addDirectEdge(edges[i][0],edges[i][1],0);
    int pos[6];
    for(int i=0;i<6;++i)pos[i]=-1;
	vector<kingo::Vertex*> res = graph.Topological_sort();
    for(int i=0;i<res.size();++i) pos[res[i]->number] = i;
    for(int i=0;i<7;++i) assert(pos[edges[i][0]] < pos[edges[i][1]]);

}
void testPrim()
{
    ifstream fin("testPrim.in");
    int N,P,Res;
    fin >> N >> P >> Res;
    kingo::Graph graph(N);
    int x,y,w;
    while(P--)
    {
        fin >> x >> y >> w;
        graph.addEdge(x,y,w);
    }
    graph.Mst_Prim(0);
    int res = 0;
    vector<kingo::Vertex> &v = graph.vertex;
    for(int i=0;i<N;++i)
    {
        if(v[i].pre != -1)
        {
            res += v[i].weight;
        }
    }
    assert(res==Res);
}
void testDijkstra()
{
    ifstream fin("testFloyd.in");
    int N,P,C;
    int cow[500];
    int x,y,w;
    fin >> N >> P >> C;
    for(int i=0;i<N;++i)fin>>cow[i];
    kingo::Graph graph(P);
    for(int i=0;i<C;++i)
    {
        fin >> x >> y >> w;
        graph.addEdge(x-1,y-1,w);
    }
    int * path = new int[P*P];
    for(int i=0;i<P;++i)
    {
        graph.Dijkstra(i);
        for(int j=0;j<P;++j) path[i*P+j] = graph.vertex[j].weight;
    }
    int minCost = MAX,currentCost;
    int minP;
    for(int i=0;i<P;++i)
    {
        currentCost = 0;
        for(int j=0;j<N;++j)
        {
            currentCost += path[(cow[j]-1)*P+i];
        }
        if(currentCost<minCost)
        {
            minCost = currentCost;
            minP = i;
        }
    }
    assert(minCost == 868);
    fin.close();
}
void testFloyd()
{
    ifstream fin("testFloyd.in");
    int N,P,C;
    int cow[500];
    int x,y,w;
    fin >> N >> P >> C;
    for(int i=0;i<N;++i)fin>>cow[i];
    kingo::Graph graph(P);
    for(int i=0;i<C;++i)
    {
        fin >> x >> y >> w;
        graph.addEdge(x-1,y-1,w);
    }
    int * path = graph.Floyd();
    int minCost = MAX,currentCost;
    int minP;
    for(int i=0;i<P;++i)
    {
        currentCost = 0;
        for(int j=0;j<N;++j)
        {
            currentCost += path[(cow[j]-1)*P+i];
        }
        if(currentCost<minCost)
        {
            minCost = currentCost;
            minP = i;
        }
    }
    assert(minCost == 868);
    fin.close();
}
void testMaxFlow()
{
    {
        kingo::Graph graph(2);
        graph.addEdge(0,1,100);
        assert(graph.MaxFlow(0,1)==100);
    }

    {
        kingo::Graph graph(4);
        graph.addDirectEdge(0,1,10000);
        graph.addDirectEdge(1,2,1);
        graph.addDirectEdge(0,2,10000);
        graph.addDirectEdge(2,3,10000);
        graph.addDirectEdge(1,3,10000);
        assert(graph.MaxFlow(0,3)==20000);
        graph.addDirectEdge(0,3,10);
        assert(graph.MaxFlowIncrment(0,3)==10);
    }
}
int main(int argc,char *argv[])
{
    cout << "test Topo..." << endl;
    testTopo();
    cout << "test Prim..." << endl;
    testPrim();
    cout << "test Dijkstra..." << endl;
    testDijkstra();
    cout << "test Floyd..." << endl;
    testFloyd();
    cout << "test MaxFlow..." << endl;
    testMaxFlow();
    cout << "All Passed!" << endl;
	return 0;
}

