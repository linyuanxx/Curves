#ifndef LINESPLINE_H
#define LINESPLINE_H
#include "bspline_function.h"
#include <QVector3D>
#include <QVector>
#include <QLinkedList>
//线条拟合,曲面拟合

class LineSpline
{
public:
    LineSpline();
    //input:
    void setPoint(const QVector<QVector3D> &line);
    //输入节点矢量与控制点个数-1；
    void setKnot(const QVector<float> kt, int np);

    //output:
    //给定一个容差值进行拟合
    void toleranceFitting(float tolerance);
    //给定控制点个数拟合， num为控制点最大下标值；
    void numberFitting(int num);
    //给定控制节点与控制点个数计算；
    void knotnumFitting(QVector<float> _dn, int num);

    //曲线参数输出；
    void getControlPoints(QVector<QVector3D> &cpt);
    void getKnot(QVector<float> &kt);

    //output: 绘制曲线或曲面上的点
    void ordinaryCurves(QVector<QVector3D> &ap);
    void bubbleCurves(QVector<QVector3D> &ap);

    //计算节点基底函数数值；
    void calNi(float um, QVector<float> &ni); //计算基底函数；
    void calNi2(float um, QVector<float> &ni);
private:
    //曲线 基本组成元素计算
    void calDu();  // 计算数据源点对应的参数值；
    void calKnot(); //计算节点矢量；
    void calApproxi();
    QVector3D pointOnCurves(float s); //输入参数计算点；

    //曲线拟合
    void bubblePointOnCurves(float s1, float s2);
private:
    //input:
    QVector<QVector3D> _line;  //原始数据点；

    //output:
    QVector<QVector3D> _cpt; //控制点
    QVector<float> _kt;  //节点矢量；
    //曲线的描述值；
    QVector<float> du;  //保存这个点对应的参数值；

    int n; //最高的控制点下标；
    int p; //曲线的次数； 固定为3次；

    int MinSrcN; // most min number of the source data;
    //output:
    float _distance;
    QVector<QVector3D> _ap; //临时存储输出bubble数据点。
};

#endif // LINESPLINE_H
