/********************************************************************************
** Form generated from reading UI file 'PlayerDetails.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERDETAILS_H
#define UI_PLAYERDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerDetails
{
public:
    QPushButton *okButton;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label2;
    QLineEdit *tb_xp;
    QLabel *label2_2;
    QLineEdit *tb_hp;
    QLabel *label2_3;
    QLineEdit *tb_mp;
    QLabel *label2_4;
    QLineEdit *tb_MaxHPMultiplier;
    QLabel *label2_5;
    QLineEdit *tb_ShootSpeed;
    QLabel *label2_6;
    QLineEdit *tb_DamageMultiplier;
    QLabel *label2_7;
    QLineEdit *tb_ArmorMultiplier;
    QLabel *label2_8;
    QLineEdit *tb_ResistanceMultiplier;
    QLabel *label;
    QLineEdit *tb_level;
    QLineEdit *tb_username;

    void setupUi(QDialog *PlayerDetails)
    {
        if (PlayerDetails->objectName().isEmpty())
            PlayerDetails->setObjectName(QStringLiteral("PlayerDetails"));
        PlayerDetails->resize(289, 352);
        okButton = new QPushButton(PlayerDetails);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(70, 300, 149, 23));
        widget = new QWidget(PlayerDetails);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 244, 256));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label2 = new QLabel(widget);
        label2->setObjectName(QStringLiteral("label2"));

        gridLayout->addWidget(label2, 2, 0, 1, 1);

        tb_xp = new QLineEdit(widget);
        tb_xp->setObjectName(QStringLiteral("tb_xp"));
        tb_xp->setReadOnly(true);

        gridLayout->addWidget(tb_xp, 2, 1, 1, 2);

        label2_2 = new QLabel(widget);
        label2_2->setObjectName(QStringLiteral("label2_2"));

        gridLayout->addWidget(label2_2, 3, 0, 1, 1);

        tb_hp = new QLineEdit(widget);
        tb_hp->setObjectName(QStringLiteral("tb_hp"));
        tb_hp->setReadOnly(true);

        gridLayout->addWidget(tb_hp, 3, 1, 1, 2);

        label2_3 = new QLabel(widget);
        label2_3->setObjectName(QStringLiteral("label2_3"));

        gridLayout->addWidget(label2_3, 4, 0, 1, 1);

        tb_mp = new QLineEdit(widget);
        tb_mp->setObjectName(QStringLiteral("tb_mp"));
        tb_mp->setReadOnly(true);

        gridLayout->addWidget(tb_mp, 4, 1, 1, 2);

        label2_4 = new QLabel(widget);
        label2_4->setObjectName(QStringLiteral("label2_4"));

        gridLayout->addWidget(label2_4, 5, 0, 1, 1);

        tb_MaxHPMultiplier = new QLineEdit(widget);
        tb_MaxHPMultiplier->setObjectName(QStringLiteral("tb_MaxHPMultiplier"));
        tb_MaxHPMultiplier->setReadOnly(true);

        gridLayout->addWidget(tb_MaxHPMultiplier, 5, 1, 1, 2);

        label2_5 = new QLabel(widget);
        label2_5->setObjectName(QStringLiteral("label2_5"));

        gridLayout->addWidget(label2_5, 6, 0, 1, 1);

        tb_ShootSpeed = new QLineEdit(widget);
        tb_ShootSpeed->setObjectName(QStringLiteral("tb_ShootSpeed"));
        tb_ShootSpeed->setReadOnly(true);

        gridLayout->addWidget(tb_ShootSpeed, 6, 1, 1, 2);

        label2_6 = new QLabel(widget);
        label2_6->setObjectName(QStringLiteral("label2_6"));

        gridLayout->addWidget(label2_6, 7, 0, 1, 1);

        tb_DamageMultiplier = new QLineEdit(widget);
        tb_DamageMultiplier->setObjectName(QStringLiteral("tb_DamageMultiplier"));
        tb_DamageMultiplier->setReadOnly(true);

        gridLayout->addWidget(tb_DamageMultiplier, 7, 1, 1, 2);

        label2_7 = new QLabel(widget);
        label2_7->setObjectName(QStringLiteral("label2_7"));

        gridLayout->addWidget(label2_7, 8, 0, 1, 1);

        tb_ArmorMultiplier = new QLineEdit(widget);
        tb_ArmorMultiplier->setObjectName(QStringLiteral("tb_ArmorMultiplier"));
        tb_ArmorMultiplier->setReadOnly(true);

        gridLayout->addWidget(tb_ArmorMultiplier, 8, 1, 1, 2);

        label2_8 = new QLabel(widget);
        label2_8->setObjectName(QStringLiteral("label2_8"));

        gridLayout->addWidget(label2_8, 9, 0, 1, 1);

        tb_ResistanceMultiplier = new QLineEdit(widget);
        tb_ResistanceMultiplier->setObjectName(QStringLiteral("tb_ResistanceMultiplier"));
        tb_ResistanceMultiplier->setReadOnly(true);

        gridLayout->addWidget(tb_ResistanceMultiplier, 9, 1, 1, 2);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        tb_level = new QLineEdit(widget);
        tb_level->setObjectName(QStringLiteral("tb_level"));
        tb_level->setReadOnly(true);

        gridLayout->addWidget(tb_level, 1, 1, 1, 2);

        tb_username = new QLineEdit(widget);
        tb_username->setObjectName(QStringLiteral("tb_username"));
        tb_username->setReadOnly(true);

        gridLayout->addWidget(tb_username, 0, 1, 1, 2);


        retranslateUi(PlayerDetails);
        QObject::connect(okButton, SIGNAL(clicked()), PlayerDetails, SLOT(accept()));

        QMetaObject::connectSlotsByName(PlayerDetails);
    } // setupUi

    void retranslateUi(QDialog *PlayerDetails)
    {
        PlayerDetails->setWindowTitle(QApplication::translate("PlayerDetails", "Player Details", 0));
        okButton->setText(QApplication::translate("PlayerDetails", "OK", 0));
        label_2->setText(QApplication::translate("PlayerDetails", "Username", 0));
        label2->setText(QApplication::translate("PlayerDetails", "XP", 0));
        label2_2->setText(QApplication::translate("PlayerDetails", "HP", 0));
        label2_3->setText(QApplication::translate("PlayerDetails", "MP", 0));
        label2_4->setText(QApplication::translate("PlayerDetails", "Max HP Multiplier", 0));
        label2_5->setText(QApplication::translate("PlayerDetails", "Shoot Speed", 0));
        label2_6->setText(QApplication::translate("PlayerDetails", "Damage Multiplier", 0));
        label2_7->setText(QApplication::translate("PlayerDetails", "Armor Multiplier", 0));
        label2_8->setText(QApplication::translate("PlayerDetails", "Resistance Multiplier", 0));
        label->setText(QApplication::translate("PlayerDetails", "Level", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayerDetails: public Ui_PlayerDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERDETAILS_H
