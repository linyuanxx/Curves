#include "loadfile.h"
#include <QTextStream>
#include <QMap>
#include <QDebug>
LoadFile::LoadFile()
{
    this->_min = QVector3D(32767,32767,32767);
    this->_max = QVector3D(-32767,-32767,-32767);
    this->persent = 0.05;
}

//输出原始数据；
void LoadFile::getPoints(QVector<QVector3D> &pt)
{
    pt.clear();
    this->fileProcess();
    pt = _pt;
    qDebug()<<"data Point size: "<<pt.size();
}

//输出等高线数据；
void LoadFile::getContours(QVector<QVector<QVector3D> > &contour, LoadFile::SortType flag)
{
    contour.clear();
    this->pickContourLine(flag);
    contour = this->_contour;
}

void LoadFile::getContour(QVector<QVector<QVector3D> > &contour)
{
    contour.clear();
    _pt.clear();
    QFile file(_filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList linelist = line.split(" ");
        if(linelist.size() < 3)
        {
            this->_contour.push_back(_pt);
            this->_pt.clear();
        }else
        this->process_linefile(line);
    }
    contour = this->_contour;
}

void LoadFile::process_linefile(const QString &line)
{
    QStringList strlist = line.split(" ");
    if(strlist.size()>4)
        return;
    float va[3];
    bool ok; //判断第一段字符是否为一个浮点数值；
    float m1 = strlist.at(0).toFloat(&ok);
    //读取obj文件中的数值；
    if(strlist[0] == "v")// read objfile;
    {
        for(int i=1; i<strlist.size(); i++)
        {
            va[i-1] = strlist.at(i).toFloat();
        }
        this->_pt.push_back(QVector3D(va[0], va[1], va[2]));
        //statistic the minvalue and maxvalue;
    }
    else if(ok)
    {
        for(int i=0; i<strlist.size(); i++)
        {
            va[i] = strlist.at(i).toFloat();
        }
        this->_pt.push_back(QVector3D(va[0], va[1], va[2]));
    }
}

LoadFile::LoadFile(const QString &filename)
{
    this->_filename = filename;
}

void LoadFile::setFileName(const QString &filename)
{
    this->_pt.clear();
    this->_contour.clear();
    this->_filename = filename;
}

//读入原始点数据；
void LoadFile::fileProcess()
{
    QFile file(_filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        process_line(line);
    }
}

void LoadFile::process_line(const QString &line)
{
    QStringList strlist = line.split(" ");
    if(strlist.size()>4)
        return;
    float va[3];
    bool ok; //判断第一段字符是否为一个浮点数值；
    float m1 = strlist.at(0).toFloat(&ok);
    //读取obj文件中的数值；
    if(strlist[0] == "v")// read objfile;
    {
        for(int i=1; i<strlist.size(); i++)
        {
            va[i-1] = strlist.at(i).toFloat();
        }
        this->_pt.push_back(QVector3D(va[0], va[1], va[2]));
        //statistic the minvalue and maxvalue;
        if(va[0] > _max.x())
            _max.setX(va[0]);
        if(va[0] < _min.x())
            _min.setX(va[0]);

        if(va[1] > _max.y())
            _max.setY(va[1]);
        if(va[1] < _min.y())
            _min.setY(va[1]);

        if(va[2] > _max.z())
            _max.setZ(va[2]);
        if(va[2] < _min.z())
            _min.setZ(va[2]);
    }
    else if(ok)
    {
        for(int i=0; i<strlist.size(); i++)
        {
            va[i] = strlist.at(i).toFloat();
        }
        this->_pt.push_back(QVector3D(va[0], va[1], va[2]));
        if(va[0] > _max.x())
            _max.setX(va[0]);
        if(va[0] < _min.x())
            _min.setX(va[0]);

        if(va[1] > _max.y())
            _max.setY(va[1]);
        if(va[1] < _min.y())
            _min.setY(va[1]);

        if(va[2] > _max.z())
            _max.setZ(va[2]);
        if(va[2] < _min.z())
            _min.setZ(va[2]);
    }
}

//
void LoadFile::secondMax(MaxType &flag)
{
    int dx = _max.x() - _min.x();
    int dy = _max.y() - _min.y();
    int dz = _max.z() - _min.z();
    if((dx-dy)*(dy-dz)>= 0)
        flag = LoadFile::YMAX;
    else if((dy-dx)*(dx-dz)>= 0)
        flag = LoadFile::XMAX;
    else
        flag = LoadFile::ZMAX;
}

