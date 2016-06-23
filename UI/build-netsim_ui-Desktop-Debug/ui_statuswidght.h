/********************************************************************************
** Form generated from reading UI file 'statuswidght.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWIDGHT_H
#define UI_STATUSWIDGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusWidght
{
public:

    void setupUi(QWidget *StatusWidght)
    {
        if (StatusWidght->objectName().isEmpty())
            StatusWidght->setObjectName(QStringLiteral("StatusWidght"));
        StatusWidght->resize(400, 300);

        retranslateUi(StatusWidght);

        QMetaObject::connectSlotsByName(StatusWidght);
    } // setupUi

    void retranslateUi(QWidget *StatusWidght)
    {
        StatusWidght->setWindowTitle(QApplication::translate("StatusWidght", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class StatusWidght: public Ui_StatusWidght {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWIDGHT_H
