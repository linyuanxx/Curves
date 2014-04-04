#include "glform.h"
#include "ui_glform.h"
#include <QGLFormat>
#include <QMouseEvent>
#include <QDebug>
#include <qmath.h>
#include <GL/glu.h>

GLForm::GLForm(QWidget *parent) :
    QGLWidget(parent)//,
  //ui(new Ui::GLForm)
{
    //ui->setupUi(this);
    rotationX  =   0.0f;
    rotationY  =   0.0f;
    rotationZ  =   0.0f;

    numSteps   =   0.0f;
    hSteps     =   0.0f;
    vSteps     =   0.0f;

    eyex = 0.f;
    eyey = 0.f;
    eyez = 0.f;
}

GLForm::~GLForm()
{
    //delete ui;
}

void GLForm::setPoint(QLinkedList<QVector3D> _pt)
{
    this->pt.clear();
    this->pt = _pt;
    this->updateGL();
}

void GLForm::setPoint(QVector<QVector3D> _pt)
{
    this->spt.clear();
    this->spt =_pt;
    this->findEyePoint();
    this->updateGL();
}

void GLForm::setContour(QVector<QVector<QVector3D> > _contour)
{
    this->contour.clear();
    this->contour = _contour;
    this->updateGL();
}

void GLForm::findEyePoint()
{
    float minx, miny, minz;
    float maxx, maxy, maxz;

    maxx = maxy = maxz = -32767.f;
    minx = miny = minz = 32767.f;

    float x, y, z;
    for(int i=0; i<this->spt.size(); i++)
    {
        x = spt[i].x();
        y = spt[i].y();
        z = spt[i].z();
        if(x > maxx)
            maxx = x;
        if(x < minx)
            minx = x;
        if(y > maxy)
            maxy = y;
        if(y < miny)
            miny = y;
        if(z > maxz)
            maxz = z;
        if(z < minz)
            minz = z;
    }
    eyex = (maxx + minx)/2;
    eyey = (maxy + miny)/2;
    eyez = (maxz + minz)/2;
    // qDebug()<<minx << miny<<minz<<maxx<<maxy<<maxz;
    //    eyex = maxx/2;
    //    eyey = maxy/2;
    //    eyez = maxz/2;
}