void LoadFile::firstMax(MaxType &flag)
{
    int dx = _max.x() - _min.x();
    int dy = _max.y() - _min.y();
    int dz = _max.z() - _min.z();

    int max = dx;
    flag = LoadFile::XMAX;
    if(dy > max)
    {
        max = dy;
        flag = LoadFile::YMAX;
    }
    if(dz > max)
    {
        max = dz;
        flag = LoadFile::ZMAX;
    }
}

void LoadFile::pickContourLine(LoadFile::SortType flags)
{
    if(_pt.size()<5)
        return;
    switch(flags)
    {
    case LoadFile::SX:
        this->pickContourSx();
        break;
    case LoadFile::SY:
        this->pickContourSy();
        break;
    case LoadFile::SZ:
        this->pickContourSz();
        break;
    case LoadFile::AU:
        this->pickContourAu();
        break;
    default:
        this->pickContourAu();
        break;
    }
}

void LoadFile::pickContourSx()
{
    float vu, vd;
    vd = _min.x();
    vu = _max.x();
    float fvd = vd + persent;
    int di=0;
    QMap<float, QVector3D> mp;
    MaxType flag;
    this->secondMax(flag);
    while(fvd <= vu)
    {
        mp.clear();
        //process;
        for(int i=0; i<_pt.size(); i++)
        {
            if(_pt[i].x() <= fvd && _pt[i].x() > vd)  // vd<pt<=fvd
            {
                switch(flag)
                {
                case YMAX:
                    mp.insert(_pt[i].y(), _pt[i]);
                    break;
                case ZMAX:
                    mp.insert(_pt[i].z(), _pt[i]);
                    break;
                }
            }
        }
        QVector<QVector3D> temv;
        for(int k=0; k<mp.size(); k++)
        {
            temv.push_back(mp.values().at(k));
        }
        vd = fvd;
        fvd += persent;
        this->_contour.push_back(temv);
    }

}

void LoadFile::pickContourSy()
{
    float vu, vd;
    vd = _min.y();
    vu = _max.y();
    float fvd = vd + persent;

    QMap<float, QVector3D> mp;
    MaxType flag;
    this->secondMax(flag);
    while(fvd <= vu)
    {
        mp.clear();
        //process;
        for(int i=0; i<_pt.size(); i++)
        {
            if(_pt[i].y() <= fvd && _pt[i].y() >= vd)  // vd<pt<=fvd
            {
                switch(flag)
                {
                case XMAX:
                    mp.insert(_pt[i].x(), _pt[i]);
                    break;
                case ZMAX:
                    mp.insert(_pt[i].z(), _pt[i]);
                    break;
                }
            }
        }
        QVector<QVector3D> temv;
        for(int k=0; k<mp.size(); k++)
        {
            temv.push_back(mp.values().at(k));
        }
        vd = fvd;
        fvd += persent;
        this->_contour.push_back(temv);
    }
}

void LoadFile::pickContourSz()
{
    float vu, vd;
    vd = _min.z();
    vu = _max.z();
    float fvd = vd + persent;
    int di=0;
    QMap<float, QVector3D> mp;
    MaxType flag;
    this->secondMax(flag);
    while(fvd <= vu)
    {
        mp.clear();
        //process;
        for(int i=0; i<_pt.size(); i++)
        {
            if(_pt[i].z() <= fvd && _pt[i].z() > vd)  // vd<pt<=fvd
            {
                switch(flag)
                {
                case XMAX:
                    mp.insert(_pt[i].x(), _pt[i]);
                    break;
                case YMAX:
                    mp.insert(_pt[i].y(), _pt[i]);
                    break;
                }
            }
        }
        QVector<QVector3D> temv;
        for(int k=0; k<mp.size(); k++)
        {
            temv.push_back(mp.values().at(k));
        }
        vd = fvd;
        fvd += persent;
        this->_contour.push_back(temv);
    }
}

//这里添加自动等高线选取；
void LoadFile::pickContourAu()
{
    //思路1，取x y z最长的方向为等高线
    //    int dx = _max.x() - _min.x();
    //    int dy = _max.y() - _min.y();
    //    int dz = _max.z() - _min.z();

    //    int max = dx;
    //    int state = 1;
    //    if(dy > max)
    //    {
    //        max = dy;
    //        state = 2;
    //    }
    //    if(dz > max)
    //    {
    //        max = dz;
    //        state = 3;
    //    }
    MaxType flag;
    this->firstMax(flag);
    switch(flag)
    {
    case XMAX:
        this->pickContourSx();
        break;
    case YMAX:
        this->pickContourSy();
        break;
    case ZMAX:
        this->pickContourSz();
        break;
    default:
        this->pickContourSy();
        break;
    }
}
