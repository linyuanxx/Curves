#ifndef LOADFILE_H
#define LOADFILE_H

#include <QFile>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QVector3D>
//can load .obj...which the datatype
//is like this "x y z" or "v x y z"
//按照x y z的最大值方向 选取等高线；

class LoadFile
{
public:
    LoadFile(const QString &filename);
    LoadFile();
    enum SortType{SX, SY, SZ, AU};
    enum MaxType{XMAX, YMAX, ZMAX};
    void setFileName(const QString &filename);
    void getPoints(QVector<QVector3D> &pt);
    void getContours(QVector<QVector<QVector3D> > &contour, LoadFile::SortType flag = LoadFile::AU);

    //datatype have got the lines;
    void getContour(QVector<QVector<QVector3D> > &contour);

    void pickContourLine(LoadFile::SortType flags = LoadFile::AU);
private:
    void fileProcess();
    void process_line(const QString &line);
    void pickContourSx();
    void pickContourSy();
    void pickContourSz();
    void pickContourAu();
    void secondMax(MaxType &flag); // 提取第二个最大值的方向；
    void firstMax(MaxType &flag); //提取最大值的方向


    void process_linefile(const QString &line);
private:
    QString _filename;
    QVector<QVector3D> _pt;
    QVector<QVector<QVector3D> > _contour;
    QVector3D _min;
    QVector3D _max;
    float persent; //一定距离选取,控制是否在同一个等高线的选取范围；
};

#endif // LOADFILE_H
