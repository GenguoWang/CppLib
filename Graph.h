#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include "heap.h"
using namespace std;
namespace kingo
{

struct Vertex;

struct Edge
{
    int weight;
    int s;
    int vertex;
};

struct Vertex
{
    int number;
    int heapIndex;
    int state;
    int weight;
    int dist, pre;
    int dTime,fTime;
    list<Edge> edge; 
};

class Graph{
private:
	int time;
public:
	typedef pair<int,int> tPair;
    typedef vector<Vertex> tV;
    typedef list<Edge> tE;
    typedef tV::iterator tVIter;
    typedef tE::iterator tEIter;
	static const int MAXINT = 0x3ffffff;
    int numberOfVertex;
	int * shortest;
    int * flowMap;
	vector<Vertex> vertex;
	enum State{NOT_VISITED,VISITING,VISITED};

	Graph(int n):numberOfVertex(n),flowMap(NULL)
	{
		vertex.resize(n);
        for(int i=0;i<n;++i) vertex[i].number=i;
		shortest = NULL;
	}
	~Graph()
	{
		if(shortest) delete [] shortest;
        if(flowMap) delete [] flowMap;
	}
	
	
	void addDirectEdge(int s,int e,int weight)
	{
		Edge edge;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);
        if(flowMap)
        {
            flowMap[s*numberOfVertex+e] = weight;
        }
	}

	void addEdge(int s,int e,int weight)
	{
		Edge edge;
        edge.s = s;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);

