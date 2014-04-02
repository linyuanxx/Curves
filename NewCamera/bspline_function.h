#ifndef BSPLINE_FUNCTION_H
#define BSPLINE_FUNCTION_H
int FindSpan(int n, int p, float u, float *U);
void BasisFuns(int i, float u, int p, float *U, float *N);

//�������ߵ�������Ϣ��
//���ĳ�������µĻ��غ�����
void AllBasisFuns(int n, int p, float u, float *U, float *N);
void CurvePoint(int n, int p, float *U, float *P, float u, float &C);
#endif // BSPLINE_FUNCTION_H
