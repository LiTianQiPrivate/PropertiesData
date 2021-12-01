#ifndef SECONDSTEPWIDGET_H
#define SECONDSTEPWIDGET_H

#include <QWidget>

namespace Ui {
class SecondStepWidget;
}

class SecondStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecondStepWidget(QWidget *parent = nullptr);
    ~SecondStepWidget();

private:
    Ui::SecondStepWidget *ui;
};

#endif // SECONDSTEPWIDGET_H
