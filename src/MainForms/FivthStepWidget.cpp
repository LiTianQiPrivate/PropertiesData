#include "FivthStepWidget.h"
#include "ui_FivthStepWidget.h"

FivthStepWidget::FivthStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FivthStepWidget)
{
    ui->setupUi(this);
}

FivthStepWidget::~FivthStepWidget()
{
    delete ui;
}
