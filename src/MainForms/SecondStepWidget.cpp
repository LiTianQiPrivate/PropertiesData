#include "SecondStepWidget.h"
#include "ui_SecondStepWidget.h"

SecondStepWidget::SecondStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondStepWidget)
{
    ui->setupUi(this);
}

SecondStepWidget::~SecondStepWidget()
{
    delete ui;
}
