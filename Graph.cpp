#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;
#include <stdlib.h>
#include <iostream>
//#include <assert.h>
using namespace std;
struct Vertex;
	struct Edge{
		int weight;
		int vertex;
	};
struct Vertex{
		int number;
		int heapIndex;
		int color;
		int key;
		int dist, pre;
		int dTime,fTime;
		list<Edge> edge; 
	};
class heap
{
	typedef Vertex * DataType;
	private:
        int mSize;
        int mMaxsize;
        DataType * mData;
        bool mBig;
        bool mHasData;
        int left(int index)
        {
            return 2*index;
        }
        int right(int index)
        {
            return 2*index+1;
        }
        int parent(int index)
        {
            return index/2;
        }
        void swap(int i,int j)
        {
            DataType temp;
			mData[i]->heapIndex = j;
			mData[j]->heapIndex = i;
            temp = mData[i];
            mData[i] = mData[j];
            mData[j] = temp;
        }
        bool bigger(int i, int j)
        {
			if(mBig) return mData[i]->key > mData[j]->key;//mBig´ó¶¥¶Ñ
			else return mData[i]->key < mData[j]->key;//Ð¡¶¥ÍÆ
        }
		void myAssert(bool flag)
		{
			//assert(flag);
		}
    public:
        heap(int maxsize,bool big)
        {
            myAssert(maxsize > 0);
            mMaxsize = maxsize;
            mBig = big;
            mHasData = true;
            mData = new DataType[maxsize+1]; //mData[0] is not used
            mSize = 0;
        }
        heap(DataType * data,int size,bool big)
        {
            myAssert(data!=NULL && size > 0);
            mMaxsize = size;
            mBig = big;
            mHasData = false;
            mData = data;
            mSize = size;
            build();
        }
        ~heap()
        {
            if(mHasData)delete[]mData;
        }
        void heapify(int index)
        {
            int l = left(index),r = right(index);
            int largest = index;
            if(l<=mSize && bigger(l,largest))
            {
                largest = l;
            }
            if(r<=mSize && bigger(r,largest))
            {
                largest = r;
            }
            if(index != largest)
            {
                swap(index,largest);
                heapify(largest);
            }
        }
        void build()
        {
            for(int i= mSize/2; i >=1;--i)
            {
                heapify(i);
            }
        }
        void sort()
        {
            for(int i= mSize; i >= 2; i--)
            {
                swap(1,i);
                mSize--;
                heapify(1);
            }
            mSize = 0;
        }
        DataType top()
        {
            myAssert(mSize >= 1);
            return mData[mSize];
        }
        DataType pop()
        {
            myAssert(mSize >= 1);
            DataType data = mData[1];
            //mData[1] = mData[mSize];
			swap(1,mSize);
            mSize--;
            heapify(1);
            return data;
        }
        void insert(DataType number)
        {
            myAssert(mSize<mMaxsize);
            mSize++;
            mData[mSize] = number;
			number->heapIndex = mSize;
            int i = mSize;
            while(i > 1 && bigger(i,parent(i)))
            {
                swap(i,parent(i));
                i = parent(i);
            }
        }
		void changeUp(int index,DataType number)
		{
			myAssert(index>=0 && index <= mSize);
			mData[index] = number;
			number->heapIndex = index;
			int i = index;
			while(i > 1&& bigger(i,parent(i)))
			{
				swap(i,parent(i));
				i = parent(i);
			}
		}
		int size()
		{
			return mSize;
		}
};
class Graph{
private:
	int time;
public:
	Graph(int n)
	{
		vertex.resize(n);
		shortest = 0;
	}
	~Graph()
	{
		if(shortest) delete [] shortest;
	}
	enum Color{WHITE,GRAY,BLACK};
	
	static const int MAXINT = 0x3ffffff;
	
	vector<Vertex> vertex;
	typedef pair<int,int> tPair;
	typedef map<tPair,int> tMap;
	tMap weight;
	int * shortest;
	void addEdgeDirct(int s,int e,int weight)
	{
		Edge edge;
		edge.vertex = e;
		edge.weight = weight;
		this->weight[pair<int,int>(s,e)] = weight;
		vertex[s].edge.push_back(edge);
	}
	void addEdge(int s,int e,int weight)
	{
		Edge edge;
		edge.vertex = e;
		edge.weight = weight;
		this->weight[pair<int,int>(s,e)] = weight;
		vertex[s].edge.push_back(edge);
		edge.vertex = s;
		edge.weight = weight;
		this->weight[pair<int,int>(e,s)] = weight;
		vertex[e].edge.push_back(edge);
	}
	void BFS(int s)
	{
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->color = WHITE;
			it->dist = MAXINT;
			it->pre = -1;
		}
		vertex[s].color = GRAY;
		vertex[s].dist = 0;
		vertex[s].pre = -1;
		queue<int> q;
		q.push(s);
		int u;
		while(!q.empty())
		{
			u = q.front();
			q.pop();
			for(list<Edge>::iterator it = vertex[u].edge.begin(); it != vertex[u].edge.end(); ++it)
			{
				if(vertex[it->vertex].color == WHITE)
				{
					vertex[it->vertex].color = GRAY;
					vertex[it->vertex].dist = vertex[u].dist+1;
					vertex[it->vertex].pre = u;
					q.push(it->vertex);
				}
			}
			vertex[u].color = BLACK;
		}
	}
	void DFS()
	{
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->color = WHITE;
			it->pre = -1;
		}
		time = 0;
		for(int it = 0; it != vertex.size(); ++it)
		{
			if(vertex[it].color == WHITE)
			{
				DFS_VISIT(it);
			}
		}
	}
	void DFS_VISIT(int u)
	{
		time++;
		vertex[u].dTime = time;
		vertex[u].color = GRAY;
		for(list<Edge>::iterator it = vertex[u].edge.begin(); it !=vertex[u].edge.end();++it)
		{
			if(vertex[it->vertex].color == WHITE)
			{
				vertex[it->vertex].pre = u;
				DFS_VISIT(it->vertex);
			}
		}
		vertex[u].color = BLACK;
		time++;
		vertex[u].fTime = time;
	}
	static bool topoBigger(Vertex* a, Vertex*b)
	{
		return a->fTime > b->fTime;
	}
	void Topological_sort()
	{
		//more efficient way is to make the list in DFS():insert the vertex onto the front of list when setting its fTime
		DFS();
		vector<Vertex*> topo(vertex.size());
		for(int i=0; i < vertex.size(); ++i)
		{
			topo[i] = &(vertex[i]);
		}
		sort(topo.begin(),topo.end(),topoBigger);
		for(int i=0; i < topo.size(); ++i)
		{
			cout << "Vertex:\t" << i << endl;
			cout << "color:\t" << topo[i]->color << endl;
			cout << "dist:\t" << topo[i]->dist << endl;
			cout << "dTime:\t" << topo[i]->dTime << endl;
			cout << "fTime:\t" << topo[i]->fTime << endl;
			cout << "pre:\t" << topo[i]->pre << endl;
			cout << endl;
		}
	}
	struct lessPrim
	{
		bool operator() (Vertex * const &a, Vertex * const &b)
		{
			//*a = *b;
			return a->key < b->key;
		}
	};
	void Mst_Prim(int r)
	{
		int i=0;
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->number = i++;
			it->key = MAXINT;
			it->pre = -1;
			it->color = WHITE;
		}
		vertex[r].key = 0;
		heap q(vertex.size(),false);
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			q.insert(&(*it));
		}
		set<Vertex*,lessPrim>::iterator setit;
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->color = BLACK;
			cout << "Vertex " << pV->number << endl;
			for(list<Edge>::iterator it = pV->edge.begin(); it != pV->edge.end(); ++it)
			{
				if(vertex[it->vertex].color == WHITE 
					&&weight.find(pair<int,int>(pV->number,it->vertex)) != weight.end() 
					&& weight[pair<int,int>(pV->number,it->vertex)] < vertex[it->vertex].key)
				{
					//q.erase(&(vertex[it->vertex]));
					vertex[it->vertex].key = weight[pair<int,int>(pV->number,it->vertex)];
					vertex[it->vertex].pre = pV->number;
					q.changeUp(vertex[it->vertex].heapIndex,&vertex[it->vertex]);
					//q.insert(&(vertex[it->vertex]));
				}
			}
		}

	};
	void Dijkstra(int s)
	{
		//result is stored in vertex.key
		int i=0;
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->number = i++;
			it->key = MAXINT;
			it->pre = -1;
			it->color = WHITE;
		}
		vertex[s].key = 0;
		this->addEdge(s,s,0);
		heap q(vertex.size(),false);
		for(vector<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
		{
			q.insert(&(*it));
		}
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->color = BLACK;
			cout << "Vertex " << pV->number << " "<< pV->key<<endl;
			if(pV->key == MAXINT) break;
			for(list<Edge>::iterator it = pV->edge.begin(); it != pV->edge.end(); ++it)
			{
				if(vertex[it->vertex].color == WHITE 
					&&weight.find(pair<int,int>(pV->number,it->vertex)) != weight.end() 
					&& pV->key + weight[pair<int,int>(pV->number,it->vertex)] < vertex[it->vertex].key)
				{
					vertex[it->vertex].key = pV->key + weight[pair<int,int>(pV->number,it->vertex)]; 
					vertex[it->vertex].pre = pV->number;
					q.changeUp(vertex[it->vertex].heapIndex,&vertex[it->vertex]);
				}
			}
		}
	}
	void Floyd()
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
		for(tMap::iterator it = weight.begin(); it != weight.end();++it)
		{
			shortest[it->first.first * n + it->first.second] = it->second;
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
	}
	void printVertex()
	{
		for(int i=0; i < vertex.size(); ++i)
		{
			cout << "Vertex:\t" << i << endl;
			cout << "color:\t" << vertex[i].color << endl;
			cout << "dist:\t" << vertex[i].dist << endl;
			cout << "dTime:\t" << vertex[i].dTime << endl;
			cout << "fTime:\t" << vertex[i].fTime << endl;
			cout << "pre:\t" << vertex[i].pre << endl;
			cout << endl;
		}
	}
};

int main(int argc,char *argv[])
{
	/*
	Graph graph(6);
	graph.addEdge(0,1,0);
	graph.addEdge(1,2,0);
	graph.addEdge(2,3,0);
	graph.addEdge(0,3,0);
	graph.addEdge(3,1,0);
	graph.addEdge(4,2,0);
	graph.addEdge(4,5,0);
	graph.addEdge(5,5,0);
	//graph.BFS(0);
	//graph.printVertex();
	graph.Topological_sort();
	
	set<int> testSet;
	for(int i=0; i < 100; ++i) testSet.insert(rand()%1000);
	for(set<int>::iterator it = testSet.begin(); it != testSet.end();++it)
	{
		cout << *it << endl;
	}
	*/
	Graph graph(6);
	graph.addEdge(0,1,4);
	graph.addEdge(1,2,7);
	graph.addEdge(2,3,9);
	graph.addEdge(3,4,2);
	graph.addEdge(4,5,1);
	graph.addEdge(0,5,3);
	graph.addEdge(0,3,100);
	//graph.Mst_Prim(0);
	graph.Dijkstra(0);
	graph.Floyd();
	cout << graph.shortest[0*6+3] << endl;
	return 0;
}
