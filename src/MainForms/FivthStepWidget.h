#ifndef FIVTHSTEPWIDGET_H
#define FIVTHSTEPWIDGET_H

#include <QWidget>

namespace Ui {
class FivthStepWidget;
}

class FivthStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FivthStepWidget(QWidget *parent = nullptr);
    ~FivthStepWidget();

private:
    Ui::FivthStepWidget *ui;
};

#endif // FIVTHSTEPWIDGET_H
