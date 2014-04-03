#ifndef LINESPLINE_H
#define LINESPLINE_H
#include "bspline_function.h"
#include <QVector3D>
#include <QVector>
#include <QLinkedList>
//�������,�������

class LineSpline
{
public:
    LineSpline();
    //input:
    void setPoint(const QVector<QVector3D> &line);
    //����ڵ�ʸ������Ƶ����-1��
    void setKnot(const QVector<float> kt, int np);

    //output:
    //����һ���ݲ�ֵ�������
    void toleranceFitting(float tolerance);
    //�������Ƶ������ϣ� numΪ���Ƶ�����±�ֵ��
    void numberFitting(int num);
    //�������ƽڵ�����Ƶ�������㣻
    void knotnumFitting(QVector<float> _dn, int num);

    //���߲��������
    void getControlPoints(QVector<QVector3D> &cpt);
    void getKnot(QVector<float> &kt);

    //output: �������߻������ϵĵ�
    void ordinaryCurves(QVector<QVector3D> &ap);
    void bubbleCurves(QVector<QVector3D> &ap);

    //����ڵ���׺�����ֵ��
    void calNi(float um, QVector<float> &ni); //������׺�����
    void calNi2(float um, QVector<float> &ni);
private:
    //���� �������Ԫ�ؼ���
    void calDu();  // ��������Դ���Ӧ�Ĳ���ֵ��
    void calKnot(); //����ڵ�ʸ����
    void calApproxi();
    QVector3D pointOnCurves(float s); //�����������㣻

    //�������
    void bubblePointOnCurves(float s1, float s2);
private:
    //input:
    QVector<QVector3D> _line;  //ԭʼ���ݵ㣻

    //output:
    QVector<QVector3D> _cpt; //���Ƶ�
    QVector<float> _kt;  //�ڵ�ʸ����
    //���ߵ�����ֵ��
    QVector<float> du;  //����������Ӧ�Ĳ���ֵ��

    int n; //��ߵĿ��Ƶ��±ꣻ
    int p; //���ߵĴ����� �̶�Ϊ3�Σ�

    int MinSrcN; // most min number of the source data;
    //output:
    float _distance;
    QVector<QVector3D> _ap; //��ʱ�洢���bubble���ݵ㡣
};

#endif // LINESPLINE_H
