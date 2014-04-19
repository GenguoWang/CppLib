#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define NUM 100
void qsort(int * begin,int * end)
{
    if(begin>=end) return;
    int *left = begin+1;
    int *right = end;
    int temp;
    //must use <= to guarantee *right<=temp when loop ended
    while(left <= right)
    {
        while(*left <= *right && *left<=*begin)left++;
        while(*left <= *right && *right>*begin)right--;
        if(left<right)
        {
        temp = *left;
        *left = *right;
        *right = temp;
        }
    }
    temp = *right;
    *right = *begin;
    *begin = temp;
    qsort(begin,right-1);
    qsort(right+1,end);
}
template<typename _T>
void qsort1(_T begin, _T end)
{
    if(begin>=end) return;
    _T i =begin, j = end;
    while(i<j)
    {
        while(i<j && *i<=*j)j--;
        swap(*i,*j);
        while(i<j && *i<=*j)i++;
        swap(*i,*j);
    }
    qsort1(begin,i-1);
    qsort1(i+1,end);
}
int main()
{
    int a[NUM];
    for(int i=0;i<NUM;++i)
    {
        a[i] =rand()%1000;
    }
    qsort(a,a+NUM-1);
    for(int i=0;i<NUM;++i)
    {
        cout << a[i] << endl;
        if(i && a[i-1]>a[i])
        {
            cout << "error" << endl;
            break;
        }
    }
}
