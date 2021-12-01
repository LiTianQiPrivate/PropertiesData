#include "Business.h"
#include <QFileInfo>
#include "ModelRAM.h"
#include "ModelRCS.h"
#include "ModelRCSF.h"

Business* Business::business = NULL;
Business::Business()
{

}

Business *Business::getBusiness()
{
    if(business == NULL)
    {
        business = new Business();
    }
    return business;
}
ModelBase* Business::loadModelBase(QString fileName,QString fileNames)
{
    QFileInfo fileinfo = QFileInfo(fileName);
    QString file_suffix = fileinfo.suffix();
    ModelBase* modelBase = NULL;
    if(file_suffix == "ram")
    {
        ModelRAM* modelObject = new ModelRAM;
        modelObject->loadFile(fileName,fileNames);
        modelBase = modelObject;
    } else if(file_suffix == "rcs") {
        ModelRCS* modelObject = new ModelRCS;
        modelObject->loadFile(fileName,fileNames);
        modelBase = modelObject;
    } else if(file_suffix == "rcsF" || file_suffix == "rcsf") {
        ModelRCSF* modelObject = new ModelRCSF;
        modelObject->loadFile(fileName,fileNames);
        modelBase = modelObject;
    }
    if(modelBase)
    {
        modelObjects.push_back(modelBase);
    }
    return modelBase;
}

RightDownWidget *Business::getRightDownWidget()
{
    return rightDownWidget;
}

void Business::setRightDownWidget(RightDownWidget *value)
{
    rightDownWidget = value;
}

RightUpWidget *Business::getRightUpWidget()
{
    return rightUpWidget;
}

void Business::setRightUpWidget(RightUpWidget *value)
{
    rightUpWidget = value;
}

CurveSetting *Business::getCurveSetting()
{
    return curveSetting;
}

void Business::setCurveSetting(CurveSetting *value)
{
    curveSetting = value;
}

SecondStepWidget *Business::getSecondStepWidget()
{
    return secondStepWidget;
}

void Business::setSecondStepWidget(SecondStepWidget *value)
{
    secondStepWidget = value;
}

ThirdStepWidget *Business::getThirdStepWidget()
{
    return thirdStepWidget;
}

void Business::setThirdStepWidget(ThirdStepWidget *value)
{
    thirdStepWidget = value;
}

FourthStepWidget *Business::getFourthStepWidget()
{
    return fourthStepWidget;
}

void Business::setFourthStepWidget(FourthStepWidget *value)
{
    fourthStepWidget = value;
}

SixthStepWidget *Business::getSixthStepWidget()
{
    return sixthStepWidget;
}

void Business::setSixthStepWidget(SixthStepWidget *value)
{
    sixthStepWidget = value;
}
