//#include "widget.h"
//#include "ui_widget.h"

//Widget::Widget(QWidget *parent) :
//    QGLWidget(parent),
//    m_pFactory(GLC_Factory::instance(this->context()))
//    ,m_Light()
//    ,m_DefaultColor()
//    ,m_World()
//    ,m_GlView(this)
//    ,m_MoverController()
//{
//    m_Light.setPosition(10.0, 10.0, 10.0);
//    m_DefaultColor.setRgbF(0.5, 0.8, 1.0, 1.0);
//    m_GlView.cameraHandle()->setIsoView();


//   CreateScene();
//    QColor repColor;
//    repColor.setRgbF(1.0, 0.11372, 0.11372, 0.0);
//    m_MoverController= m_pFactory->createDefaultMoverController(repColor, &m_GlView);
//}

//Widget::~Widget()
//{

//}

//void Widget::initializeGL()
//{
//    // OpenGL initialisation from NEHE production
//    m_GlView.initGl();
//    m_GlView.reframe(m_World.boundingBox());
//    m_GlView.setDistMinAndMax(m_World.boundingBox());
//}

//void Widget::paintGL()
//{

//    // Clear screen
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // Load identity matrix
//    glLoadIdentity();


////       glBegin(GL_LINES);
////        glVertex3f(0.0,0.0,0.0);
////        glVertex3f(100,0,0);
////       glEnd();

//    // define the light
//    m_Light.enable();
//    m_Light.glExecute();

//    // define view matrix
//    m_GlView.glExecuteCam();

//    // Display the collection of GLC_Object
//    m_World.glExecute(0, false);

//    // Display UI Info (orbit circle)
//    m_GlView.glExecute();
//    m_MoverController.drawActiveMoverRep();
//}

//void Widget::resizeGL(int w, int h)
//{
//    m_GlView.setWinGLSize(w, h);
//}

//void Widget::testAddSourcData()
//{
//    this->sp.clear();
//    int wx = 1000;
//    for(int i=0; i<5000; i++)
//    {
//        if(i%2 == 0)
//        sp.push_back(QVector3D(-rand()%wx, -rand()%wx, -rand()%wx));
//        else
//            sp.push_back(QVector3D(rand()%wx, rand()%wx, rand()%wx));
//    }
//}

//void Widget::CreateScene()
//{

//        GLC_StructOccurence* pRoot= m_World.rootOccurence();
//        GLC_StructInstance* pInstance= NULL;



//       int va = 1000;
//        // Create a box at the center of the scene
//        GLC_3DRep box(m_pFactory->createBox(0.1*va, 0.1*va, 0.1*va));
//       //GLC_3DRep box(m_pFactory->createBox(10, 10, 10));
//        box.geomAt(0)->addMaterial(new GLC_Material(m_DefaultColor));
//        pRoot->addChild(new GLC_StructInstance(box.clone()));

//        // create Z axis representation
//        GLC_3DRep cylinder(m_pFactory->createCylinder(0.02*va, 2.0*va));
//        cylinder.geomAt(0)->addMaterial(new GLC_Material(Qt::blue));
//        pRoot->addChild(new GLC_StructInstance(cylinder.clone()));

//        // create X axis representation
//        cylinder= m_pFactory->createCylinder(0.02*va, 2.0*va);
//        cylinder.geomAt(0)->addMaterial(new GLC_Material(Qt::red));
//        GLC_Matrix4x4 matRot(glc::Y_AXIS, glc::PI/2);			//Create a rotation matrix
//        pInstance= new GLC_StructInstance(cylinder.clone());
//        pInstance->move(matRot);								// move the cylinder
//        pRoot->addChild(pInstance);

//        // create Y axis representation
//        cylinder= m_pFactory->createCylinder(0.02*va, 2.0*va);
//        cylinder.geomAt(0)->addMaterial(new GLC_Material(Qt::green));
//        matRot.setMatRot(glc::X_AXIS, -glc::PI/2);								// Set rotation matrix
//        pInstance= new GLC_StructInstance(cylinder.clone());
//        pInstance->move(matRot);								// move the cylinder
//        pRoot->addChild(pInstance);

//        // Create 3 circles around axis

////        GLC_3DRep circle(m_pFactory->createCircle(2.5));
////        circle.geomAt(0)->addMaterial(new GLC_Material(Qt::red));
////        pRoot->addChild(new GLC_StructInstance(circle.clone()));

////        circle= m_pFactory->createCircle(2.5);
////        matRot.setMatRot(glc::Y_AXIS, glc::PI/2);
////        pInstance= new GLC_StructInstance(circle.clone());
////        pInstance->move(matRot);								// move the cylinder
////        pRoot->addChild(pInstance);

////        circle= m_pFactory->createCircle(2.5);
////        matRot.setMatRot(glc::X_AXIS, glc::PI/2);
////        pInstance= new GLC_StructInstance(circle.clone());
////        pInstance->move(matRot);								// move the cylinder
////        pRoot->addChild(pInstance);


//        //add points;
//        for(int i=0; i<1000; i+=10)
//        {
//        GLC_3DRep line(m_pFactory->createPoint(i, i, i));
//        pRoot->addChild(new GLC_StructInstance(line.clone()));
//        }

//        testAddSourcData();
//       for(int i=0; i<sp.size(); i++)
//       {
//           GLC_3DRep pt(m_pFactory->createPoint(sp[i].x(), sp[i].y(), sp[i].z()));
//           pRoot->addChild(new GLC_StructInstance(pt.clone()));
//       }
//}
//void Widget::mousePressEvent(QMouseEvent *e)
//{
//    if (m_MoverController.hasActiveMover()) return;
//    switch (e->button())
//    {
//    case (Qt::LeftButton):
//            m_MoverController.setActiveMover(GLC_MoverController::TrackBall, e->x(), e->y());
//            updateGL();
//            break;
//    case (Qt::RightButton):
//            m_MoverController.setActiveMover(GLC_MoverController::Pan, e->x(), e->y());
//            updateGL();
//            break;
//    case (Qt::MidButton):
//            m_MoverController.setActiveMover(GLC_MoverController::Zoom, e->x(), e->y());
//            updateGL();
//            break;

//    default:
//            break;
//    }
//}

//void Widget::mouseMoveEvent(QMouseEvent *e)
//{
//    if (not m_MoverController.hasActiveMover()) return;
//    m_MoverController.move(e->x(), e->y());
//    m_GlView.setDistMinAndMax(m_World.boundingBox());
//    updateGL();
//}

//void Widget::mouseReleaseEvent(QMouseEvent *)
//{
//    if (not m_MoverController.hasActiveMover()) return;
//    m_MoverController.setNoMover();
//    updateGL();
//}
