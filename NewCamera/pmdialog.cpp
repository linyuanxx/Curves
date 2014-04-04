#include "pmdialog.h"
#include "ui_pmdialog.h"
#include <QDebug>
PmDialog::PmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PmDialog)
{
    ui->setupUi(this);
//    this->ui->horizontalSlider_oline->setMinimum(1);
//    this->ui->horizontalSlider_oline->setMaximum(100);
//    this->ui->horizontalSlider_bbline->setMinimum(1);
//    this->ui->horizontalSlider_bbline->setMaximum(100);

//    this->ui->horizontalSlider_oline->setValue(10);
//    this->ui->horizontalSlider_bbline->setValue(500);
    connect(this->ui->horizontalSlider_oline, SIGNAL(valueChanged(int)), this, SLOT(setoBoxValue()));
    connect(this->ui->horizontalSlider_bbline, SIGNAL(valueChanged(int)), this, SLOT(setbbBoxValue()));
}

PmDialog::~PmDialog()
{
    delete ui;
}

void PmDialog::setoBoxValue()
{
   int vo = this->ui->horizontalSlider_oline->value();
   this->osteps = (vo*1.f)/1000.f;   //param 0.001 -> 0.1;
   this->ui->doubleSpinBox_oline->setValue(osteps);
   emit ovalueChanged(osteps);
}

void PmDialog::setbbBoxValue()
{
   int vb = this->ui->horizontalSlider_bbline->value();
   this->distance = (vb*1.f)/100.f;
   this->ui->doubleSpinBox_bbline->setValue(distance);
   emit bbvalueChanged(distance);
}
