#ifndef BUSINESS_H
#define BUSINESS_H

#include <QString>
#include "ModelBase.h"
class RightDownWidget;
class RightUpWidget;
class CurveSetting;
class SecondStepWidget;
class ThirdStepWidget;
class FourthStepWidget;
class SixthStepWidget;
class Business
{
public:
    Business();
    static Business *getBusiness();
    static Business *business;
    ModelBase* loadModelBase(QString fileName, QString fileNames = "");
    std::vector<ModelBase*> modelObjects; // 文件数据
public:
    RightDownWidget *getRightDownWidget();
    void setRightDownWidget(RightDownWidget *value);
    RightDownWidget *rightDownWidget;
public:
    RightUpWidget *getRightUpWidget();
    void setRightUpWidget(RightUpWidget *value);
    RightUpWidget *rightUpWidget;
public:
    CurveSetting *getCurveSetting();
    void setCurveSetting(CurveSetting *value);
    CurveSetting *curveSetting;
public:
    SecondStepWidget *getSecondStepWidget();
    void setSecondStepWidget(SecondStepWidget *value);
    SecondStepWidget *secondStepWidget;
public:
    ThirdStepWidget *getThirdStepWidget();
    void setThirdStepWidget(ThirdStepWidget *value);
    ThirdStepWidget *thirdStepWidget;
public:
    FourthStepWidget *getFourthStepWidget();
    void setFourthStepWidget(FourthStepWidget *value);
    FourthStepWidget *fourthStepWidget;
public:
    SixthStepWidget *getSixthStepWidget();
    void setSixthStepWidget(SixthStepWidget *value);
    SixthStepWidget *sixthStepWidget;
};

#endif // BUSINESS_H
