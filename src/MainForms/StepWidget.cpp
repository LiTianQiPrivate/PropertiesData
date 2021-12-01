#include "StepWidget.h"
#include "ui_StepWidget.h"
#include "Business.h"
#include "RightUpWidget.h"

StepWidget::StepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepWidget)
{
    ui->setupUi(this);
}

StepWidget::~StepWidget()
{
    delete ui;
}
void StepWidget::setWidget(int index, QWidget *widget)
{
    QWidget* currentWidget = ui->toolBox->widget(index);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(widget);
    layout->setMargin(0);
    currentWidget->setLayout(layout);
}

int StepWidget::getStepWidgetIndex()
{
    return ui->toolBox->currentIndex();
}

QToolBox *StepWidget::getStepWidgetQtoolBox()
{
    return ui->toolBox;
}
/**
 * @brief StepWidget::on_toolBox_currentChanged
 * item改变响应函数
 * @param index
 */
void StepWidget::on_toolBox_currentChanged(int index)
{
    Business::getBusiness()->getRightUpWidget()->setIndexTabWidgetShow(index);
}
