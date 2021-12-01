 #ifndef MODELBASE_H
#define MODELBASE_H

#include <QString>
#include <vector>
#include "KeyText.h"
#include "Point3D.h"
#include "QColor"

class ModelBase
{
public:
    struct TASK_DATA
    {
        TASK_DATA(QString k = "", QString v = "")
        {
            key = k;
            value = v;
        }
        QString key = "";
        QString value = "";
    };
    ModelBase(QString className = "");
    QString getClassName();
    QString FileName();
    void setFileName(QString str)
    {
        fileName = str;
    }
    std::vector<TASK_DATA>& getTaskDatas();
    std::vector<TASK_DATA>& getSystemDatas();
    virtual std::vector<TASK_DATA>& getConditionsDatas() = 0;
    virtual QString findDataInfo(QString key) = 0;
    virtual bool findDataInfoFlag(QString key) = 0;
    virtual std::vector<Point2D> getPoint2D(){return std::vector<Point2D>();}
//    virtual std::vector<Point3D> getPoint3D(){return std::vector<Point3D>();}
    std::vector<std::vector<Point3D>>& getPointDatas(){return pointDatas;}
    QColor getColor();
    virtual void setShowHideFlag(bool v)
    {
        showHide = v;
    }
    virtual bool getShowHideFlag()
    {
        return showHide;
    }
    virtual void setNature(int state)
    {
        nature = state;
        // 1 曲线显示 2 背景曲线显示  3 定标曲线显示
    }
    virtual int getNature()
    {
        return nature;
    }
    virtual bool getSelectStatic()
    {
        return selectState;
    }
    virtual void setSelectStatic(bool v)
    {
        selectState = v;
    }
public:
    bool showHide = true;  // 默认显示
    bool selectState = true; // 默认 被选中
    int nature = 1;
    QString fileName = "";
    QString oriFileName = "";
    std::vector<TASK_DATA> taskDatas;
    std::vector<TASK_DATA> systemDatas;
    std::vector<std::vector<Point3D>> pointDatas; // 数据
    QString className;
protected:
    QColor color;


};

#endif // MODELBASE_H
