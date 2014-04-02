#ifndef GLFORM_H
#define GLFORM_H

#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QLinkedList>
#include <QVector3D>
#include <QVector>
//namespace Ui {
//class GLForm;
//}

class GLForm : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit GLForm(QWidget *parent = 0);
    ~GLForm();

    void setPoint(QLinkedList<QVector3D> _pt);
    void setPoint(QVector<QVector3D> _pt);
    void setContour(QVector<QVector<QVector3D> > _pt);

private:
    void findEyePoint();

public slots:
    void clearData();

protected:
    //opengl draw function
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    //mouse control function
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
private:
   // Ui::GLForm *ui;
    QLinkedList<QVector3D> pt;
    QVector<QVector3D> spt;
    QVector<QVector<QVector3D> > contour;
    //窗口控制；
    //控制视角
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    QPoint lastPos;

    GLfloat numSteps; //近、远
    GLfloat hSteps;   //水平方向移动
    GLfloat vSteps;   //竖直方向移动

    float eyex, eyey, eyez;
};

#endif // GLFORM_H
