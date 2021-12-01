#ifndef RIGHTUPWIDGET_H
#define RIGHTUPWIDGET_H

#include <QWidget>
#include "PropertiesBase.h"
namespace Ui {
class RightUpWidget;
}

class RightUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RightUpWidget(QWidget *parent = nullptr);
    ~RightUpWidget();
    void resizeEvent(QResizeEvent *event);
    // ui.tab 曲线设置界面处理函数
    std::vector<ModelBase *> getModelBases();
    void setModelBases(std::vector<ModelBase *> modelObjects);
    std::vector<ModelBase *> modelBases;
    void UpDataModelBase();
    void setXTypeCurve(double xMin,double xMax,int xStep);
    void setYTypeCurve(double yMin,double yMax,int yStep);
    void setCurveFps(double fps);
    void setCurvePosition(double position);
    void setXName(QString str);
    void setYName(QString str);
    void setIndexTabWidgetShow(int index);
    PropertiesBase *targetCurve = nullptr;
    PropertiesBase *backCurve = nullptr;
    PropertiesBase *pickCurve = nullptr;
    // ui.tab_3 预处理界面处理函数
    void setModelBases_3(std::vector<ModelBase *> modelObjects);
    PropertiesBase *tab_3Curve = nullptr;
private:
    Ui::RightUpWidget *ui;
};

#endif // RIGHTUPWIDGET_H
