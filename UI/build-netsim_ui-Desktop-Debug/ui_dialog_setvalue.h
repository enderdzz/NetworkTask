/********************************************************************************
** Form generated from reading UI file 'dialog_setvalue.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SETVALUE_H
#define UI_DIALOG_SETVALUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_dialog_setvalue
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *dialog_setvalue)
    {
        if (dialog_setvalue->objectName().isEmpty())
            dialog_setvalue->setObjectName(QStringLiteral("dialog_setvalue"));
        dialog_setvalue->resize(400, 185);
        buttonBox = new QDialogButtonBox(dialog_setvalue);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(100, 140, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        textBrowser = new QTextBrowser(dialog_setvalue);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(30, 20, 351, 111));

        retranslateUi(dialog_setvalue);
        QObject::connect(buttonBox, SIGNAL(rejected()), dialog_setvalue, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), dialog_setvalue, SLOT(accept()));

        QMetaObject::connectSlotsByName(dialog_setvalue);
    } // setupUi

    void retranslateUi(QDialog *dialog_setvalue)
    {
        dialog_setvalue->setWindowTitle(QApplication::translate("dialog_setvalue", "Dialog", 0));
        textBrowser->setHtml(QApplication::translate("dialog_setvalue", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'WenQuanYi Micro Hei'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Network Simulator</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A job relased under GPL.</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog_setvalue: public Ui_dialog_setvalue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SETVALUE_H
