#ifndef SIXTHSTEPWIDGET_H
#define SIXTHSTEPWIDGET_H

#include <QWidget>

namespace Ui {
class SixthStepWidget;
}

class SixthStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SixthStepWidget(QWidget *parent = nullptr);
    ~SixthStepWidget();

private:
    Ui::SixthStepWidget *ui;
};

#endif // SIXTHSTEPWIDGET_H
