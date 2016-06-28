/********************************************************************************
** Form generated from reading UI file 'statuswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWIDGET_H
#define UI_STATUSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusWidget
{
public:

    void setupUi(QWidget *StatusWidget)
    {
        if (StatusWidget->objectName().isEmpty())
            StatusWidget->setObjectName(QStringLiteral("StatusWidget"));
        StatusWidget->resize(400, 300);

        retranslateUi(StatusWidget);

        QMetaObject::connectSlotsByName(StatusWidget);
    } // setupUi

    void retranslateUi(QWidget *StatusWidget)
    {
        StatusWidget->setWindowTitle(QApplication::translate("StatusWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class StatusWidget: public Ui_StatusWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWIDGET_H
