#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T12:20:08
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
TARGET = NewCamera
TEMPLATE = app

#-------------------------------------
#win32 {
#   LIBS += -L"$$(GLC_LIB_DIR)/lib" -lGLC_lib1
#    INCLUDEPATH += "$$(GLC_LIB_DIR)/include"
#}
#--------------------------------------------

INCLUDEPATH += /usr/local/include\
               /usr/local/include/opencv\
               /usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_highgui.so\
        /usr/local/lib/libopencv_imgproc.so\
        /usr/local/lib/libopencv_core.so

LIBS += -lglut -lGLU

SOURCES += main.cpp\
        widget.cpp \
    loadfile.cpp \
    linespline.cpp \
    bspline_function.cpp \
    surfacespline.cpp \
    glform.cpp \
    mainwindow.cpp \
    pmdialog.cpp

HEADERS  += widget.h \
    loadfile.h \
    linespline.h \
    bspline_function.h \
    surfacespline.h \
    glform.h \
    mainwindow.h \
    pmdialog.h

FORMS    += widget.ui \
    glform.ui \
    mainwindow.ui \
    pmdialog.ui
