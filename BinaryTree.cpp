#include <iostream>
#include <stdlib.h>
using namespace std;
class BinaryTree
{
    public:
        typedef int DataType;
        struct node
        {
            DataType weight;
            node *left;
            node *right;
            node *parent;
            node()
            {
                left = NULL;
                right = NULL;
                parent = NULL;
            }
        };
   private:
        node * mRoot;
    public:
        BinaryTree()
        {
            mRoot = NULL;
        }
        void insert(DataType number)
        {
            node * pNode = mRoot,*preNode = NULL;
            while(pNode != NULL)
            {
                preNode = pNode;
                if(pNode->weight > number) pNode = pNode->left;
                else pNode = pNode->right;
            }
            node *cNode = new node();
            cNode->parent = preNode;
            cNode->weight = number;
            if(preNode == NULL)
            {
                mRoot = cNode;
            }
            else if(number > preNode->weight)
            {
                preNode->right = cNode;
            }
            else
            {
                preNode->left = cNode;
            }
        }
        node* search(DataType number)
        {
            return search(mRoot,number);
        }
        node* search(node * pNode, DataType number)
        {
            while(pNode != NULL && pNode->weight != number)
            {
                if(number < pNode->weight) pNode = pNode->left;
                else pNode = pNode->right;
            }
            return pNode;
        }
        node * min()
        {
            return min(mRoot);
        }
        node * max()
        {
            return max(mRoot);
        }
        node* min(node* pNode)
        {
            while(pNode != NULL && pNode->left != NULL) pNode = pNode->left;
            return pNode;
        }
        node* max(node* pNode)
        {
            while(pNode != NULL && pNode->right != NULL) pNode = pNode->right;
            return pNode;
        }
        node* nextNode(node* pNode)
        {
            if(pNode->right != NULL) return min(pNode->right);
            node * p = pNode->parent;
            while(p!=NULL && pNode == p->right)
            {
                pNode = p;
                p = p->parent;
            }
            return p;
        }
        ~BinaryTree()
        {
            clear(mRoot);
        }
        void clear(node * pNode)
        {
            if(pNode == NULL) return;
            clear(pNode->left);
            clear(pNode->right);
            delete pNode;
        }
        void walkMid()
        {
            node *temp[1000];
            node *p;
            int top = 0;
            if(mRoot == NULL) return;
            p = mRoot;
            while(p != NULL) {
                temp[top++] = p;
                p = p->left;
            }
            while(top > 0)
            {
                p = temp[--top];
                visit(p);
                p = p->right;
                while(p != NULL)
                {
                    temp[top++] = p;
                    p = p->left;
                }
            }
        }
        void visit(node * p)
        {
            cout << p->weight << endl;
        }
        void transplant(node *oldNode,node * newNode)
        {
            if(oldNode->parent == NULL) mRoot = newNode;
            else if(oldNode == oldNode->parent->left)
            {
                oldNode->parent->left = newNode;
            }
            else
            {
                oldNode->parent->right = newNode;
            }
            if(newNode != NULL) newNode->parent = oldNode->parent;
        }
        void remove(node *pNode)
        {
            if(pNode->left == NULL)
            {
                transplant(pNode,pNode->right);
                delete pNode;
            }
            else if(pNode->right == NULL)
            {
                transplant(pNode,pNode->left);
                delete pNode;
            }
            else
            {
                node *p = min(pNode->right);
                if(p->parent != pNode)
                {
                    transplant(p,p->right);
                    p->right = pNode->right;
                    p->right->parent = p;
                }
                transplant(pNode,p);
                p->left = pNode->left;
                p->left->parent = p;
                delete pNode;
            }
        }
};

int main(int argc,char ** argv)
{
    BinaryTree bt;
    for(int i=0; i < 100; ++i) bt.insert(rand()%1000);
    bt.walkMid();
    cout <<"max" << bt.max()->weight << endl;
    /*
    BinaryTree::node *p = bt.min();
    while(p != NULL)
    {
        cout << p->weight << endl;
        p = bt.nextNode(p);
    }*/
    BinaryTree bb;
    bb.insert(4);
    bb.insert(3);
    bb.insert(8);
    bb.insert(1);
    bb.insert(2);
    bb.insert(6);
    bb.insert(7);
    bb.insert(10);
    bb.insert(11);
    bb.walkMid();
    bb.remove(bb.search(7));
    bb.remove(bb.search(10));
    bb.remove(bb.search(11));
    bb.remove(bb.search(4));
    bb.walkMid();
    return 0;
}
