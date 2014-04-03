#ifndef SURFACESPLINE_H
#define SURFACESPLINE_H
#include <QVector3D>
#include <QLinkedList>
#include <QVector>
#include "linespline.h"
#include "bspline_function.h"

//3��B�����������
class Point;
class CenterBox;

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

    //bubble algrithm
    QVector3D paramToPoint(float u, float v);
    void BoxDiv(CenterBox cb);

private:
    QVector<QVector<QVector3D> > _sp; //��ʼ���ݵ㣻
    QVector<float> _vkt,_hkt; //ˮƽ�Ľڵ�ʸ������ֱ�Ľڵ�ʸ������

    QVector<QVector<QVector3D> > _cp; //����������Ϻ����еĿ��Ƶ㣻
    QVector<QVector<QVector3D> > _vcp; //����������Ϻ����п��Ƶ㣻

    QVector<LineSpline> _surf;
    float _tolerance; //�ݲΧ��
    float _numbers;   //����������±�ֵ��
    LineSpline linefunction;  //������ϣ�

    //bubble output data;
    QVector<QVector3D> _bbv;
};

class Point
{
public:
    Point(float _x, float _y)
    {
        this->x = _x;
        this->y = _y;
    }

    Point ():x(0),y(0)
    {

    }

    Point(const Point &p)
    {
        this->x = p.x;
        this->y = p.y;
    }

    Point& operator=(const Point &p)
    {
        if(this == &p)
        {
            return *this;
        }else
        {
            this->x = p.x;
            this->y = p.y;
        }
    }

    float x,y;
};

class CenterBox
{
public:
    CenterBox(Point _ld, Point _ru)
    {
        this->ld = _ld;
        this->ru = _ru;
        cp = Point((ld.x+ru.x)/2, (ld.y+ru.y)/2);
    }

    CenterBox():ld(Point(0, 0)), ru(Point(0,0))
    {
        cp = Point(0,0);
    }

    CenterBox(const CenterBox &cb)
    {
        this->ld = cb.ld;
        this->ru = cb.ru;
        this->cp = this->getCenter();
    }

    CenterBox & operator= (const CenterBox &cb)
    {
        if(this == &cb)
        {
            return *this;
        }else{
            this->ld = cb.ld;
            this->ru = cb.ru;
            this->cp = this->getCenter();
        }
    }

    Point getCenter()
    {
        return cp;
    }

    Point ld, ru;
  private:
    Point cp;
};

#endif // SURFACESPLINE_H
