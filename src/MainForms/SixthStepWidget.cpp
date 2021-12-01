#include "SixthStepWidget.h"
#include "ui_SixthStepWidget.h"

SixthStepWidget::SixthStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SixthStepWidget)
{
    ui->setupUi(this);
}

SixthStepWidget::~SixthStepWidget()
{
    delete ui;
}
