#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
namespace kingo
{
template<typename DataType,typename ContainType=vector<DataType>,typename CompType=less<DataType> >
class heap
{
	private:
        static const int INVALID_INDEX = -1;
        ContainType data;
        vector<int> dataIndex;
        vector<int> invertIndex;
        int mSize;
        CompType compare;
        int left(int index) { return 2*index; }
        int right(int index) { return 2*index+1; }
        int parent(int index) { return index/2; }
        void swap(int i,int j)
        {
            DataType temp;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            
            //change index
            int pi = invertIndex[i];
            int pj = invertIndex[j];
            int tempIndex = dataIndex[pi];
            dataIndex[pi] = dataIndex[pj];
            dataIndex[pj] = tempIndex;
            
            //change inverted index
            tempIndex = invertIndex[i];
            invertIndex[i] = invertIndex[j];
            invertIndex[j] = tempIndex;
        }
        void heapify(int index)
        {
            int l = left(index),r = right(index);
            int theIndexOfUpper = index;
            if(l<=mSize && compare(data[l],data[theIndexOfUpper]))
            {
                theIndexOfUpper = l;
            }
            if(r<=mSize && compare(data[r],data[theIndexOfUpper]))
            {
                theIndexOfUpper = r;
            }
            if(index != theIndexOfUpper)
            {
                swap(index,theIndexOfUpper);
                heapify(theIndexOfUpper);
            }
        }
        void initEmptyHeap()
        {
            mSize = 0;
            DataType zeroPos;
            data.push_back(zeroPos);
            dataIndex.push_back(0);
            invertIndex.push_back(0);
        }
        int addData(const DataType& newData)
        {
            int thisIndex;
            mSize++;
            if(mSize < data.size())
            {
                data[mSize] = newData;
                dataIndex.push_back(mSize);
                thisIndex = dataIndex.size()-1;
                invertIndex[mSize] = thisIndex;
            }
            else
            {
                data.push_back(newData);   
                dataIndex.push_back(mSize);
                thisIndex = dataIndex.size()-1;
                invertIndex.push_back(thisIndex);
            }
            return dataIndex.size()-1;
        }
        void removeLast()
        {
            dataIndex[invertIndex[mSize]] = INVALID_INDEX;
            invertIndex[mSize] = INVALID_INDEX;
            mSize--;
        }
        void changeUp(int i)
        {
            while(i > 1 && compare(data[i],data[parent(i)]))
            {
                swap(i,parent(i));
                i = parent(i);
            }
        }
    public:
        heap()
        {
            initEmptyHeap();
        }
        template<typename iterator>
        heap(iterator begin,iterator end)
        {
            initEmptyHeap();
            while(begin != end)
            {
                addData(*begin);
                ++begin;
            }
            build();
        }
        ~heap()
        {
        }
        int size()
        {
            return mSize;
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
            for(int last= mSize; last > 1; last--)
            {
                swap(1,last);
                removeLast();
                heapify(1);
            }
            removeLast();
        }
        DataType top()
        {
            return data[1];
        }
        DataType pop()
        {
            DataType topData = data[1];
            swap(1,mSize);
            removeLast();
            heapify(1);
            return topData;
        }
        int push(DataType newData)
        {
            int thisIndex = addData(newData);
            changeUp(mSize);
            return thisIndex;
        }
        void change(int index,DataType newData)
        {
            int pos = dataIndex[index];
            DataType oldData = data[pos];
            data[pos] = newData;
            if(compare(newData,oldData))
            {
                changeUp(pos);
            }
            else
            {
                heapify(pos);
            }
        }
        void changeUpByIndex(int index)
        {
            int pos = dataIndex[index];
            changeUp(pos);
        }
        void changeDownByIndex(int index)
        {
            int pos = dataIndex[index];
            heapify(pos);
        }
        ContainType& getData()
        {
            return data;
        }
        DataType getByIndex(int index)
        {
            int pos = dataIndex[index];
            return data[pos];
        }
        bool isIndexValid(int index)
        {
            if(index>=1 && index < dataIndex.size() && dataIndex[index] != INVALID_INDEX)
            {
                return true;
            }
            else return false;
        }
};
}

