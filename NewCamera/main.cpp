#include <QtGui/QApplication>
//#include "widget.h"
#include "glform.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // Widget w;
   // w.show();
//    QVector<QVector3D> pt;
//    for(int i=0; i<100; i++)
//        pt.push_back(QVector3D(rand()%300, rand()%300, rand()%300));
//    GLForm glf;
//    glf.setPoint(pt);
//    glf.show();



    MainWindow mw;
    mw.show();
    return a.exec();
}
