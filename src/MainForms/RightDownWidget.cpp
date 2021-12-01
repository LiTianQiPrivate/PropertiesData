#include "RightDownWidget.h"
#include "ui_RightDownWidget.h"
#include "Business.h"
#include "RightUpWidget.h"
#include <QDebug>
#include "CurvePlot.h"
#include "XYZWidget.h"
RightDownWidget::RightDownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightDownWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList header;
    header << QString::fromLocal8Bit(NUMBER_NAME)
           << QString::fromLocal8Bit("选择")
           << QString::fromLocal8Bit(DATA_TYPE)
           << QString::fromLocal8Bit(TARGET_NAME)
           << QString::fromLocal8Bit("目标状态")
           << QString::fromLocal8Bit(TARGET_PITCH_ANGLE)
           << QString::fromLocal8Bit(TARGET_ROLL_ANGLE)
           << QString::fromLocal8Bit(POLARIZATION_COMBINATION)
           << QString::fromLocal8Bit("频率参数")
           << QString::fromLocal8Bit("方位参数")
           << QString::fromLocal8Bit("波段");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选取
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    // 设置表头
    ui->tableWidget_2->setColumnCount(13);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList header1;
    header1 << QString::fromLocal8Bit(NUMBER_NAME)
           << QString::fromLocal8Bit("选择")
           << QString::fromLocal8Bit(DATA_TYPE)
           << QString::fromLocal8Bit("数据属性")
           << QString::fromLocal8Bit(TARGET_NAME)
           << QString::fromLocal8Bit("频率参数")
           << QString::fromLocal8Bit("角度参数")
           << QString::fromLocal8Bit("目标状态")
           << QString::fromLocal8Bit(TARGET_PITCH_ANGLE)
           << QString::fromLocal8Bit(TARGET_ROLL_ANGLE)
           << QString::fromLocal8Bit(WORK_FPS)
           << QString::fromLocal8Bit(POLARIZATION_COMBINATION)
           << QString::fromLocal8Bit("文件名");
    ui->tableWidget_2->setHorizontalHeaderLabels(header1);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选取
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_2->setDragEnabled(true);
    ui->tableWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slotHeaderClicked(int)));
}

RightDownWidget::~RightDownWidget()
{
    delete ui;
}

