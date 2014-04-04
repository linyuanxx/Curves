#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glf = new GLForm;
    this->setCentralWidget(glf);

    this->pm = new PmDialog;
    //�����ļ���
    connect(this->ui->readaction, SIGNAL(triggered()), this, SLOT(fileRead()));
    //�����ʾ���ݣ�
    connect(this->ui->actionClear, SIGNAL(triggered()), this->glf, SLOT(clearData()));
    //��ʾԭʼ��Ⱥ���ݣ�
    connect(this->ui->actionSource, SIGNAL(triggered()), this, SLOT(showSource()));
    //��ʾ�ȸ��ߣ�
    connect(this->ui->actioncontour, SIGNAL(triggered()), this, SLOT(showContour()));

    //bspline line
    connect(this->ui->actionOrdinary, SIGNAL(triggered()), this, SLOT(ordinaryLine()));
    //bspline bubble line
    connect(this->ui->actionBubble, SIGNAL(triggered()), this, SLOT(bubbleLine()));

    //bspline surface
    connect(this->ui->actionsurodinary, SIGNAL(triggered()), this, SLOT(ordinarySurface()));
    //bspline bubble surface
    connect(this->ui->actionBubble_2, SIGNAL(triggered()), this, SLOT(bubbleSurface()));

    //paramter widget;
    connect(this->ui->actionParam_dialog, SIGNAL(triggered()), this, SLOT(showDialog()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileRead()
{
    QString filename = QFileDialog::getOpenFileName(this, "Read Model", "/home/linyuan/modelfiles");
    this->loadfile.setFileName(filename);
    this->loadfile.getPoints(pt);
    //this->loadfile.getContours(contour, LoadFile::AU);
    this->loadfile.getContour(contour);
    this->glf->setPoint(pt);
}

void MainWindow::showSource()
{
    this->glf->setPoint(pt);
}

void MainWindow::showContour()
{
    this->glf->setContour(contour);
}

void MainWindow::ordinaryLine()
{
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayosurface(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybsurface(float)));
    //disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayoline(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybline(float)));
    connect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayoline(float)));
    QLinkedList<QVector3D> ap;
    for(int i=0; i<contour.size(); i++)
    {
        QVector<QVector3D> mp;
        linebs.setPoint(contour[i]);
        linebs.toleranceFitting(5.0);
        linebs.ordinaryCurves(mp);
        for(int k=0; k<mp.size(); k++)
            ap.push_back(mp[k]);
    }
    this->glf->setPoint(ap);
}

void MainWindow::bubbleLine()
{
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayosurface(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybsurface(float)));
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayoline(float)));
    //disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybline(float)));
    connect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybline(float)));
    QLinkedList<QVector3D> ap;
    for(int i=0; i<contour.size(); i++)
    {
        QVector<QVector3D> mp;
        linebs.setPoint(contour[i]);
        linebs.toleranceFitting(5.0);
        linebs.bubbleCurves(mp);
        for(int k=0; k<mp.size(); k++)
            ap.push_back(mp[k]);
    }
    this->glf->setPoint(ap);
}

void MainWindow::ordinarySurface()
{
    //disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayosurface(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybsurface(float)));
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayoline(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybline(float)));
    connect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayosurface(float)));
    QLinkedList<QVector3D> ap;
    this->surfbs.inputData(contour);
    this->surfbs.approxSurface();
    this->surfbs.ordinarySurface(ap);
    this->glf->setPoint(ap);

}

void MainWindow::bubbleSurface()
{
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayosurface(float)));
   // disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybsurface(float)));
    disconnect(this->pm, SIGNAL(ovalueChanged(float)), this, SLOT(redisplayoline(float)));
    disconnect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybline(float)));
    connect(this->pm, SIGNAL(bbvalueChanged(float)), this, SLOT(redisplaybsurface(float)));
    QLinkedList<QVector3D> ap;
    this->surfbs.inputData(contour);
    this->surfbs.approxSurface();
    this->surfbs.bubbleSurface(ap);
    this->glf->setPoint(ap);
}

void MainWindow::showDialog()
{
    this->pm->show();
}

void MainWindow::redisplayoline(float osteps)
{
    linebs.setOsteps(osteps);
    QLinkedList<QVector3D> ap;
    for(int i=0; i<contour.size(); i++)
    {
        QVector<QVector3D> mp;
        linebs.setPoint(contour[i]);
        linebs.toleranceFitting(5.0);
        linebs.ordinaryCurves(mp);
        for(int k=0; k<mp.size(); k++)
            ap.push_back(mp[k]);
    }
    this->glf->setPoint(ap);
}

void MainWindow::redisplaybline(float distance)
{
    this->linebs.setDistance(distance);
    QLinkedList<QVector3D> ap;
    for(int i=0; i<contour.size(); i++)
    {
        QVector<QVector3D> mp;
        linebs.setPoint(contour[i]);
        linebs.toleranceFitting(5.0);
        linebs.bubbleCurves(mp);
        for(int k=0; k<mp.size(); k++)
            ap.push_back(mp[k]);
    }
    this->glf->setPoint(ap);
}

void MainWindow::redisplayosurface(float osteps)
{
    QLinkedList<QVector3D> ap;
    this->surfbs.setOsteps(osteps);
    this->surfbs.ordinarySurface(ap);
    this->glf->setPoint(ap);
}

void MainWindow::redisplaybsurface(float distance)
{
    QLinkedList<QVector3D> ap;
    this->surfbs.setDistance(distance);
    this->surfbs.bubbleSurface(ap);
    this->glf->setPoint(ap);
}
