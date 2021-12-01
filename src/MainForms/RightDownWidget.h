#ifndef RIGHTDOWNWIDGET_H
#define RIGHTDOWNWIDGET_H

#include <QWidget>
#include "ModelBase.h"
#include <QTableWidgetItem>

namespace Ui {
class RightDownWidget;
}
class PropertiesBase;
class RightDownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RightDownWidget(QWidget *parent = nullptr);
    ~RightDownWidget();
    std::vector<ModelBase *> modelBases;
    // ui.tableWidget  公共模块
    void addModelBase(ModelBase *object);
    QString getFrepBandName(double fstart,double fend,bool isFileName);
    void freshenTableWidget();
    // ui.tableWidget_2 预处理模块
    void addModelBases_2(std::vector<ModelBase *> modelBases);
    // ui.tab_2 动态统计结果模块
    void addModelBases_1(std::vector<ModelBase *> modelBase);
    PropertiesBase *curvePlot = nullptr;
private slots:
    // ui.tableWidget  公共模块
    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void slotHeaderClicked(int index);

    void on_tabWidget_currentChanged(int index);

    // ui.tableWidget_2  预处理模块
    void on_pushButton_7_clicked(bool checked);

    void on_pushButton_8_clicked(bool checked);

    void on_pushButton_9_clicked(bool checked);

    void on_pushButton_10_clicked(bool checked);

private:
    Ui::RightDownWidget *ui;
};

#endif // RIGHTDOWNWIDGET_H