void GLForm::initializeGL()
{
    glClearColor(0.0,0.0,0.0,1.0);
    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightPosition[] = {0.0f, 0.0f, -200.0f, 1.0f};
    GLfloat LightPosition2[] = {20.0f, 20.0f, 20.0f, 1.0f};
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition2);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GLForm::resizeGL(int w, int h)
{
    if(h==0)
        h = 1;
    glViewport(0,0,w,h);
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    //gluPerspective(45.0, w/h, 0.1, 3500.0);
    //    glOrtho(-1000,1000,-1000,1000,-1000,1000);
    //   // glFrustum(-1000, 1000, -1000, 1000, 10, 2000);
    //    glMatrixMode(GL_MODELVIEW);


    float aspectRatio;
    const float zNear = 0.1; //1
    const float zFar = 3000; //2
    const float fieldOfView = 60.0; //3
    GLfloat size;
    //CGRect frame = [[UIScreen mainScreen] bounds]; //4

    aspectRatio=(float)this->width()/(float)this->height(); //5


    //Set the OpenGL projection matrix.
    glMatrixMode(GL_PROJECTION); //6
    glLoadIdentity();
    float md = 3.14159f;
    float radians = md*fieldOfView/180;
    size = zNear * tanf(radians / 2.0); //7
    glFrustum(-size, size, -size /aspectRatio, size /aspectRatio, zNear, zFar); //8
    //glViewport(0, 0, w, h); //9
    //Make the OpenGL ModelView matrix the default.
    glMatrixMode(GL_MODELVIEW); //10
    glLoadIdentity();
}
/*
第1、2行指定了近裁面和远裁面的距离。这两个值的意思是，任何远于1000或近于0.1的对象都将被过滤掉。你可能会问一千什么？就是一千！单位看你自己设想。你可以把它想象成光年，或者英尺，都无所谓。不信的话你自己随便设置一下试试。

第3行设定视角为60度。

第4行获取屏幕的尺寸大小。

第5行根据屏幕的尺寸计算最终屏幕的纵横比例。它的高度和宽度的值决定了相对高度的视域（FOV），如果将其翻转的话，将变成相对于宽度的视域。如果我们要设置一个60度视域，就像一个宽角度镜头，那么它将基于窗口的高度而非宽度。当渲染到一个非正方形的屏幕上时尤为重要。

由于glfrustumf影响的是投影矩阵，所以我们需要确认将当前矩阵从模型视图矩阵设置成投影矩阵。第6行就是要做这个滴。

第7行计算锥形视角的左右上下的限制值。你可以把它想象成3D空间中的虚拟窗口。原点在屏幕中央，所以x轴和y轴的值都是从-size到+size。这就是为什么会有GLKMathDegreesToRadians (fieldOfView) / 2.0将窗口分为两部分——视角的角度是从-30度到+30度的。乘以zNear就可以计算出近剪裁面在坐标轴各个方向上的大小。这就是正切函数的作用了，眼睛在z轴上，到原点的距离是zNear，视域被z轴分为上下两部分各为30度，所以就可以明白size就是近剪裁面在x和y轴上的长度。

第8行将计算的左右上下以及近剪裁面和远剪裁面的值传进glFrustumf函数。这里下边和上边的值都除以了aspectRatio（屏幕宽高比），而左右边没有，这是因为调用glLoadIdentity函数标准化投影矩阵的时候将所有的顶点数据都标准化到了-1~1的范围内，屏幕宽度和高度实际大小不一样，但都被标准化成了1。所以如果左右值和上下值一样的话得到的就是一个宽度比较大而高度比较小的长方形，而不是预期的正方形，所以左右值不变，而上下值要除以宽高比。

第9行用来设置视口，一般为屏幕的大小。不过你可以根据需要来设置坐标和宽度、高度。

第10行为将当前的矩阵从投影矩阵设置为模型视图矩阵。
 */

void GLForm::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef( hSteps ,  vSteps , -1500+numSteps );
    glTranslatef(eyex, eyey, -eyez);
    // gluLookAt(1.0, 1.0,1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationX, 1.0, 0.0, 0.0); //旋转时重绘用
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    //glPushMatrix();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();


    glBegin(GL_POINTS);

    // source points;
    glColor3f(1.0, 0.0, 0.2);
    for(int i=0; i<spt.size(); i++)
    {
        glVertex3f(spt[i].x(), spt[i].y(), spt[i].z());
    }
    // source contour points;
    glColor3f(1.0, 0.2, 0.0);
    for(int i=0; i<contour.size(); i ++)
    {
        for(int j=0; j<contour[i].size(); j++)
            glVertex3f(contour.at(i).at(j).x(), contour.at(i).at(j).y(), contour.at(i).at(j).z());
    }
    //reconstruction curves points;
    glColor3f(0.0, 0.5, 1.0);
    QVector3D vpt;
    QLinkedListIterator<QVector3D> lis(pt);
    while(lis.hasNext())
    {
        vpt =lis.next();
        glVertex3f(vpt.x(), vpt.y(), vpt.z());
    }
    glEnd();
    // glPopMatrix();
    glFlush();
}

void GLForm::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLForm::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton) {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        rotationX += 180 * dy;
        rotationZ += 180 * dx;
        updateGL();
    }
    lastPos = event->pos();
}

void GLForm::mouseReleaseEvent(QMouseEvent *event)
{
}

void GLForm::wheelEvent(QWheelEvent *event)
{
    float numDegrees = event->delta() / 8;
    numSteps += ( numDegrees / 15 ) * 10; //乘以5是为了使拉近拉远的速度变快

    if (event->orientation() == Qt::Vertical)
    {
        updateGL();
    }
}

void GLForm::clearData()
{
    this->pt.clear();
    this->spt.clear();
    this->contour.clear();
    this->updateGL();
}
