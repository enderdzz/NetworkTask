/********************************************************************************
** Form generated from reading UI file 'netsim_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETSIM_MAINWINDOW_H
#define UI_NETSIM_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphwidget.h"
#include "statuswidget.h"

QT_BEGIN_NAMESPACE

class Ui_Netsim_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionQuit;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btnOnOff;
    QPushButton *btnQuit;
    QProgressBar *progressBar;
    QWidget *widgetConfig;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layoutConfig;
    QGroupBox *groupDataLength;
    QSpinBox *spinDataLength;
    QGroupBox *groupWindowSize;
    QSpinBox *spinWindowSize;
    QGroupBox *groupARQType;
    QRadioButton *radioArqSw;
    QRadioButton *radioArqBn;
    QGroupBox *groupErrorCon;
    QDoubleSpinBox *spinUpError;
    QDoubleSpinBox *spinDownError;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupSimSpeed;
    QSlider *slidSimSpeed;
    QGroupBox *groupTransStatus;
    StatusWidget *widgetWindowStatus;
    QLabel *label_3;
    QTreeWidget *treeWidget;
    graphwidget *widget;
    QMenuBar *menubar;
    QMenu *menu_Operation;

    void setupUi(QMainWindow *Netsim_MainWindow)
    {
        if (Netsim_MainWindow->objectName().isEmpty())
            Netsim_MainWindow->setObjectName(QStringLiteral("Netsim_MainWindow"));
        Netsim_MainWindow->resize(702, 476);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Netsim_MainWindow->sizePolicy().hasHeightForWidth());
        Netsim_MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(Netsim_MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionQuit = new QAction(Netsim_MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralwidget = new QWidget(Netsim_MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(518, 400, 176, 41));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnOnOff = new QPushButton(gridLayoutWidget);
        btnOnOff->setObjectName(QStringLiteral("btnOnOff"));

        gridLayout->addWidget(btnOnOff, 0, 0, 1, 1);

        btnQuit = new QPushButton(gridLayoutWidget);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));

        gridLayout->addWidget(btnQuit, 0, 1, 1, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(536, 370, 131, 23));
        progressBar->setValue(24);
        widgetConfig = new QWidget(centralwidget);
        widgetConfig->setObjectName(QStringLiteral("widgetConfig"));
        widgetConfig->setGeometry(QRect(526, 0, 151, 371));
        verticalLayoutWidget = new QWidget(widgetConfig);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 151, 371));
        layoutConfig = new QVBoxLayout(verticalLayoutWidget);
        layoutConfig->setObjectName(QStringLiteral("layoutConfig"));
        layoutConfig->setContentsMargins(0, 0, 0, 0);
        groupDataLength = new QGroupBox(verticalLayoutWidget);
        groupDataLength->setObjectName(QStringLiteral("groupDataLength"));
        spinDataLength = new QSpinBox(groupDataLength);
        spinDataLength->setObjectName(QStringLiteral("spinDataLength"));
        spinDataLength->setGeometry(QRect(16, 22, 111, 29));
        spinDataLength->setMinimum(10);
        spinDataLength->setMaximum(200);

        layoutConfig->addWidget(groupDataLength);

        groupWindowSize = new QGroupBox(verticalLayoutWidget);
        groupWindowSize->setObjectName(QStringLiteral("groupWindowSize"));
        spinWindowSize = new QSpinBox(groupWindowSize);
        spinWindowSize->setObjectName(QStringLiteral("spinWindowSize"));
        spinWindowSize->setGeometry(QRect(16, 25, 111, 29));
        spinWindowSize->setMinimum(1);
        spinWindowSize->setMaximum(199);

        layoutConfig->addWidget(groupWindowSize);

        groupARQType = new QGroupBox(verticalLayoutWidget);
        groupARQType->setObjectName(QStringLiteral("groupARQType"));
        radioArqSw = new QRadioButton(groupARQType);
        radioArqSw->setObjectName(QStringLiteral("radioArqSw"));
        radioArqSw->setGeometry(QRect(10, 40, 101, 20));
        radioArqSw->setChecked(false);
        radioArqBn = new QRadioButton(groupARQType);
        radioArqBn->setObjectName(QStringLiteral("radioArqBn"));
        radioArqBn->setGeometry(QRect(10, 20, 101, 20));
        radioArqBn->setChecked(true);

        layoutConfig->addWidget(groupARQType);

        groupErrorCon = new QGroupBox(verticalLayoutWidget);
        groupErrorCon->setObjectName(QStringLiteral("groupErrorCon"));
        groupErrorCon->setMinimumSize(QSize(0, 100));
        spinUpError = new QDoubleSpinBox(groupErrorCon);
        spinUpError->setObjectName(QStringLiteral("spinUpError"));
        spinUpError->setGeometry(QRect(70, 30, 69, 29));
        spinUpError->setMaximum(0.8);
        spinUpError->setSingleStep(0.1);
        spinDownError = new QDoubleSpinBox(groupErrorCon);
        spinDownError->setObjectName(QStringLiteral("spinDownError"));
        spinDownError->setGeometry(QRect(70, 60, 69, 29));
        spinDownError->setMaximum(0.8);
        spinDownError->setSingleStep(0.1);
        label = new QLabel(groupErrorCon);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(16, 38, 41, 16));
        label_2 = new QLabel(groupErrorCon);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(8, 67, 61, 16));

        layoutConfig->addWidget(groupErrorCon);

        groupSimSpeed = new QGroupBox(verticalLayoutWidget);
        groupSimSpeed->setObjectName(QStringLiteral("groupSimSpeed"));
        slidSimSpeed = new QSlider(groupSimSpeed);
        slidSimSpeed->setObjectName(QStringLiteral("slidSimSpeed"));
        slidSimSpeed->setGeometry(QRect(10, 36, 121, 20));
        slidSimSpeed->setOrientation(Qt::Horizontal);

        layoutConfig->addWidget(groupSimSpeed);

        groupTransStatus = new QGroupBox(centralwidget);
        groupTransStatus->setObjectName(QStringLiteral("groupTransStatus"));
        groupTransStatus->setGeometry(QRect(7, 0, 511, 411));
        widgetWindowStatus = new StatusWidget(groupTransStatus);
        widgetWindowStatus->setObjectName(QStringLiteral("widgetWindowStatus"));
        widgetWindowStatus->setGeometry(QRect(50, 50, 451, 41));
        label_3 = new QLabel(groupTransStatus);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 30, 131, 16));
        treeWidget = new QTreeWidget(groupTransStatus);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 100, 191, 301));
        treeWidget->setAutoExpandDelay(0);
        treeWidget->setWordWrap(false);
        treeWidget->setColumnCount(2);
        widget = new graphwidget(groupTransStatus);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(210, 100, 291, 301));
        Netsim_MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Netsim_MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 702, 27));
        menu_Operation = new QMenu(menubar);
        menu_Operation->setObjectName(QStringLiteral("menu_Operation"));
        Netsim_MainWindow->setMenuBar(menubar);

        menubar->addAction(menu_Operation->menuAction());
        menu_Operation->addAction(actionAbout);
        menu_Operation->addAction(actionQuit);

        retranslateUi(Netsim_MainWindow);

        QMetaObject::connectSlotsByName(Netsim_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Netsim_MainWindow)
    {
        Netsim_MainWindow->setWindowTitle(QApplication::translate("Netsim_MainWindow", "Netsim_MainWindow", 0));
        actionAbout->setText(QApplication::translate("Netsim_MainWindow", "&About", 0));
        actionQuit->setText(QApplication::translate("Netsim_MainWindow", "&Quit", 0));
        btnOnOff->setText(QApplication::translate("Netsim_MainWindow", "Start", 0));
        btnQuit->setText(QApplication::translate("Netsim_MainWindow", "Quit", 0));
        groupDataLength->setTitle(QApplication::translate("Netsim_MainWindow", "Data Length", 0));
        groupWindowSize->setTitle(QApplication::translate("Netsim_MainWindow", "Send Window size", 0));
        groupARQType->setTitle(QApplication::translate("Netsim_MainWindow", "ARQ Type", 0));
        radioArqSw->setText(QApplication::translate("Netsim_MainWindow", "Stop-Wait", 0));
        radioArqBn->setText(QApplication::translate("Netsim_MainWindow", "Bac&k N", 0));
        groupErrorCon->setTitle(QApplication::translate("Netsim_MainWindow", "Error Percentage", 0));
        label->setText(QApplication::translate("Netsim_MainWindow", "Uplink", 0));
        label_2->setText(QApplication::translate("Netsim_MainWindow", "Downlink", 0));
        groupSimSpeed->setTitle(QApplication::translate("Netsim_MainWindow", "Simulation Speed", 0));
        groupTransStatus->setTitle(QApplication::translate("Netsim_MainWindow", "Tx/Rx Connection Status", 0));
        label_3->setText(QApplication::translate("Netsim_MainWindow", "Receiver's Window", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("Netsim_MainWindow", "Value", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("Netsim_MainWindow", "Item", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("Netsim_MainWindow", "Rx Frame", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("Netsim_MainWindow", "Count", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("Netsim_MainWindow", "ACKSent", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("Netsim_MainWindow", "Timeout Err", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem5->setText(0, QApplication::translate("Netsim_MainWindow", "Tx Frame", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("Netsim_MainWindow", "Count", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("Netsim_MainWindow", "ACKSent", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem5->child(2);
        ___qtreewidgetitem8->setText(0, QApplication::translate("Netsim_MainWindow", "Timeout Err", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

        menu_Operation->setTitle(QApplication::translate("Netsim_MainWindow", "Ope&ration", 0));
    } // retranslateUi

};

namespace Ui {
    class Netsim_MainWindow: public Ui_Netsim_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETSIM_MAINWINDOW_H
