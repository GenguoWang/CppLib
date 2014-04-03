#include <string>
#include <vector>
#include <iostream>
namespace kingo
{
std::vector<int> KMP(std::string str,std::string toFind)
{
    std::vector<int> longestSuffix(toFind.size());
    longestSuffix[0] = 0;
    int k=0;
    for(int i=1;i<toFind.size();++i)
    {
        while(k!=0 && toFind[k] != toFind[i])
        {
            k = longestSuffix[k-1];
        }
        if(toFind[k] == toFind[i])
        {
            longestSuffix[i] = ++k;
        }
        else
        {
            //means k is equal 0, no suffix is found
            longestSuffix[i] = 0;
        }
    }
    std::vector<int> res;
    k=0;
    for(int i=0;i < str.size();++i)
    {
        while(k!=0 && toFind[k] != str[i])
        {
            k = longestSuffix[k-1];
        }
        if(toFind[k] == str[i])
        {
            k++;
        }
        if(k==toFind.size())
        {
            res.push_back(i+1-k);
            k = longestSuffix[k-1];
        }
    }
    return res;
}
}
