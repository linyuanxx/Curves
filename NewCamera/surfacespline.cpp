#include "surfacespline.h"

SurfaceSpline::SurfaceSpline()
{
    this->_tolerance = 5.f;
    this->_numbers = 3;
}

void SurfaceSpline::inputData(QVector<QVector<QVector3D> > &sp)
{
    this->_sp.clear();
    this->_sp = sp;
}
//曲面拟合
/*
  *取横向拟合出来的第一条曲线作为 横向的标准节点矢量， 及后面的拟合曲线精度不去考虑，
  *将第一条曲线的节点矢量与控制点个数赋值到后面拟合计算中。
  *纵向的计算方法与这个相同
  *
  *这个demo 只进行数值的运算，不显示每条曲线的计算过程
  */
void SurfaceSpline::approxSurface()
{
    QVector<QVector3D> ct;
    // fisrt fitting;
    for(int i=1; i<_sp.size(); i++)
    {
        ct.clear();
        linefunction.setPoint(_sp[i]);
        if(i == 0)
        {
            linefunction.toleranceFitting(_tolerance);
            linefunction.getControlPoints(ct);
            linefunction.getKnot(_hkt);
        }else
        {
            linefunction.knotnumFitting(_hkt, _sp[0].size()-1);
            linefunction.getControlPoints(ct);
        }
        _cp.push_back(ct);
    }
    ct.clear();
    // second fitting
    for(int i=0; i<_cp[0].size(); i++)
    {
        QVector<QVector3D> vl;
        for(int k=0; k<_cp.size(); k++)
        {
            vl.push_back(_cp.at(k).at(i));
        }
        ct.clear();
        linefunction.setPoint(vl);
        if(i == 0)
        {
            linefunction.toleranceFitting(_tolerance);
            linefunction.getControlPoints(ct);
            linefunction.getKnot(this->_vkt);
        }else
        {
            linefunction.knotnumFitting(_vkt, _vcp[0].size()-1);
            linefunction.getControlPoints(ct);
        }
        this->_vcp.push_back(ct);
    }
}

/*
  *拟合曲面
  *统计每条曲线的所有参数；
  *
 */
void SurfaceSpline::statisticSurface()
{

}

void SurfaceSpline::ordinarySurface(QLinkedList<QVector3D> &ap)
{
    QVector<float> dvm;
    QVector<float> dhm;
    for(float sv=0.f; sv <= 1.f; sv += 0.01f)
    {
        linefunction.setKnot(this->_vkt, this->_cp.size()-1);
        linefunction.calNi(sv,dvm);
        for(float sh=0.f; sh <= 1.f; sh += 0.01f)
        {
            linefunction.setKnot(this->_hkt, this->_cp.at(0).size()-1);
            linefunction.calNi(sh, dhm);
            float x, y, z;
            x=y=z=0.f;
            for(int dvi=0; dvi<dvm.size(); dvi++)
            {
                for(int dhi=0; dhi<dhm.size(); dhi++)
                {
                    float tm = dvm[dvi]*dhm[dhi];
                    x += _cp[dvi][dhi].x()* tm;
                    y += _cp[dvi][dhi].y()* tm;
                    z += _cp[dvi][dhi].z()* tm;
                }
            }
            ap.push_back(QVector3D(x, y, z));
        }
    }
}

void SurfaceSpline::bubbleSurface(QLinkedList<QVector3D> &ap)
{

}
