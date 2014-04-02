#ifndef APPROXIMATION_H
#define APPROXIMATION_H
#include <QVector>
#include <QVector3D>
#include <QLinkedList>
#include "linespline.h"
#include "bspline_function.h"

//绘制图形到数据点里面。
class Approximation
{
public:
    Approximation();

    void setContour(const QVector<QVector<QVector3D> > &contour);
    void getDrawPoint(QLinkedList<QVector3D> &drawpt);
private:
    void ordinaryLineDraw();
    void bubbleLineDraw();
    void ordinarySurfaceDraw();
    void bubbleSurfaceDraw();

    void basisfunctions(int n, int p, float u, const QVector<float> &kt, QVector<float> &ni);
    void pointOnCurves(int n, int p, float u, const QVector<QVector3D> &pt,
                       const QVector<float> &kt, QVector3D &point);
    //递归函数；
    void bubbleLine(int n, int p, const QVector<QVector3D> &pt,
                     const QVector<float> &kt, float s1, float s2);

private:
    QVector<QVector<QVector3D> > _linp;
    QLinkedList<QVector3D> _drawpt;
    LineSpline splinefunction;
    float _parampace;
    float _distance;
    float _tolerance;
};

#endif // APPROXIMATION_H
