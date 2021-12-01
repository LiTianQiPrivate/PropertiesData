#include "CurveSetting.h"
#include "ui_CurveSetting.h"
#include <QAction>
#include <QDebug>
#include "Business.h"
#include "RightUpWidget.h"
CurveSetting::CurveSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveSetting)
{
    ui->setupUi(this);
    QDoubleValidator *m_double =new QDoubleValidator;
    QIntValidator *m_int = new QIntValidator;
    ui->xMinEdit->setValidator(m_double);
    ui->xMaxEdit->setValidator(m_double);
    ui->xStepEdit->setValidator(m_int);
    ui->yMinEdit->setValidator(m_double);
    ui->yMaxEdit->setValidator(m_double);
    ui->yStepEdit->setValidator(m_int);
    ui->doubleSpinBox->setEnabled(false);
    ui->doubleSpinBox->setValue(8.00);
    ui->doubleSpinBox->setSingleStep(0.01);
    ui->doubleSpinBox_2->setEnabled(false);
    ui->doubleSpinBox_2->setValue(-180.00);
    ui->doubleSpinBox_2->setSingleStep(0.2);
}

CurveSetting::~CurveSetting()
{
    delete ui;
}
/**
 * @brief CurveSetting::setCurveType
 * 动态添加曲线类型
 * @param object
 */
void CurveSetting::setCurveType(ModelBase *object)
{
    QString str = object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE));
    for(int i=0;i< ui->comboBoxDataType->count();i++)
    {
        QString s = ui->comboBoxDataType->itemText(i);
        if(str == s)
        {
            return ;
        }
    }
    ui->comboBoxDataType->addItem(str);
}
/**
 * @brief CurveSetting::on_radioButton_clicked
 * 频率checkBox
 * @param checked
 */
void CurveSetting::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->doubleSpinBox->setEnabled(true);
        double fps = ui->doubleSpinBox->text().toDouble();
        Business::getBusiness()->getRightUpWidget()->setCurveFps(fps);
    }
    else
    {
        ui->doubleSpinBox->setEnabled(false);
    }
}
/**
 * @brief CurveSetting::on_radioButton_2_clicked
 * 方位checkbox
 * @param checked
 */
void CurveSetting::on_radioButton_2_clicked(bool checked)
{
    if(checked)
    {
        ui->doubleSpinBox_2->setEnabled(true);
    }
    else
    {
        ui->doubleSpinBox_2->setEnabled(false);
    }
}
/**
 * @brief CurveSetting::on_checkBox_clicked
 * x轴范围设置
 * @param checked
 */
void CurveSetting::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
         double xMin = ui->xMinEdit->text().toDouble();
         double xMax = ui->xMaxEdit->text().toDouble();
         int xStep = ui->xStepEdit->text().toInt();
         Business::getBusiness()->getRightUpWidget()->setXTypeCurve(xMin,xMax,xStep);
         ui->checkBox->setCheckState(Qt::Unchecked);
    }
}
/**
 * @brief CurveSetting::on_checkBox_2_clicked
 * y轴范围设置
 * @param checked
 */
void CurveSetting::on_checkBox_2_clicked(bool checked)
{
    if(checked)
    {
         double yMin = ui->yMinEdit->text().toDouble();
         double yMax = ui->yMaxEdit->text().toDouble();
         int yStep = ui->yStepEdit->text().toInt();
         Business::getBusiness()->getRightUpWidget()->setYTypeCurve(yMin,yMax,yStep);
         ui->checkBox->setCheckState(Qt::Unchecked);
    }
}
/**
 * @brief CurveSetting::on_doubleSpinBox_valueChanged
 *  频率设置
 * @param arg1
 */
void CurveSetting::on_doubleSpinBox_valueChanged(double arg1)
{
    if(ui->doubleSpinBox->isEnabled())
    {
        ui->doubleSpinBox_2->setEnabled(false);
        double fps = ui->doubleSpinBox->text().toDouble();
        Business::getBusiness()->getRightUpWidget()->setCurveFps(fps);
    }
}
/**
 * @brief CurveSetting::on_doubleSpinBox_2_valueChanged
 *  方位设置
 * @param arg1
 */
void CurveSetting::on_doubleSpinBox_2_valueChanged(double arg1)
{
    if(ui->doubleSpinBox_2->isEnabled())
    {
        ui->doubleSpinBox->setEnabled(false);
        double angle = ui->doubleSpinBox_2->text().toDouble();
        Business::getBusiness()->getRightUpWidget()->setCurvePosition(angle);
    }
}
/**
 * @brief CurveSetting::on_comboBox_x_activated
 * x轴名称设置
 * @param arg1
 */
void CurveSetting::on_comboBox_x_activated(const QString &arg1)
{
    Business::getBusiness()->getRightUpWidget()->setXName(arg1);
}
/**
 * @brief CurveSetting::on_comboBox_y_activated
 * y轴名称设置
 * @param arg1
 */
void CurveSetting::on_comboBox_y_activated(const QString &arg1)
{
    Business::getBusiness()->getRightUpWidget()->setYName(arg1);
}
