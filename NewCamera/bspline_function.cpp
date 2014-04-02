/*
Bspline function;
*/
#include "bspline_function.h"
#include <cmath>
#include <QDebug>
/************************************************************************/
/* 找到参数所在的结点区间
   input:
   n 基函数的个数-1或控制点的个数-1；
   p 曲线次数；
   u 参数；
   U 结点矢量链表；
   返回值：
   为计算的在哪个区间的结果值；
*/
/************************************************************************/

int FindSpan(int n, int p, float u, float *U)
{
    if(fabs(u - U[n+1]) < 0.0000001) return n;
    int low = p;
    int high = n+1;
    int mid = (low+high)/2;
    while(u < U[mid] || u >= U[mid+1])
    {
        if(u < U[mid])high = mid;
        else low = mid;
        mid = (low + high)/2;
        //qDebug()<<"LLLL"<<endl<<mid<<u<<U[mid];
    }
    return mid;
}

/************************************************************************/
/* 计算当前的参数值的基底函数值； 
   input：
   i 参数当前在哪个区间；
   u 参数值；
   p 曲线次数；
   U 结点矢量；
   output:
   N 计算的最终基底函数值；
*/
/************************************************************************/

void BasisFuns(int i, float u, int p, float *U, float *N)
{
    N[0] = 1.f;
    float *left = new float[p+1];
    float *right = new float[p+1];
    float saved = 0.f;
    for(int j=1; j <= p; j++)
    {
        left[j] = u - U[i+1-j];
        right[j] = U[i+j] - u;
        saved = 0.f;
        for(int r=0; r<j; r++)
        {
            float temp = N[r]/(right[r+1]+left[j-r]);
            N[r] = saved + right[r+1]*temp;
            saved = left[j-r]*temp;
        }
        N[j] = saved;
    }
    delete left;
    delete right;
}

//输入曲线的所有信息；
//输出某个参数下的基地函数；
void AllBasisFuns(int n, int p, float u, float *U, float *N)
{
    int mid = FindSpan(n, p, u, U);
    BasisFuns(mid, u, p, U, N);
}

/************************************************************************/
/* 计算曲线上的点；
   input：
   n 控制点个数；
   p 曲线次数；
   U 结点矢量；
   P 控制点；
   u 参数值；
   output：
   C 曲线值；
*/
/************************************************************************/

void CurvePoint(int n, int p, float *U, float *P, float u, float &C)
{
    float *N = new float[p+1];
    int span = FindSpan(n, p, u, U);
    BasisFuns(span, u, p, U, N);
    C = 0.f;
    for(int i=0; i<=p; i++)
        C = C + N[i]*P[span-p+i];
    delete N;
}



/************************************************************************/
/* 直接计算基底函数的导数值
   input：
   i 区间顺序；
   u 参数值；
   p 次数；
   n 基数个数；
   U 结点矢量链表；
   output：
   ders 导数值链表；
*/
/************************************************************************/
