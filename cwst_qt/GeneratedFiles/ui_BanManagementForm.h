/********************************************************************************
** Form generated from reading UI file 'BanManagementForm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANMANAGEMENTFORM_H
#define UI_BANMANAGEMENTFORM_H

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

class Ui_BannedIPDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *Cancelbtn;
    QListWidget *lb_bannedIPs;
    QLineEdit *tb_IP;
    QPushButton *AddIPbtn;

    void setupUi(QDialog *BannedIPDialog)
    {
        if (BannedIPDialog->objectName().isEmpty())
            BannedIPDialog->setObjectName(QStringLiteral("BannedIPDialog"));
        BannedIPDialog->resize(282, 317);
        layoutWidget = new QWidget(BannedIPDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 270, 181, 33));
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

        lb_bannedIPs = new QListWidget(BannedIPDialog);
        lb_bannedIPs->setObjectName(QStringLiteral("lb_bannedIPs"));
        lb_bannedIPs->setGeometry(QRect(10, 20, 256, 192));
        lb_bannedIPs->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lb_bannedIPs->setSelectionBehavior(QAbstractItemView::SelectRows);
        tb_IP = new QLineEdit(BannedIPDialog);
        tb_IP->setObjectName(QStringLiteral("tb_IP"));
        tb_IP->setGeometry(QRect(40, 230, 113, 20));
        AddIPbtn = new QPushButton(BannedIPDialog);
        AddIPbtn->setObjectName(QStringLiteral("AddIPbtn"));
        AddIPbtn->setGeometry(QRect(170, 230, 87, 23));

        retranslateUi(BannedIPDialog);

        QMetaObject::connectSlotsByName(BannedIPDialog);
    } // setupUi

    void retranslateUi(QDialog *BannedIPDialog)
    {
        BannedIPDialog->setWindowTitle(QApplication::translate("BannedIPDialog", "Ban Manager", 0));
        okButton->setText(QApplication::translate("BannedIPDialog", "OK", 0));
        Cancelbtn->setText(QApplication::translate("BannedIPDialog", "Cancel", 0));
        AddIPbtn->setText(QApplication::translate("BannedIPDialog", "Add IP", 0));
    } // retranslateUi

};

namespace Ui {
    class BannedIPDialog: public Ui_BannedIPDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANMANAGEMENTFORM_H
