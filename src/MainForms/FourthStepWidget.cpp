#include "FourthStepWidget.h"
#include "ui_FourthStepWidget.h"

FourthStepWidget::FourthStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FourthStepWidget)
{
    ui->setupUi(this);
}

FourthStepWidget::~FourthStepWidget()
{
    delete ui;
}
