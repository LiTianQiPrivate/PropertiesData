#include "RightUpWidget.h"
#include "ui_RightUpWidget.h"
#include "CurvePlot.h"
#include <QDebug>
RightUpWidget::RightUpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightUpWidget)
{
    ui->setupUi(this);
    for(int i = 1;i<ui->tabWidget->count();i++)
    {
        ui->tabWidget->setTabEnabled(i,false);
    }
    targetCurve = new CurvePlot(ui->widget_7);
    backCurve = new CurvePlot(ui->widget_8);
    pickCurve = new CurvePlot(ui->widget_9);
}

RightUpWidget::~RightUpWidget()
{
    delete targetCurve;
    delete backCurve;
    delete pickCurve;
    delete ui;
}

void RightUpWidget::resizeEvent(QResizeEvent *event)
{
    if(targetCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (targetCurve);
        currentWidget->setGeometry(0, 0, ui->widget_7->width(), ui->widget_7->height());
    }
    if(backCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (backCurve);
        currentWidget->setGeometry(0, 0, ui->widget_8->width(), ui->widget_8->height());
    }
    if(pickCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (pickCurve);
        currentWidget->setGeometry(0, 0, ui->widget_9->width(), ui->widget_9->height());
    }
}

std::vector<ModelBase *> RightUpWidget::getModelBases()
{
    return modelBases;
}
/**
 * @brief RightUpWidget::setModelBases
 * 获取数据 并 遍历显示
 * @param modelObjects
 */
void RightUpWidget::setModelBases(std::vector<ModelBase *> modelObjects)
{
    modelBases = modelObjects;
    UpDataModelBase();
}

void RightUpWidget::UpDataModelBase()
{
    std::vector<ModelBase *> targetModelBase;
    std::vector<ModelBase *> backModelBase;
    std::vector<ModelBase *> pickModelBase;
    for(int i=0;i<modelBases.size();i++)
    {
        ModelBase *object = modelBases[i];
        if(object->getSelectStatic())
        {
            if(object->getNature() == 1)
            {
                // widget_7
                targetModelBase.push_back(object);
            }
            else if(object->getNature() == 2)
            {
                // widget_8
                backModelBase.push_back(object);
            }
            else if(object->getNature() == 3)
            {
                // widget_9
                pickModelBase.push_back(object);
            }
        }
    }
    if(targetCurve)
    {
        delete targetCurve;
        targetCurve = NULL;
    }
    if(backCurve)
    {
        delete backCurve;
        backCurve = NULL;
    }
    if(pickCurve)
    {
        delete pickCurve;
        pickCurve = NULL;
    }
    targetCurve = new CurvePlot(ui->widget_7);
    backCurve = new CurvePlot(ui->widget_8);
    pickCurve = new CurvePlot(ui->widget_9);
    targetCurve->setModelBases(targetModelBase);
    backCurve->setModelBases(backModelBase);
    pickCurve->setModelBases(pickModelBase);
    if(targetCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (targetCurve);
        currentWidget->setGeometry(0, 0, ui->widget_7->width(), ui->widget_7->height());
        currentWidget->show();
    }
    if(backCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (backCurve);
        currentWidget->setGeometry(0, 0, ui->widget_8->width(), ui->widget_8->height());
        currentWidget->show();
    }
    if(pickCurve)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (pickCurve);
        currentWidget->setGeometry(0, 0, ui->widget_9->width(), ui->widget_9->height());
        currentWidget->show();
    }
}
/**
 * @brief RightUpWidget::setXTypeCurve
 * 设置X轴范围 及间隔
 * @param xMin
 * @param xMax
 * @param xStep
 */
void RightUpWidget::setXTypeCurve(double xMin, double xMax, int xStep)
{
    targetCurve->setXTypeCurve(xMin,xMax,xStep);
    backCurve->setXTypeCurve(xMin,xMax,xStep);
    pickCurve->setXTypeCurve(xMin,xMax,xStep);
}
/**
 * @brief RightUpWidget::setYTypeCurve
 * 设置y轴范围 及间隔
 * @param yMin
 * @param yMax
 * @param yStep
 */
void RightUpWidget::setYTypeCurve(double yMin, double yMax, int yStep)
{
    targetCurve->setYTypeCurve(yMin,yMax,yStep);
    backCurve->setYTypeCurve(yMin,yMax,yStep);
    pickCurve->setYTypeCurve(yMin,yMax,yStep);
}
/**
 * @brief RightUpWidget::setCurveFps
 * 设置频率
 * @param fps
 */
void RightUpWidget::setCurveFps(double fps)
{
    targetCurve->setCurveFps(fps);
}
/**
 * @brief RightUpWidget::setCurvePosition
 * 设置方位
 * @param position
 */
void RightUpWidget::setCurvePosition(double position)
{
    targetCurve->setCurvePosition(position);
}
/**
 * @brief RightUpWidget::setXName
 * 设置X轴名字
 * @param str
 */
void RightUpWidget::setXName(QString str)
{
    targetCurve->setXName(str);
}
/**
 * @brief RightUpWidget::setYName
 * 设置Y轴名字
 * @param str
 */
void RightUpWidget::setYName(QString str)
{
    targetCurve->setYName(str);
}
/**
 * @brief RightUpWidget::setIndexTabWidgetShow
 * tabWidget与toolBox对应响应函数
 * @param index
 */
void RightUpWidget::setIndexTabWidgetShow(int index)
{
    for(int i = 1; i< ui->tabWidget->count();i++)
    {
        if(index == 0)
        {
            ui->tabWidget->setCurrentIndex(0);
        }
        if(index == i)
        {
            ui->tabWidget->setTabEnabled(i,true);
            ui->tabWidget->setCurrentIndex(i);
        }
        else
        {
            ui->tabWidget->setTabEnabled(i,false);
        }
    }
    if(index == 1)
    {
        setModelBases_3(modelBases);
    }
}
/**
 * @brief RightUpWidget::setModelBases_3
 * 预处理曲线加载模块
 * @param modelObjects
 */
void RightUpWidget::setModelBases_3(std::vector<ModelBase *> modelObjects)
{
    if(tab_3Curve)
    {
        delete tab_3Curve;
        tab_3Curve = NULL;
    }
    for(int i=0;i<modelObjects.size();i++)
    {
        tab_3Curve = new CurvePlot(ui->widget_10);
        tab_3Curve->setModelBases(modelBases);
        if(tab_3Curve)
        {
            QWidget* currentWidget = dynamic_cast<QWidget*> (tab_3Curve);
            currentWidget->setGeometry(0, 0, ui->widget_10->width(), ui->widget_10->height());
            currentWidget->show();
        }
    }
}