        edge.s = e;
		edge.vertex = s;
		edge.weight = weight;
		vertex[e].edge.push_back(edge);
        if(flowMap)
        {
            flowMap[s*numberOfVertex+e] = weight;
            flowMap[e*numberOfVertex+s] = weight;
        }
	}
    void BFS()
    {
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->dist = MAXINT;
			it->pre = -1;
		}
		for(int i = 0; i != vertex.size(); ++i)
		{
			if(vertex[i].state == NOT_VISITED)
			{
				BFS_VISIT(i);
			}
		}
    }
	void BFS_VISIT(int s)
	{
		vertex[s].state = VISITING;
		vertex[s].dist = 0;
		vertex[s].pre = -1;
		queue<Vertex *> q;
		q.push(&(vertex[s]));
		Vertex* currentVertex;
		while(!q.empty())
		{
			currentVertex = q.front();
			q.pop();
            tE &currentEdges = currentVertex->edge;
			for(tEIter it = currentEdges.begin(); it != currentEdges.end(); ++it)
			{
                Vertex &nextVertex = vertex[it->vertex];
				if(nextVertex.state == NOT_VISITED)
				{
					nextVertex.state = VISITING;
					nextVertex.dist = currentVertex->dist+1;
					nextVertex.pre = currentVertex->number;
					q.push(&nextVertex);
				}
			}
			currentVertex->state = VISITED;
		}
	}
	void DFS()
	{
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->pre = -1;
		}
		time = 0;
		for(int it = 0; it != vertex.size(); ++it)
		{
			if(vertex[it].state == NOT_VISITED)
			{
				DFS_VISIT(it);
			}
		}
	}
	void DFS_VISIT(int u)
	{
		time++;
		vertex[u].dTime = time;
		vertex[u].state = VISITING;
		for(tEIter it = vertex[u].edge.begin(); it !=vertex[u].edge.end();++it)
		{
            Vertex &nextVertex = vertex[it->vertex];
			if(nextVertex.state == NOT_VISITED)
			{
				nextVertex.pre = u;
				DFS_VISIT(nextVertex.number);
			}
		}
		vertex[u].state = VISITED;
		time++;
		vertex[u].fTime = time;
	}
	static bool topoBigger(Vertex* a, Vertex*b)
	{
		return a->fTime > b->fTime;
	}
	vector<Vertex*> Topological_sort()
	{
		//more efficient way is to make the list in DFS():insert the vertex onto the front of list when setting its fTime
		DFS();
		vector<Vertex*> topo(vertex.size());
		for(int i=0; i < vertex.size(); ++i)
		{
			topo[i] = &(vertex[i]);
		}
		sort(topo.begin(),topo.end(),topoBigger);
        /*
		for(int i=0; i < topo.size(); ++i)
		{
			cout << "Vertex:\t" << topo[i]->number << endl;
			cout << "state:\t" << topo[i]->state << endl;
			cout << "dist:\t" << topo[i]->dist << endl;
			cout << "dTime:\t" << topo[i]->dTime << endl;
			cout << "fTime:\t" << topo[i]->fTime << endl;
			cout << "pre:\t" << topo[i]->pre << endl;
			cout << endl;
		}
        */
        return topo;
	}
	struct lessKey
	{
		bool operator() (Vertex * const &a, Vertex * const &b)
		{
			return a->weight < b->weight;
		}
	};
	void Mst_Prim(int r)
	{
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->weight = MAXINT;
			it->pre = -1;
			it->state = NOT_VISITED;
            it->heapIndex = -1;
		}
		vertex[r].weight = 0;
		heap<Vertex*,vector<Vertex*>,lessKey> q;
        vertex[r].heapIndex = q.push(&(vertex[r]));
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->state = VISITED;
			for(tEIter eit = pV->edge.begin(); eit != pV->edge.end(); ++eit)
			{
                Vertex &nextVertex = vertex[eit->vertex];
				if(nextVertex.state == NOT_VISITED 
					&& eit->weight < nextVertex.weight)
				{
					nextVertex.weight = eit->weight;
					nextVertex.pre = pV->number;
					if(nextVertex.heapIndex==-1) nextVertex.heapIndex = q.push(&nextVertex);
                    else q.changeUpByIndex(nextVertex.heapIndex);
				}
			}
		}
	};
	void Dijkstra(int s)
	{
		//result is stored in vertex.weight
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->weight = MAXINT;
			it->pre = -1;
			it->state = NOT_VISITED;
            it->heapIndex = -1;
		}
		vertex[s].weight = 0;
		heap<Vertex*,vector<Vertex*>,lessKey> q;
		vertex[s].heapIndex = q.push(&(vertex[s]));
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->state = VISITED;
			for(tEIter eit = pV->edge.begin(); eit != pV->edge.end(); ++eit)
			{
                Vertex &nextVertex = vertex[eit->vertex];
				if(nextVertex.state == NOT_VISITED 
					&& pV->weight + eit->weight < nextVertex.weight)
				{
					nextVertex.weight = pV->weight + eit->weight; 
					nextVertex.pre = pV->number;
					if(nextVertex.heapIndex==-1)
                    {
                        nextVertex.heapIndex = q.push(&nextVertex);
                    }
                    else
                    {
                        q.changeUpByIndex(nextVertex.heapIndex);   
                    }
				}
			}
		}
	}
	int* Floyd()
	{
		int n = vertex.size();
		if(shortest) delete [] shortest;
		shortest = new int[n*n];
		for(int i = 0; i < n; ++i)
		{
			for(int j=0; j < n; ++j)
			{
				if(i==j) shortest[i*n+j] = 0;
				else  shortest[i*n+j] = MAXINT;
			}
		}
        for(int i=0;i < vertex.size();++i)
        {
            for(tEIter eit = vertex[i].edge.begin();eit != vertex[i].edge.end();++eit)
            {
                shortest[i * n + eit->vertex] = eit->weight;
            }
        }
		for(int k = 0; k < n; ++k)
		{
			for(int i = 0; i < n; ++i)
			{
				if(k==i) continue;
				for(int j = 0; j < n; ++j)
				{
					if(shortest[i*n+k] + shortest[k*n+j] < shortest[i*n+j])
					{
						shortest[i*n+j] = shortest[i*n+k] + shortest[k*n+j];
					}
				}
			}
		}
        return shortest;
	}
    bool MBFS(int s,int t)
    {
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->dist = MAXINT;
			it->pre = -1;
		}
        queue<Vertex*> q;
        q.push(&vertex[s]);
        vertex[s].state = VISITED;
        vertex[s].dist = 0;
        Vertex* currentVertex;
        while(!q.empty())
        {
            currentVertex = q.front();
            q.pop();
            for(tEIter it = currentVertex->edge.begin();it != currentVertex->edge.end();++it)
            {
                Vertex &nextVertex = vertex[it->vertex];
                if(nextVertex.state == NOT_VISITED && flowMap[currentVertex->number * numberOfVertex + nextVertex.number] > 0)
                {
                    q.push(&nextVertex);
                    nextVertex.dist = currentVertex->dist+1;
                    nextVertex.state = VISITED;
                }
            }
        }
        return vertex[t].state == VISITED;
    }
    int MDFS(int x,int t, int flow)
    {
        if(x==t || !flow) return flow;
        int sum = 0,u;
        Vertex &currentVertex = vertex[x];
        for(tEIter it = currentVertex.edge.begin();it != currentVertex.edge.end();++it)
        {
            Vertex & nextVertex = vertex[it->vertex];
            if(nextVertex.dist == currentVertex.dist+1 
             && (u = MDFS(it->vertex,t,min(flow,flowMap[x*numberOfVertex+it->vertex]))) > 0)
             {
                flowMap[x*numberOfVertex+it->vertex] -= u;
                flowMap[it->vertex*numberOfVertex+x] += u;
                sum += u;
                flow -= u;
                if(!flow) break;
             }
        }
        return sum;
    }
    int getAugment(int s, int t)
    {
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->dist = MAXINT;
			it->pre = -1;
		}
        queue<Vertex*> q;
        q.push(&vertex[s]);
        vertex[s].state = VISITED;
        Vertex* currentVertex;
        while(!q.empty())
        {
            currentVertex = q.front();
            q.pop();
            if(currentVertex->number == t) break;
            for(tEIter it = currentVertex->edge.begin();it != currentVertex->edge.end();++it)
            {
                Vertex &nextVertex = vertex[it->vertex];
                if(nextVertex.state == NOT_VISITED && flowMap[currentVertex->number * numberOfVertex + nextVertex.number] > 0)
                {
                    q.push(&nextVertex);
                    nextVertex.pre = currentVertex->number;
                    nextVertex.state = VISITED;
                }
            }
        }
        if(vertex[t].pre == -1) return -1;
        int augment = MAXINT;
        int node = t,flow,pre;
        while((pre=vertex[node].pre) != -1)
        {
            flow = flowMap[pre*numberOfVertex+node];
            if(flow < augment) augment = flow;
            node = pre;
        }
        node = t;
        while((pre=vertex[node].pre) != -1)
        {
            flowMap[pre*numberOfVertex+node] -= augment;
            flowMap[node*numberOfVertex+pre] += augment;
            node = pre;
        }
        return augment;
    }
    int MaxFlowIncrment(int s,int t)
    {
        return MaxFlow(s,t,true);
    }
    int MaxFlow(int s, int t,bool increment=false)
    {
        int n = numberOfVertex;
        bool hasData = (flowMap!=NULL);
        if(flowMap==NULL)
        {
            flowMap = new int[n*n];
        }
        if(!increment || !hasData)
        {
            for(int i = 0; i < n; ++i)
            {
                for(int j=0; j < n; ++j)
                {
                    flowMap[i*n+j] = 0;
                }
            }
            for(int i=0;i < n;++i)
            {
                for(tEIter eit = vertex[i].edge.begin();eit != vertex[i].edge.end();++eit)
                {
                    flowMap[i * n + eit->vertex] = eit->weight;
                }
            }
        }
        int augment;
        int maxflow=0;
        /*
        while(MBFS(s,t))
        {
            maxflow += MDFS(s,t,MAXINT);
        }
        */
        while((augment=getAugment(s,t))>0)
        {
            maxflow += augment;
        }
        return maxflow;
    }
	void printVertex()
	{
		for(int i=0; i < vertex.size(); ++i)
		{
			cout << "Vertex:\t" << i << endl;
			cout << "state:\t" << vertex[i].state << endl;
			cout << "dist:\t" << vertex[i].dist << endl;
			cout << "dTime:\t" << vertex[i].dTime << endl;
			cout << "fTime:\t" << vertex[i].fTime << endl;
			cout << "pre:\t" << vertex[i].pre << endl;
			cout << endl;
		}
	}
};
}
