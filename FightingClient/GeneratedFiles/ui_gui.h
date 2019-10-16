/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiClass
{
public:
    QWidget *centralWidget;
    QWidget *menuWidget;
    QPushButton *createLobby;
    QPushButton *joinLobby;
    QLineEdit *name;
    QListWidget *list;
    QLabel *status;
    QPushButton *refreshList;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *guiClass)
    {
        if (guiClass->objectName().isEmpty())
            guiClass->setObjectName(QStringLiteral("guiClass"));
        guiClass->resize(1015, 793);
        centralWidget = new QWidget(guiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        menuWidget = new QWidget(centralWidget);
        menuWidget->setObjectName(QStringLiteral("menuWidget"));
        menuWidget->setGeometry(QRect(20, 0, 1001, 701));
        createLobby = new QPushButton(menuWidget);
        createLobby->setObjectName(QStringLiteral("createLobby"));
        createLobby->setGeometry(QRect(150, 80, 151, 34));
        joinLobby = new QPushButton(menuWidget);
        joinLobby->setObjectName(QStringLiteral("joinLobby"));
        joinLobby->setGeometry(QRect(480, 70, 301, 34));
        name = new QLineEdit(menuWidget);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(360, 10, 191, 25));
        list = new QListWidget(menuWidget);
        list->setObjectName(QStringLiteral("list"));
        list->setGeometry(QRect(370, 150, 161, 331));
        status = new QLabel(menuWidget);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(77, 570, 811, 20));
        refreshList = new QPushButton(menuWidget);
        refreshList->setObjectName(QStringLiteral("refreshList"));
        refreshList->setGeometry(QRect(360, 490, 181, 61));
        guiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(guiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1015, 31));
        guiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(guiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        guiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(guiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        guiClass->setStatusBar(statusBar);

        retranslateUi(guiClass);

        QMetaObject::connectSlotsByName(guiClass);
    } // setupUi

    void retranslateUi(QMainWindow *guiClass)
    {
        guiClass->setWindowTitle(QApplication::translate("guiClass", "gui", Q_NULLPTR));
        createLobby->setText(QApplication::translate("guiClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\273\320\276\320\261\320\261\320\270", Q_NULLPTR));
        joinLobby->setText(QApplication::translate("guiClass", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \320\270\320\274\320\265\321\216\321\211\320\265\320\274\321\203\321\201\321\217 \320\273\320\276\320\261\320\261\320\270", Q_NULLPTR));
        status->setText(QString());
        refreshList->setText(QApplication::translate("guiClass", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\273\320\276\320\261\320\261\320\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class guiClass: public Ui_guiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
