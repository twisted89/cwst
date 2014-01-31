/********************************************************************************
** Form generated from reading UI file 'cwst_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CWST_QT_H
#define UI_CWST_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cwst_qtClass
{
public:
    QAction *actionExit;
    QAction *actionManage_Bans;
    QAction *actionManage_Private_IP_s;
    QWidget *centralWidget;
    QTextEdit *tb_log;
    QTableWidget *gv_players;
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *cb_publicSlots;
    QLabel *label_2;
    QComboBox *cb_privateSlots;
    QCheckBox *cb_maxPlayersfix;
    QCheckBox *cb_usePublicFirst;
    QCheckBox *cb_daylight;
    QComboBox *cb_MaxLevel;
    QLabel *label_3;
    QCheckBox *cb_MaxLvlCheck;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cwst_qtClass)
    {
        if (cwst_qtClass->objectName().isEmpty())
            cwst_qtClass->setObjectName(QStringLiteral("cwst_qtClass"));
        cwst_qtClass->resize(750, 373);
        actionExit = new QAction(cwst_qtClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionManage_Bans = new QAction(cwst_qtClass);
        actionManage_Bans->setObjectName(QStringLiteral("actionManage_Bans"));
        actionManage_Private_IP_s = new QAction(cwst_qtClass);
        actionManage_Private_IP_s->setObjectName(QStringLiteral("actionManage_Private_IP_s"));
        centralWidget = new QWidget(cwst_qtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tb_log = new QTextEdit(centralWidget);
        tb_log->setObjectName(QStringLiteral("tb_log"));
        tb_log->setGeometry(QRect(10, 140, 371, 171));
        tb_log->setReadOnly(true);
        gv_players = new QTableWidget(centralWidget);
        gv_players->setObjectName(QStringLiteral("gv_players"));
        gv_players->setGeometry(QRect(390, 10, 341, 301));
        gv_players->setContextMenuPolicy(Qt::CustomContextMenu);
        gv_players->setSelectionMode(QAbstractItemView::SingleSelection);
        gv_players->setSelectionBehavior(QAbstractItemView::SelectRows);
        gv_players->setSortingEnabled(false);
        gv_players->horizontalHeader()->setHighlightSections(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 361, 121));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 81, 21));
        cb_publicSlots = new QComboBox(groupBox);
        cb_publicSlots->setObjectName(QStringLiteral("cb_publicSlots"));
        cb_publicSlots->setGeometry(QRect(100, 20, 91, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 81, 21));
        cb_privateSlots = new QComboBox(groupBox);
        cb_privateSlots->setObjectName(QStringLiteral("cb_privateSlots"));
        cb_privateSlots->setGeometry(QRect(100, 50, 91, 22));
        cb_maxPlayersfix = new QCheckBox(groupBox);
        cb_maxPlayersfix->setObjectName(QStringLiteral("cb_maxPlayersfix"));
        cb_maxPlayersfix->setGeometry(QRect(220, 20, 101, 18));
        cb_usePublicFirst = new QCheckBox(groupBox);
        cb_usePublicFirst->setObjectName(QStringLiteral("cb_usePublicFirst"));
        cb_usePublicFirst->setGeometry(QRect(220, 40, 131, 20));
        cb_daylight = new QCheckBox(groupBox);
        cb_daylight->setObjectName(QStringLiteral("cb_daylight"));
        cb_daylight->setGeometry(QRect(220, 60, 101, 18));
        cb_MaxLevel = new QComboBox(groupBox);
        cb_MaxLevel->setObjectName(QStringLiteral("cb_MaxLevel"));
        cb_MaxLevel->setEnabled(false);
        cb_MaxLevel->setGeometry(QRect(100, 80, 91, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 81, 21));
        cb_MaxLvlCheck = new QCheckBox(groupBox);
        cb_MaxLvlCheck->setObjectName(QStringLiteral("cb_MaxLvlCheck"));
        cb_MaxLvlCheck->setGeometry(QRect(220, 80, 101, 18));
        cwst_qtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(cwst_qtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        cwst_qtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cwst_qtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        cwst_qtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(cwst_qtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        cwst_qtClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionExit);
        menuTools->addAction(actionManage_Bans);
        menuTools->addAction(actionManage_Private_IP_s);

        retranslateUi(cwst_qtClass);

        QMetaObject::connectSlotsByName(cwst_qtClass);
    } // setupUi

    void retranslateUi(QMainWindow *cwst_qtClass)
    {
        cwst_qtClass->setWindowTitle(QApplication::translate("cwst_qtClass", "CWST", 0));
        actionExit->setText(QApplication::translate("cwst_qtClass", "Exit", 0));
        actionManage_Bans->setText(QApplication::translate("cwst_qtClass", "Manage Bans", 0));
        actionManage_Private_IP_s->setText(QApplication::translate("cwst_qtClass", "Manage Private IP's", 0));
        groupBox->setTitle(QApplication::translate("cwst_qtClass", "Settings", 0));
        label->setText(QApplication::translate("cwst_qtClass", "Max public slots", 0));
        label_2->setText(QApplication::translate("cwst_qtClass", "Max private slots", 0));
        cb_maxPlayersfix->setText(QApplication::translate("cwst_qtClass", "Max Players Fix", 0));
        cb_usePublicFirst->setText(QApplication::translate("cwst_qtClass", "Use Public slots first", 0));
        cb_daylight->setText(QApplication::translate("cwst_qtClass", "Always Daylight", 0));
        label_3->setText(QApplication::translate("cwst_qtClass", "Max level", 0));
        cb_MaxLvlCheck->setText(QApplication::translate("cwst_qtClass", "Max level check", 0));
        menuFile->setTitle(QApplication::translate("cwst_qtClass", "File", 0));
        menuTools->setTitle(QApplication::translate("cwst_qtClass", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class cwst_qtClass: public Ui_cwst_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CWST_QT_H
