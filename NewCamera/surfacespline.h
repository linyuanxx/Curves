#ifndef SURFACESPLINE_H
#define SURFACESPLINE_H
#include <QVector3D>
#include <QLinkedList>
#include <QVector>
#include "linespline.h"
#include "bspline_function.h"

//3次B样条曲面拟合


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
    QVector<QVector<QVector3D> > _sp; //初始数据点；
    QVector<float> _vkt,_hkt; //水平的节点矢量，垂直的节点矢量。。

    QVector<QVector<QVector3D> > _cp; //横向曲线拟合后所有的控制点；
    QVector<QVector<QVector3D> > _vcp; //纵向曲线拟合后所有控制点；

    QVector<LineSpline> _surf;
    float _tolerance; //容差范围；
    float _numbers;   //顶点数最大下标值；
    LineSpline linefunction;  //线条拟合；
};

#endif // SURFACESPLINE_H
