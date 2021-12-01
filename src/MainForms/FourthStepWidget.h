#ifndef FOURTHSTEPWIDGET_H
#define FOURTHSTEPWIDGET_H

#include <QWidget>

namespace Ui {
class FourthStepWidget;
}

class FourthStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FourthStepWidget(QWidget *parent = nullptr);
    ~FourthStepWidget();

private:
    Ui::FourthStepWidget *ui;
};

#endif // FOURTHSTEPWIDGET_H
