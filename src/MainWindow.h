#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "RightDownWidget.h"
#include "RightUpWidget.h"
#include "CurveSetting.h"
#include "StepWidget.h"
#include "SecondStepWidget.h"
#include "ThirdStepWidget.h"
#include "FourthStepWidget.h"
#include "FivthStepWidget.h"
#include "SixthStepWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    RightUpWidget rightUpWidget;
    RightDownWidget rightDownWidget;
    CurveSetting curveSetting;
    StepWidget stepWidget;
    SecondStepWidget secondStepWidget;
    ThirdStepWidget thirdStepWidget;
    FourthStepWidget fourthStepWidget;
    FivthStepWidget fivthStepWidget;
    SixthStepWidget sixthStepWidget;
private slots:
    void on_openAction_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
