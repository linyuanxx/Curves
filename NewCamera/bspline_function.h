#ifndef BSPLINE_FUNCTION_H
#define BSPLINE_FUNCTION_H
int FindSpan(int n, int p, float u, float *U);
void BasisFuns(int i, float u, int p, float *U, float *N);

//输入曲线的所有信息；
//输出某个参数下的基地函数；
void AllBasisFuns(int n, int p, float u, float *U, float *N);
void CurvePoint(int n, int p, float *U, float *P, float u, float &C);
#endif // BSPLINE_FUNCTION_H
