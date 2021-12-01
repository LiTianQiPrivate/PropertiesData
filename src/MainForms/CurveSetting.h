#ifndef CURVESETTING_H
#define CURVESETTING_H

#include <QWidget>
#include "ModelBase.h"
namespace Ui {
class CurveSetting;
}

class CurveSetting : public QWidget
{
    Q_OBJECT

public:
    explicit CurveSetting(QWidget *parent = nullptr);
    ~CurveSetting();
    void setCurveType(ModelBase *object);
private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_comboBox_x_activated(const QString &arg1);

    void on_comboBox_y_activated(const QString &arg1);

private:
    Ui::CurveSetting *ui;
};

#endif // CURVESETTING_H
