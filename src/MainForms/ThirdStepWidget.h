#ifndef THIRDSTEPWIDGET_H
#define THIRDSTEPWIDGET_H

#include <QWidget>

namespace Ui {
class ThirdStepWidget;
}

class ThirdStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdStepWidget(QWidget *parent = nullptr);
    ~ThirdStepWidget();

private:
    Ui::ThirdStepWidget *ui;
};

#endif // THIRDSTEPWIDGET_H
