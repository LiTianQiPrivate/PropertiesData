#include "ThirdStepWidget.h"
#include "ui_ThirdStepWidget.h"

ThirdStepWidget::ThirdStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThirdStepWidget)
{
    ui->setupUi(this);
}

ThirdStepWidget::~ThirdStepWidget()
{
    delete ui;
}
