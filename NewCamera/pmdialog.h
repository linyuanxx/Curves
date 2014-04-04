#ifndef PMDIALOG_H
#define PMDIALOG_H

#include <QDialog>

namespace Ui {
class PmDialog;
}

class PmDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PmDialog(QWidget *parent = 0);
    ~PmDialog();

    float const getSteps()
    {
        return this->osteps;
    }

    float const getDistance()
    {
        return this->distance;
    }

public slots:
    void setoBoxValue();
    void setbbBoxValue();
 signals:
    void ovalueChanged(float);
    void bbvalueChanged(float);
private:
    Ui::PmDialog *ui;
    float osteps;
    float distance;
};

#endif // PMDIALOG_H
