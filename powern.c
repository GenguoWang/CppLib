#include <stdlib.h>
#include <stdio.h>
void cacu(int a1[],int a2[],int res[])
{
    int p[4];
    p[0] = a1[0]*a2[0]+a1[0+1]*a2[0+2];
    p[0+1] = a1[0]*a2[0+1]+a1[0+1]*a2[0+3];
    p[0+2] = a1[0+2]*a2[0]+a1[0+3]*a2[0+2];
    p[0+3] = a1[0+2]*a2[0+1]+a1[0+3]*a2[0+3];
    for(int i=0;i<4;++i)res[i] = p[i];
}
int main()
{
    int n;
    scanf("%d",&n);
    int cnt = 0;
    int tmp  = n;
    while(tmp>0)
    {
        tmp = tmp >> 1;
        cnt++;
    }
    int* p = (int *)malloc(sizeof(int)*cnt*4);
    p[0] = 1;
    p[1] = 1;
    p[2] = 1;
    p[3] = 0;
    int nn,mm;
    for(int i=1;i<cnt;++i)
    {
        cacu(p+4*i-4,p+4*i-4,p+4*i);
    }
    int res[4];
    res[0] = 1;
    res[1] = 1;
    res[2] = 1;
    res[3] = 0;
    cnt = 0;
    while(n>0)
    {
        if(n%2)
        {
            cacu(p+cnt*4,res,res);
        }
        n = n>>1;
        cnt++;
    }
    printf("%d\n",res[3]);
    free(p);
}
