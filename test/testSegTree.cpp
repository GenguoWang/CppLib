#include "../SegTree.h"
void testSegTree()
{
    int pos[10001];
    memset((void*)pos,0,sizeof(pos));
    pos[0] = 1;
    pos[10000] = 1;
    kingo::SegTree st(0,10000);
    st.insert(0);
    st.insert(10000);
    int tests = 1000,l,r;
    while(tests--)
    {
        int num = rand()%9000+1;
        if(pos[num]) continue;
        cout << "find     " << num << endl;
        st.find(num,l,r);
        cout << "find     " << num << endl;
        int ll = num,rr=num;
        while(pos[ll]==0)ll--;
        while(pos[rr]==0)rr++;
        st.insert(num);
        pos[num] = 1;
        assert(l==ll&&r==rr);
    }
}
int main()
{
    testSegTree();
    cout << "Passed " << endl;
    return 0;    
}




