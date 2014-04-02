/*
Bspline function;
*/
#include "bspline_function.h"
#include <cmath>
#include <QDebug>
/************************************************************************/
/* �ҵ��������ڵĽ������
   input:
   n �������ĸ���-1����Ƶ�ĸ���-1��
   p ���ߴ�����
   u ������
   U ���ʸ������
   ����ֵ��
   Ϊ��������ĸ�����Ľ��ֵ��
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
/* ���㵱ǰ�Ĳ���ֵ�Ļ��׺���ֵ�� 
   input��
   i ������ǰ���ĸ����䣻
   u ����ֵ��
   p ���ߴ�����
   U ���ʸ����
   output:
   N ��������ջ��׺���ֵ��
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

//�������ߵ�������Ϣ��
//���ĳ�������µĻ��غ�����
void AllBasisFuns(int n, int p, float u, float *U, float *N)
{
    int mid = FindSpan(n, p, u, U);
    BasisFuns(mid, u, p, U, N);
}

/************************************************************************/
/* ���������ϵĵ㣻
   input��
   n ���Ƶ������
   p ���ߴ�����
   U ���ʸ����
   P ���Ƶ㣻
   u ����ֵ��
   output��
   C ����ֵ��
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
/* ֱ�Ӽ�����׺����ĵ���ֵ
   input��
   i ����˳��
   u ����ֵ��
   p ������
   n ����������
   U ���ʸ������
   output��
   ders ����ֵ����
*/
/************************************************************************/
