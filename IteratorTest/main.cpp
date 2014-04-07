#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <vector>
using namespace std;


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

float Pointlength(Point a, Point b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x*x+y*y);
}
vector<CenterBox> vcb;
void BoxDiv(CenterBox cb)
{
    float length = Pointlength(cb.ld, cb.ru);
   // cout<<"length: "<<length<<endl;
    if(length < 0.1)return;
    else
    {
        BoxDiv(CenterBox(cb.ld, cb.getCenter())); //ld
        BoxDiv(CenterBox(Point(cb.ld.x, cb.getCenter().y), Point(cb.getCenter().x, cb.ru.y))); //lu
        BoxDiv(CenterBox(cb.getCenter(), cb.ru)); //ru
        BoxDiv(CenterBox(Point(cb.getCenter().x, cb.ld.y), Point(cb.ru.x, cb.getCenter().y))); //rd

        vcb.push_back(cb);
//        vcb.push_back(CenterBox(cb.ld, cb.getCenter()));
//        vcb.push_back(CenterBox(Point(cb.ld.x, cb.getCenter().y), Point(cb.getCenter().x, cb.ru.y)));
//        vcb.push_back(CenterBox(cb.getCenter(), cb.ru));
//        vcb.push_back(CenterBox(Point(cb.getCenter().x, cb.ld.y), Point(cb.ru.x, cb.getCenter().y)));
    }
}

void drawCenterbox(CenterBox cb)
{
    glBegin(GL_LINES);
    glVertex2f(cb.ld.x, cb.ld.y);
    glVertex2f(cb.ld.x, cb.ru.y);

    glVertex2f(cb.ld.x, cb.ru.y);
    glVertex2f(cb.ru.x, cb.ru.y);

    glVertex2f(cb.ru.x, cb.ru.y);
    glVertex2f(cb.ru.x, cb.ld.y);

    glVertex2f(cb.ru.x, cb.ld.y);
    glVertex2f(cb.ld.x, cb.ld.y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.5, -0.25, 0.0);
    glColor3f(1.0, 0.f, 0.f);
    cout<<"size: "<<vcb.size()/4<<endl;
    for(int i=0; i<vcb.size(); i++)
    {

        drawCenterbox(vcb[i]);

//        glBegin(GL_POINTS);

//        glVertex2f(vcb[i].ld.x, vcb[i].ld.y);
//        glVertex2f(vcb[i].ru.x, vcb[i].ru.y);

//         glEnd();
     }
    glFlush();
    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutCreateWindow("test");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    cout << "Hello World!" << endl;
    cout <<"M"<<endl;
    CenterBox cb(Point(0, 0), Point(1, 1));
    BoxDiv(cb);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