void RightDownWidget::addModelBase(ModelBase *object)
{
    modelBases.push_back(object);
    if(object->getClassName() == "ModelRCSF")
    {
        XYZWidget xyzWidget;
        xyzWidget.setModelRCSF((ModelRCSF*)object);
        xyzWidget.exec();
        if(xyzWidget.getIsOK())
        {
            ModelRCSF* model = (ModelRCSF*)object;
            int xType;
            double value;
            xyzWidget.getReturn(xType, value);
            model->setXStype(xType);
            model->setCurrentValue(value);
        }
    }
    QTableWidgetItem *check = new QTableWidgetItem;
    check->setCheckState(Qt::Checked);
    check->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    int rows = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rows);
    ui->tableWidget->setItem(rows,0,new QTableWidgetItem(QString::number(rows+1))); // 序号
    ui->tableWidget->setItem(rows,1,check);  // 选择
    QString sort = object->findDataInfo(QString::fromLocal8Bit(DATA_SORT));
    if(sort == QString::fromLocal8Bit("目标数据"))
    {
        sort = "T";
        object->setNature(1);
    }
    else if(sort == QString::fromLocal8Bit("背景数据"))
    {
        sort = "B";
        object->setNature(2);
    }
    else if(sort == QString::fromLocal8Bit("定标数据"))
    {
        sort = "C";
        object->setNature(3);
    }
    ui->tableWidget->setItem(rows,2,new QTableWidgetItem(sort));  // 数据类型
    ui->tableWidget->setItem(rows,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME)))); // 目标名称
    ui->tableWidget->setItem(rows,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_EXPLAIN))));  // 目标状态
    ui->tableWidget->setItem(rows,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));  // 俯仰角
    ui->tableWidget->setItem(rows,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));   // 横滚角
    ui->tableWidget->setItem(rows,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION)))); // 极化
    QString startFPS = object->findDataInfo(QString::fromLocal8Bit(START_FPS));
    QString endFPS = object->findDataInfo(QString::fromLocal8Bit(END_FPS));
    QString stepFPS = object->findDataInfo(QString::fromLocal8Bit(FPS_STEP));
    int countFPS = (endFPS.toDouble() - startFPS.toDouble())/stepFPS.toDouble()*1000+1+0.5;   // +0.5为了防止double计算后转int时 精度丢失问题
    QString fps = startFPS + "-" + endFPS + "GHz" + "(" +QString::number(countFPS) + QString::fromLocal8Bit("点")+")";
    ui->tableWidget->setItem(rows,8,new QTableWidgetItem(fps));  // 频率点数
    QString startANGLE = object->findDataInfo(QString::fromLocal8Bit(START_TARGET_ANGLE));
    QString endANGLE = object->findDataInfo(QString::fromLocal8Bit(END_TARGET_ANGLE));
    QString stepANGLE = object->findDataInfo(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE));
    int countANGLE = (endANGLE.toDouble()-startANGLE.toDouble())/stepANGLE.toDouble()+1+0.5;
    QString angle = startANGLE + QString::fromLocal8Bit("°") + "-" + endANGLE + QString::fromLocal8Bit("°") + "(" + QString::number(countANGLE) + QString::fromLocal8Bit("点")+")";
    ui->tableWidget->setItem(rows,9,new QTableWidgetItem(angle));  // 方位点数
    QString band = getFrepBandName(startFPS.toDouble(),endFPS.toDouble(),false);
    ui->tableWidget->setItem(rows,10,new QTableWidgetItem(band));  // 波段
    for (int i=0;i<ui->tableWidget->rowCount();i++)
    {
       for (int j=0;j<ui->tableWidget->columnCount();j++)
       {
           ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       }
    }
    Business::getBusiness()->getRightUpWidget()->setModelBases(modelBases);
}
/**
 * @brief RightDownWidget::getFrepBandName
 * 获取波段字符串
 * @param fstart    起始工作频率
 * @param fend      中值工作频率
 * @param isFileName
 */
QString RightDownWidget::getFrepBandName(double fstart, double fend, bool isFileName)
{
    QString strfreqband_sum = "";
    int startindex = 0;
    int endindex = 0;
    QString strband[] = {"P", "L", "S1", "S2", "C1", "C2", "X", "Ku", "K", "Ka" };
    if ((fstart > 0) && (fstart < 1)) //P
        startindex = 0;
    if ((fstart >= 1) && (fstart < 2))//L
        startindex = 1;
    if ((fstart >= 2) && (fstart < 2.6))//S1
        startindex = 2;
    if ((fstart >= 2.6) && (fstart < 4))//S2
        startindex = 3;
    if ((fstart >= 4) && (fstart < 6))//C1
        startindex = 4;
    if ((fstart >= 6) && (fstart < 8))//C2
        startindex = 5;
    if ((fstart >= 8) && (fstart < 12))//X
        startindex = 6;
    if ((fstart >= 12) && (fstart < 18))//Ku
        startindex = 7;
    if ((fstart >= 18) && (fstart < 26.5))//K
        startindex = 8;
    if ((fstart >= 26.5) && (fstart < 40))//Ka
        startindex = 9;
    if ((fend > 0) && (fend <= 1))
        endindex = 0;
    if ((fend > 1) && (fend <= 2))
        endindex = 1;
    if ((fend > 2) && (fend <= 2.6))
        endindex = 2;
    if ((fend > 2.6) && (fend <= 4))
        endindex = 3;
    if ((fend > 4) && (fend <= 6))
        endindex = 4;
    if ((fend > 6) && (fend <= 8))
        endindex = 5;
    if ((fend > 8) && (fend <= 12))
        endindex = 6;
    if ((fend > 12) && (fend <= 18))
        endindex = 7;
    if ((fend > 18) && (fend <= 26.5))
        endindex = 8;
    if ((fend > 26.5) && (fend <= 40))
        endindex = 9;

    if (isFileName)//用于标识文件名
    {
        for (int i = startindex; i <= endindex; i++)
        {
            strfreqband_sum = strfreqband_sum + strband[i];
            if (i != endindex)
                strfreqband_sum = strfreqband_sum + "";
        }
        strfreqband_sum.replace("C1C2","C");
        strfreqband_sum.replace("S1S2","S");
    }
    else//用于显示列表项
    {
        for (int i = startindex; i <= endindex; i++)
        {
            strfreqband_sum = strfreqband_sum + strband[i];
            if (i != endindex)

                strfreqband_sum = strfreqband_sum + QString::fromLocal8Bit("、");
        }
        strfreqband_sum.replace(QString::fromLocal8Bit("C1、C2"),"C");
        strfreqband_sum.replace(QString::fromLocal8Bit("S1、S2"),"S");
    }
    //点频分界点情况
    if (fstart == fend)
    {
        if (fstart == 1)
            strfreqband_sum = "L";
        if (fstart == 2)
            strfreqband_sum = "S1";
        if (fstart == 2.6)
            strfreqband_sum = "S2";
        if (fstart == 4)
            strfreqband_sum = "C1";
        if (fstart == 6)
            strfreqband_sum = "C2";
        if (fstart == 8)
            strfreqband_sum = "X";
        if (fstart == 12)
            strfreqband_sum = "X";
        if (fstart == 26.5)
            strfreqband_sum = "Ku";
        if (fstart == 40)
            strfreqband_sum = "Ka";
    }
    return strfreqband_sum;
}
/**
 * @brief RightDownWidget::freshenTableWidget
 * 刷新tableWidget 每次排序后刷新
 */
