#ifndef MSIGMABASE_H
#define MSIGMABASE_H
#include <vector>
#include <QString>
#include <QPointF>
class ModelBase;
class PropertiesBase
{
public:
    PropertiesBase(QString name);
    virtual ~PropertiesBase();
    virtual void setModelBases(std::vector<ModelBase*> modelObjects){}
    virtual void addModelBase(ModelBase* modelObject){}
    virtual void clearModelBase(){}
    virtual void showModelBase(int index){}
    virtual void hideModelBase(int index){}
    virtual bool isVisible(int index){return true;}
    virtual void removeModelBase(int index){}
    virtual void updataView(){}
    std::vector<ModelBase*> modelBases;
protected:
    QString className = "";
public:   // 曲线设置功能响应虚函数
    virtual void setXTypeCurve(double xMin,double xMax,int xStep){}
    virtual void setYTypeCurve(double yMin,double yMax,int yStep){}
    virtual void setCurveFps(double fps){}
    virtual void setCurvePosition(double position){}
    virtual void setXName(QString str){}
    virtual void setYName(QString str){}
};

#endif // MSIGMABASE_H
