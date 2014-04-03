#include <cassert>
#include "../KMP.h"
using namespace std;
void testKMP()
{
    vector<int> res = kingo::KMP("wggloveggw","love");
    assert(res.size() == 1);
    assert(res[0] == 3);
    res = kingo::KMP("abababababa","aba");
    assert(res.size() == 5);
    for(int i=0;i<res.size();++i)assert(res[i]==2*i);
}
int main()
{
    testKMP();
    cout << "All Passed!" << endl;
    return 0;
}