void RightDownWidget::freshenTableWidget()
{
    std::vector<ModelBase *> m_modelBases;
    for(int i =0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i,0);
        int index = item->text().toInt();
        m_modelBases.push_back(modelBases[index-1]);
    }
    modelBases.clear();
    modelBases = m_modelBases;
    // 更改序号  使得 与  modelBases中数据顺序相同
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i,0);
        item->setText(QString::number(i+1));
    }
}
/**
 * @brief RightDownWidget::addModelBases_2
 * ui.tableWidget_2数据加载初始化
 * @param modelBases
 */
void RightDownWidget::addModelBases_2(std::vector<ModelBase *> modelBases)
{
    // 加载数据
    for(int i=0;i<modelBases.size();i++)
    {
        QTableWidgetItem *check = new QTableWidgetItem;
        check->setCheckState(Qt::Checked);
        check->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ModelBase *object = modelBases[i];
        //int rows = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(i,1,check);
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString("T")));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,8,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
        ui->tableWidget_2->setItem(i,9,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
        ui->tableWidget_2->setItem(i,10,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,11,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,12,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
    }
    ui->tableWidget_2->setRowCount(modelBases.size());
    for (int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
       for (int j=0;j<ui->tableWidget_2->columnCount();j++)
       {
           ui->tableWidget_2->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       }
    }

}
/**
 * @brief RightDownWidget::addModelBases_1
 * 动态统计结果模块
 * @param modelBase
 */
void RightDownWidget::addModelBases_1(std::vector<ModelBase *> modelBases)
{
    if(curvePlot)
    {
        delete curvePlot;
        curvePlot = NULL;
    }
    for(int i=0;i<modelBases.size();i++)
    {
        curvePlot = new CurvePlot(ui->widget);
        curvePlot->setModelBases(modelBases);
        if(curvePlot)
        {
            QWidget* currentWidget = dynamic_cast<QWidget*> (curvePlot);
            currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
            currentWidget->show();
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_clicked
 * 设为背景数据
 * @param checked
 */
void RightDownWidget::on_pushButton_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem *item  = ui->tableWidget->item(i,0);
        if(item->isSelected())
        {
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString("B")));
            ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            modelBases[item->row()]->setNature(2);
        }
    }
    Business::getBusiness()->getRightUpWidget()->setModelBases(modelBases);
}
/**
 * @brief RightDownWidget::on_pushButton_2_clicked
 * 设为定标数据
 * @param checked
 */
