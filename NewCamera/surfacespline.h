#ifndef SURFACESPLINE_H
#define SURFACESPLINE_H
#include <QVector3D>
#include <QLinkedList>
#include <QVector>
#include "linespline.h"
#include "bspline_function.h"

//3��B�����������


class SurfaceSpline
{
public:
    SurfaceSpline();

    void inputData(QVector<QVector<QVector3D> > &sp);

    //output all surface points;
    void ordinarySurface(QLinkedList<QVector3D> &ap);
    void bubbleSurface(QLinkedList<QVector3D> &ap);

private:
    void approxSurface();
    void statisticSurface();
private:
    QVector<QVector<QVector3D> > _sp; //��ʼ���ݵ㣻
    QVector<float> _vkt,_hkt; //ˮƽ�Ľڵ�ʸ������ֱ�Ľڵ�ʸ������

    QVector<QVector<QVector3D> > _cp; //����������Ϻ����еĿ��Ƶ㣻
    QVector<QVector<QVector3D> > _vcp; //����������Ϻ����п��Ƶ㣻

    QVector<LineSpline> _surf;
    float _tolerance; //�ݲΧ��
    float _numbers;   //����������±�ֵ��
    LineSpline linefunction;  //������ϣ�
};

#endif // SURFACESPLINE_H
