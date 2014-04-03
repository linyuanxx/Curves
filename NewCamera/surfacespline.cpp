#include "surfacespline.h"
#include <QMap>
#include <QDebug>
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
    for(int i=0; i<_sp.size(); i++)
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
            linefunction.knotnumFitting(_hkt, _cp[0].size()-1);
            linefunction.getControlPoints(ct);
        }

        _cp.push_back(ct);
    }
    // second fitting
    for(int i=0; i<_cp[0].size(); i++)
    {
        // y direction;
        QVector<QVector3D> vl;
        QVector3D svp;
        QMap<float, QVector3D> map;
        for(int k=0; k<_cp.size(); k++)
        {
            svp = _cp.at(k).at(i);
            map.insert(svp.y(), svp);
            //vl.push_back(_cp.at(k).at(i));
        }

        QMapIterator<float, QVector3D>imp(map);
        while(imp.hasNext())
        {
            vl.push_back(imp.next().value());
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
    this->approxSurface();
    QVector<float> dvm;
    QVector<float> dhm;
    for(float sv=0.f; sv <= 1.f; sv += 0.01f)
    {
        linefunction.setKnot(this->_vkt, this->_vcp.size()-1);
        linefunction.calNi(sv,dvm);
        for(float sh=0.f; sh <= 1.f; sh += 0.01f)
        {
            linefunction.setKnot(this->_hkt, this->_vcp.at(0).size()-1);
            linefunction.calNi(sh, dhm);
            float x, y, z;
            x=y=z=0.f;
            for(int dvi=0; dvi<dvm.size(); dvi++)
            {
                for(int dhi=0; dhi<dhm.size(); dhi++)
                {
                    float tm = dvm[dvi]*dhm[dhi];
                    QVector3D tv = _vcp[dvi][dhi];
                    x += tv.x()* tm;
                    y += tv.y()* tm;
                    z += tv.z()* tm;
                }
            }
            ap.push_back(QVector3D(x, y, z));
        }
    }
}

QVector3D SurfaceSpline::paramToPoint(float u, float v)
{
    QVector<float>dvm, dhm;
    linefunction.setKnot(this->_vkt, this->_vcp.size()-1);
    linefunction.calNi(v, dvm);
    linefunction.setKnot(this->_hkt, this->_vcp.size()-1);
    linefunction.calNi(u, dhm);

    float x, y, z;
    x=y=z=0.f;
    for(int dvi=0; dvi<dvm.size(); dvi++)
    {
        for(int dhi=0; dhi<dhm.size(); dhi++)
        {
            float tm = dvm[dvi]*dhm[dhi];
            QVector3D tv = _vcp[dvi][dhi];
            x += tv.x()* tm;
            y += tv.y()* tm;
            z += tv.z()* tm;
        }
    }
    return QVector3D(x, y, z);
}

void SurfaceSpline::BoxDiv(CenterBox cb)
{
    QVector3D vertice[5];
    vertice[0] = paramToPoint(cb.ld.x, cb.ld.y);
    vertice[1] = paramToPoint(cb.ld.x, cb.ru.y);
    vertice[2] = paramToPoint(cb.ru.x, cb.ru.y);
    vertice[3] = paramToPoint(cb.ru.x, cb.ld.y);
    vertice[4] = paramToPoint(cb.ld.x, cb.ld.y);
    float length[4];
    float mlength = 32767.f;
    QVector3D lev;
    for(int i=1; i<4; i++)
    {
        lev = vertice[i]-vertice[i-1];
        length[i-1] = lev.length();
        if(length[i-1] < mlength)
            mlength = length[i-1];
    }
    // qDebug()<<"LLL: "<<_bbv.size();
    if(mlength < 1.0)return;
    else
    {
        BoxDiv(CenterBox(cb.ld, cb.getCenter())); //ld
        BoxDiv(CenterBox(Point(cb.ld.x, cb.getCenter().y), Point(cb.getCenter().x, cb.ru.y))); //lu
        BoxDiv(CenterBox(cb.getCenter(), cb.ru)); //ru
        BoxDiv(CenterBox(Point(cb.getCenter().x, cb.ld.y), Point(cb.ru.x, cb.getCenter().y))); //rd

        for(int i=0; i<4; i++)
            _bbv.push_back(vertice[i]);
    }
}

void SurfaceSpline::bubbleSurface(QLinkedList<QVector3D> &ap)
{
    ap.clear();
    this->approxSurface();
    qDebug()<<_bbv.size();
    this->BoxDiv(CenterBox(Point(0,0), Point(1.f, 1.f)));

    for(int i=0; i<_bbv.size(); i++)
        ap.push_back(_bbv[i]);
}
