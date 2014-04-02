#include "approximation.h"

Approximation::Approximation()
{
    this->_parampace = 0.02f;
    this->_distance = 5.f;
    this->_tolerance = 5.f;
}

void Approximation::setContour(const QVector<QVector<QVector3D> > &contour)
{
    this->_linp.clear();
    this->_linp = contour;
}

void Approximation::getDrawPoint(QLinkedList<QVector3D> &drawpt)
{
    drawpt = this->_drawpt;
    this->_drawpt.clear();
}

void Approximation::basisfunctions(int n, int p, float u, const QVector<float> &kt, QVector<float> &ni)
{
   float *fkt = new float[kt.size()];
   for(int i=0; i<kt.size(); i++)
   {
       fkt[i] = kt[i];
   }
   float *Ni = new float[n+1];
   AllBasisFuns(n, p, u, fkt, Ni);
   for(int i=0; i<n+1; i++)
   {
       ni.push_back(Ni[i]);
   }
   delete fkt;
   delete Ni;
}

void Approximation::pointOnCurves(int n, int p, float u, const QVector<QVector3D> &pt, const QVector<float> &kt, QVector3D &point)
{
    float dx, dy, dz;
    float *fkt = new float[kt.size()];
    for(int i=0; i<kt.size(); i++)
        fkt[i] = kt[i];
    float *nP = new float[n+1];
    //¼ÆËãx
    for(int i=0; i<n+1; i++)
        nP[i] = pt[i].x();
    CurvePoint(n, p, fkt, nP, u, dx);
    //y
    for(int i=0; i<n+1; i++)
        nP[i] = pt[i].y();
    CurvePoint(n, p, fkt, nP, u, dy);
    //z
    for(int i=0; i<n+1; i++)
        nP[i] = pt[i].z();
    CurvePoint(n, p, fkt, nP, u, dz);

    point = QVector3D(dx, dy, dz);
}

void Approximation::ordinaryLineDraw()
{
    splinefunction.setPoint(this->_linp[0]);
    QVector<QVector3D> cp;
    QVector<float> kt;
    splinefunction.toleranceFitting(this->_tolerance);
    splinefunction.getControlPoints(cp);
    splinefunction.getKnot(kt);
    int n = cp.size()-1;
    int p = 3;
    QVector3D dst;
    for(float u=0.f; u<=1.f; u+=0.02f)
    {
      this->pointOnCurves(n, p, u, cp, kt, dst);
      this->_drawpt.push_back(dst);
    }
}

void Approximation::bubbleLine(int n, int p, const QVector<QVector3D> &pt,
                                const QVector<float> &kt, float s1, float s2)
{
    QVector3D pn1, pn2;
    QVector3D dv;
    pointOnCurves(n, p, s1, pt, kt, pn1);
    pointOnCurves(n, p, s2, pt, kt, pn2);
    dv = pn1 - pn2;
    float length = dv.length();
    if(length < this->_distance)
        return;
    else
    {
         QVector3D temp;
         pointOnCurves(n, p, (s1+s2)/2, pt, kt, temp);
         this->_drawpt.push_back(temp);
         bubbleLine(n, p, pt, kt, s1, (s1+s2)/2);
         bubbleLine(n, p, pt, kt, (s1+s2)/2, s2);
    }
}

void Approximation::bubbleLineDraw()
{
    splinefunction.setPoint(this->_linp[0]);
    QVector<QVector3D> cp;
    QVector<float> kt;
    splinefunction.toleranceFitting(this->_tolerance);
    splinefunction.getControlPoints(cp);
    splinefunction.getKnot(kt);
    int n = cp.size() - 1;
    int p = 3;
    QVector3D pn1, pn2;
    pointOnCurves(n, p, 0.f, cp, kt, pn1);
    pointOnCurves(n, p, 1.f, cp, kt, pn2);
    this->_drawpt.push_back(pn1);
    this->_drawpt.push_back(pn2);
    this->bubbleLine(n, p, cp, kt, 0.f, 1.f);
}


void Approximation::ordinarySurfaceDraw()
{
    QVector<QVector<QVector3D> > _hvpt;
    QVector<float> vkt;
    QVector<float> hkt;

    for(int i=0; i<this->_linp.size(); i++)
    {
        QVector<QVector3D> cpt;
        splinefunction.setPoint(this->_linp[i]);

    }
}

void Approximation::bubbleSurfaceDraw()
{

}
