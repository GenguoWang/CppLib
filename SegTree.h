#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

namespace kingo
{
class SegTree
{
public:
    struct Node {
        //if have left right
        //mNumber = left->rNumber, right->lNumber = mNumber+1
        //number cannot be negative
        int lNumber,mNumber,rNumber;
        int trueLeft,trueRight;
        Node *left,*right;
        Node(int l,int r):lNumber(l),rNumber(r),left(NULL),right(NULL)
        {
            trueLeft = -1;
            trueRight = -1;
        }
        Node(int l,int r,int trueLeft, int trueRight):lNumber(l),rNumber(r),left(NULL),right(NULL)
        {
            this->trueLeft = trueLeft;
            this->trueRight = trueRight;
        }
    };
    Node *root;
    SegTree(int l,int r)
    {
        root = new Node(l,r);
    }
    void find(int num,int&l,int&r)
    {
        Node*node = root;
        while(node->left != NULL)
        {
            if(num > node->mNumber)
            {
                if(node->trueLeft>=0) l = node->trueLeft;
                node = node->right;
            }
            else
            {
                if(node->trueRight>=0) r = node->trueRight;
                node = node->left;
            }
        }
    }
    void insert(int num)
    {
        Node *p = root;
        while(p->left != NULL)
        {
            if(num > p->mNumber)
            {
                if(p->trueRight==-1||num < p->trueRight)
                {
                    p->trueRight = num;
                }
                p = p->right;
            }
            else
            {
                if(p->trueLeft==-1||num > p->trueLeft)
                {
                    p->trueLeft = num;
                }
                p = p->left;
            }
        }
        int temp=(p->lNumber+p->rNumber)/2;
        while(p->lNumber != num||p->rNumber != num)
        {
            p->mNumber = temp;
            p->left = new Node(p->lNumber,temp);
            p->right = new Node(temp+1,p->rNumber);
            if(num<=temp)
            {
                if(p->trueLeft==-1||num > p->trueLeft)
                {
                    p->trueLeft = num;
                }
                p = p->left;   
            }
            else{
                if(p->trueRight==-1||num < p->trueRight)
                {
                    p->trueRight = num;
                }
                p = p->right;
            }
            temp=(p->lNumber+p->rNumber)/2;
        }
    }
    ~SegTree()
    {
        destroy(root);
    }
    private:
    void destroy(Node* node)
    {
        if(node==NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};
}
