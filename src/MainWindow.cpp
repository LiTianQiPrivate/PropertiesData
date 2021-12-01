#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include "Business.h"
#include <QDebug>
#include "ToolBoxItem.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString qss;
    QFile qssFile("../src/QSS/myQss.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    stepWidget.setWidget(1,&secondStepWidget);
    stepWidget.setWidget(2,&thirdStepWidget);
    stepWidget.setWidget(3,&fourthStepWidget);
    stepWidget.setWidget(4,&fivthStepWidget);
    stepWidget.setWidget(5,&sixthStepWidget);
    /****左侧UI界面****/
    QVBoxLayout *layout1 = new QVBoxLayout(this);
    layout1->addWidget(&curveSetting);
    layout1->addWidget(&stepWidget);
    layout1->setStretchFactor(&curveSetting,1);
    layout1->setStretchFactor(&stepWidget,3);
    /****右侧UI界面****/
    QVBoxLayout *layout2 = new QVBoxLayout(this);
    layout2->addWidget(&rightUpWidget);
    layout2->addWidget(&rightDownWidget);
    layout2->setStretchFactor(&rightUpWidget,5);
    layout2->setStretchFactor(&rightDownWidget,2);
    /****整体界面布局****/
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->setStretchFactor(layout1,3);
    layout->setStretchFactor(layout2,10);
    ui->centralwidget->setLayout(layout);
    Business::getBusiness()->setRightDownWidget(&rightDownWidget);
    Business::getBusiness()->setRightUpWidget(&rightUpWidget);
    Business::getBusiness()->setCurveSetting(&curveSetting);
    Business::getBusiness()->setSecondStepWidget(&secondStepWidget);
    Business::getBusiness()->setThirdStepWidget(&thirdStepWidget);
    QFile file("./fileList.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << file.errorString();
    }
    else
    {
        QTextStream inputFile(&file);
        QString line = inputFile.readLine();
        QVector<QString> inputList;
        while(!line.isNull())
        {
            inputList.push_back(line);
            line = inputFile.readLine();
        }
        // 减5是为了去掉.mpro的后缀
        QString fileNames = inputList[0].left(inputList[0].length()-5) + "/data";
        qDebug() << "fileNames == " << fileNames;
        for(int i=1;i<inputList.size();i++)
        {
            // inputList[0] 为工程名字  后续的为文件名字
            QDir dir(fileNames);
            dir.setFilter(QDir::Files);  //  设置过滤器  只加载文件
            QStringList list = dir.entryList(QDir::Files);
            for(int j=0;j<list.size();j++)
            {
                QFileInfo file = list[j];
                if(file.suffix() == "ram" || file.suffix() == "rcs" || file.suffix() == "rcsf" || file.suffix() == "rcsF" || file.suffix() == "rcs2f")
                {
                    if(file.fileName() == inputList[i])
                    {
                        ModelBase* modelObject = Business::getBusiness()->loadModelBase(list[j],fileNames);
                        rightDownWidget.addModelBase(modelObject);
                        curveSetting.setCurveType(modelObject);
                    }
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openAction_triggered()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("file names"), "./", "*.ram *.rcs *.rcsf");
    for(int i = 0; i < fileList.size(); i++)
    {
        ModelBase* modelObject = Business::getBusiness()->loadModelBase(fileList[i].toUtf8());
        rightDownWidget.addModelBase(modelObject);
        curveSetting.setCurveType(modelObject);
    }
}
