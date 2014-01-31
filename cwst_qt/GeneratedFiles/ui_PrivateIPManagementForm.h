/********************************************************************************
** Form generated from reading UI file 'PrivateIPManagementForm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATEIPMANAGEMENTFORM_H
#define UI_PRIVATEIPMANAGEMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateIPDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *Cancelbtn;
    QListWidget *lb_privateIPs;
    QLineEdit *tb_IP;
    QPushButton *AddIPbtn;

    void setupUi(QDialog *PrivateIPDialog)
    {
        if (PrivateIPDialog->objectName().isEmpty())
            PrivateIPDialog->setObjectName(QStringLiteral("PrivateIPDialog"));
        PrivateIPDialog->resize(301, 317);
        layoutWidget = new QWidget(PrivateIPDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 270, 181, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        Cancelbtn = new QPushButton(layoutWidget);
        Cancelbtn->setObjectName(QStringLiteral("Cancelbtn"));

        hboxLayout->addWidget(Cancelbtn);

        lb_privateIPs = new QListWidget(PrivateIPDialog);
        lb_privateIPs->setObjectName(QStringLiteral("lb_privateIPs"));
        lb_privateIPs->setGeometry(QRect(20, 20, 256, 192));
        lb_privateIPs->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lb_privateIPs->setSelectionBehavior(QAbstractItemView::SelectRows);
        tb_IP = new QLineEdit(PrivateIPDialog);
        tb_IP->setObjectName(QStringLiteral("tb_IP"));
        tb_IP->setGeometry(QRect(50, 230, 113, 20));
        AddIPbtn = new QPushButton(PrivateIPDialog);
        AddIPbtn->setObjectName(QStringLiteral("AddIPbtn"));
        AddIPbtn->setGeometry(QRect(180, 230, 87, 23));

        retranslateUi(PrivateIPDialog);

        QMetaObject::connectSlotsByName(PrivateIPDialog);
    } // setupUi

    void retranslateUi(QDialog *PrivateIPDialog)
    {
        PrivateIPDialog->setWindowTitle(QApplication::translate("PrivateIPDialog", "Private IP Manager", 0));
        okButton->setText(QApplication::translate("PrivateIPDialog", "OK", 0));
        Cancelbtn->setText(QApplication::translate("PrivateIPDialog", "Cancel", 0));
        AddIPbtn->setText(QApplication::translate("PrivateIPDialog", "Add IP", 0));
    } // retranslateUi

};

namespace Ui {
    class PrivateIPDialog: public Ui_PrivateIPDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATEIPMANAGEMENTFORM_H
