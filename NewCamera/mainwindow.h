#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glform.h"
#include "loadfile.h"
#include "linespline.h"
#include "surfacespline.h"
#include "pmdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void fileRead();
    void showContour();
    void showSource();

    //line  bspline;
    void ordinaryLine();
    void bubbleLine();
    //surface bspline;
    void ordinarySurface();
    void bubbleSurface();

    //paramter set;
    void showDialog();

    void redisplayoline(float);
    void redisplaybline(float);
    void redisplayosurface(float);
    void redisplaybsurface(float);

private:
    Ui::MainWindow *ui;
    GLForm *glf;
    LoadFile loadfile;
    LineSpline linebs;
    SurfaceSpline surfbs;
    PmDialog *pm;  //�������ã�

    QVector<QVector3D> pt;
    QVector<QVector<QVector3D> > contour;
};

#endif // MAINWINDOW_H