void RightDownWidget::on_pushButton_2_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem *item  = ui->tableWidget->item(i,0);
        if(item->isSelected())
        {
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString("C")));
            ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            modelBases[item->row()]->setNature(3);
        }
    }
    Business::getBusiness()->getRightUpWidget()->setModelBases(modelBases);
}
/**
 * @brief RightDownWidget::on_tableWidget_cellClicked
 * 复选框 响应函数
 * @param row
 * @param column
 */
void RightDownWidget::on_tableWidget_cellClicked(int row, int column)
{
    if(column != 1)
    {
        return;
    }
    if(modelBases.size() >= row && modelBases.size() > 0)
    {
        if(ui->tableWidget->item(row,column)->checkState() == Qt::Unchecked)
        {
            modelBases[row]->setSelectStatic(false);
        }
        else
        {
            modelBases[row]->setSelectStatic(true);
        }
    }
    Business::getBusiness()->getRightUpWidget()->setModelBases(modelBases);
}
/**
 * @brief RightDownWidget::on_pushButton_3_clicked
 * 曲线全选
 * @param checked
 */
void RightDownWidget::on_pushButton_3_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i,j);
            item->setSelected(true);
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_4_clicked
 * 取消全选
 * @param checked
 */
void RightDownWidget::on_pushButton_4_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i,j);
            item->setSelected(false);
        }
    }
}
/**
 * @brief RightDownWidget::slotHeaderClicked
 * 表头排序 响应函数
 * @param index
 */
void RightDownWidget::slotHeaderClicked(int index)
{
    if(index != 3 && index != 6 && index != 7 && index != 8 && index != 9)
    {
        ui->tableWidget->horizontalHeader()->setSortIndicatorShown(false);
        return;
    }
    static bool bSortShow = true;
    Qt::SortOrder order = bSortShow ? (Qt::AscendingOrder) : (Qt::DescendingOrder);
    ui->tableWidget->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableWidget->horizontalHeader()->setSortIndicator(index, order);
    ui->tableWidget->sortItems(index,order);
    //QString strSort = bSortShow ? "asc" : "desc";
    freshenTableWidget();
    bSortShow = !bSortShow;
}
/**
 * @brief RightDownWidget::on_tabWidget_currentChanged
 * tab页切换响应函数
 * @param index
 */
void RightDownWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
    {
        if(!modelBases.empty())
        {
            addModelBases_2(modelBases);
        }
    }
    else if(index == 1)
    {
        if(!modelBases.empty())
        {
            addModelBases_1(modelBases);
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_7_clicked
 * ui.tablewidget_2 设为背景数据
 * @param checked
 */
void RightDownWidget::on_pushButton_7_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        QTableWidgetItem *item  = ui->tableWidget_2->item(i,0);
        if(item->isSelected())
        {
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString("B")));
            ui->tableWidget_2->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            //modelBases[item->row()]->setNature(2);
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_8_clicked
 * ui.tableWidget_2设为定标数据
 * @param checked
 */
void RightDownWidget::on_pushButton_8_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        QTableWidgetItem *item  = ui->tableWidget_2->item(i,0);
        if(item->isSelected())
        {
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString("C")));
            ui->tableWidget_2->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            //modelBases[item->row()]->setNature(2);
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_9_clicked
 * ui.tableWidget_2 全选
 * @param checked
 */
void RightDownWidget::on_pushButton_9_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget_2->columnCount();j++)
        {
            QTableWidgetItem *item = ui->tableWidget_2->item(i,j);
            item->setSelected(true);
        }
    }
}
/**
 * @brief RightDownWidget::on_pushButton_10_clicked
 * ui.tableWidget_2 取消全选
 * @param checked
 */
void RightDownWidget::on_pushButton_10_clicked(bool checked)
{
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget_2->columnCount();j++)
        {
            QTableWidgetItem *item = ui->tableWidget_2->item(i,j);
            item->setSelected(false);
        }
    }
}
