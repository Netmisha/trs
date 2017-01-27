/********************************************************************************
** Form generated from reading UI file 'reportform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTFORM_H
#define UI_REPORTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *ReportWidget;

    void setupUi(QWidget *ReportForm)
    {
        if (ReportForm->objectName().isEmpty())
            ReportForm->setObjectName(QStringLiteral("ReportForm"));
        ReportForm->resize(410, 300);
        verticalLayout = new QVBoxLayout(ReportForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ReportWidget = new QWidget(ReportForm);
        ReportWidget->setObjectName(QStringLiteral("ReportWidget"));

        verticalLayout->addWidget(ReportWidget);


        retranslateUi(ReportForm);

        QMetaObject::connectSlotsByName(ReportForm);
    } // setupUi

    void retranslateUi(QWidget *ReportForm)
    {
        ReportForm->setWindowTitle(QApplication::translate("ReportForm", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ReportForm: public Ui_ReportForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTFORM_H
