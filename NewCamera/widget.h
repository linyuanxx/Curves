//#ifndef WIDGET_H
//#define WIDGET_H

//#include <QWidget>
//#include <QtOpenGL>
//#include <GLC_Factory>
//#include <GLC_Viewport>
//#include <GLC_World>
//#include <GLC_Light>
//#include <GLC_MoverController>
//#include <QVector>
//#include <QVector3D>
//namespace Ui {
//    class Widget;
//}

//class Widget : public QGLWidget
//{
//    Q_OBJECT

//public:
//    explicit Widget(QWidget *parent = 0);
//    ~Widget();
//    void CreateScene();


//    void testAddSourcData();
//    //传入数据；
//    void setData(const QVector<QVector3D> &pt)
//    {
//        this->sp.clear();
//        this->sp = pt;
//    }
//protected:
//    void initializeGL();
//    void paintGL();
//    void resizeGL(int w, int h);

//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//private:
//    Ui::Widget *ui;

//    QVector<QVector3D> sp;
//    //GLC
//    GLC_Factory *m_pFactory;
//    GLC_Light m_Light;
//    QColor m_DefaultColor;
//    GLC_World m_World;
//    GLC_Viewport m_GlView;
//    GLC_MoverController m_MoverController;
//};

//#endif // WIDGET_H
