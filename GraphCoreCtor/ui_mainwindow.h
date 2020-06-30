/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAsFile;
    QAction *orientation;
    QAction *changeTheme;
    QAction *about;
    QAction *clearAll;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *graphLayout;
    QVBoxLayout *propertyView;
    QLabel *lexsButton;
    QListWidget *lexList;
    QLabel *linsButton;
    QListWidget *linsList;
    QLabel *lcsButton;
    QListWidget *lcsList;
    QHBoxLayout *buttonsView;
    QPushButton *clearLists;
    QPushButton *removeSelectButton;
    QPushButton *findCoresButton;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *propertyMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(552, 312);
        MainWindow->setMinimumSize(QSize(552, 312));
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QString::fromUtf8("openFile"));
        saveFile = new QAction(MainWindow);
        saveFile->setObjectName(QString::fromUtf8("saveFile"));
        saveAsFile = new QAction(MainWindow);
        saveAsFile->setObjectName(QString::fromUtf8("saveAsFile"));
        orientation = new QAction(MainWindow);
        orientation->setObjectName(QString::fromUtf8("orientation"));
        orientation->setCheckable(true);
        orientation->setChecked(true);
        changeTheme = new QAction(MainWindow);
        changeTheme->setObjectName(QString::fromUtf8("changeTheme"));
        changeTheme->setCheckable(true);
        changeTheme->setChecked(true);
        about = new QAction(MainWindow);
        about->setObjectName(QString::fromUtf8("about"));
        about->setVisible(true);
        clearAll = new QAction(MainWindow);
        clearAll->setObjectName(QString::fromUtf8("clearAll"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphLayout = new QGridLayout();
        graphLayout->setObjectName(QString::fromUtf8("graphLayout"));

        horizontalLayout->addLayout(graphLayout);

        propertyView = new QVBoxLayout();
        propertyView->setObjectName(QString::fromUtf8("propertyView"));
        propertyView->setContentsMargins(5, -1, 5, -1);
        lexsButton = new QLabel(centralwidget);
        lexsButton->setObjectName(QString::fromUtf8("lexsButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lexsButton->sizePolicy().hasHeightForWidth());
        lexsButton->setSizePolicy(sizePolicy);

        propertyView->addWidget(lexsButton);

        lexList = new QListWidget(centralwidget);
        lexList->setObjectName(QString::fromUtf8("lexList"));

        propertyView->addWidget(lexList);

        linsButton = new QLabel(centralwidget);
        linsButton->setObjectName(QString::fromUtf8("linsButton"));
        sizePolicy.setHeightForWidth(linsButton->sizePolicy().hasHeightForWidth());
        linsButton->setSizePolicy(sizePolicy);

        propertyView->addWidget(linsButton);

        linsList = new QListWidget(centralwidget);
        linsList->setObjectName(QString::fromUtf8("linsList"));

        propertyView->addWidget(linsList);

        lcsButton = new QLabel(centralwidget);
        lcsButton->setObjectName(QString::fromUtf8("lcsButton"));
        sizePolicy.setHeightForWidth(lcsButton->sizePolicy().hasHeightForWidth());
        lcsButton->setSizePolicy(sizePolicy);

        propertyView->addWidget(lcsButton);

        lcsList = new QListWidget(centralwidget);
        lcsList->setObjectName(QString::fromUtf8("lcsList"));

        propertyView->addWidget(lcsList);

        buttonsView = new QHBoxLayout();
        buttonsView->setObjectName(QString::fromUtf8("buttonsView"));
        buttonsView->setContentsMargins(0, -1, -1, -1);
        clearLists = new QPushButton(centralwidget);
        clearLists->setObjectName(QString::fromUtf8("clearLists"));

        buttonsView->addWidget(clearLists);

        removeSelectButton = new QPushButton(centralwidget);
        removeSelectButton->setObjectName(QString::fromUtf8("removeSelectButton"));

        buttonsView->addWidget(removeSelectButton);

        findCoresButton = new QPushButton(centralwidget);
        findCoresButton->setObjectName(QString::fromUtf8("findCoresButton"));

        buttonsView->addWidget(findCoresButton);


        propertyView->addLayout(buttonsView);


        horizontalLayout->addLayout(propertyView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 552, 20));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        propertyMenu = new QMenu(menubar);
        propertyMenu->setObjectName(QString::fromUtf8("propertyMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(propertyMenu->menuAction());
        fileMenu->addAction(openFile);
        fileMenu->addAction(saveFile);
        fileMenu->addAction(saveAsFile);
        fileMenu->addAction(clearAll);
        propertyMenu->addAction(orientation);
        propertyMenu->addAction(changeTheme);
        propertyMenu->addAction(about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "GraphCoreCtor", nullptr));
        openFile->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        openFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        saveFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        saveFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        saveAsFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
#if QT_CONFIG(shortcut)
        saveAsFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        orientation->setText(QCoreApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\260\321\206\320\270\321\217", nullptr));
#if QT_CONFIG(shortcut)
        orientation->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        changeTheme->setText(QCoreApplication::translate("MainWindow", "\320\247\320\265\321\200\320\275\320\260\321\217 \321\202\320\265\320\274\320\260", nullptr));
#if QT_CONFIG(shortcut)
        changeTheme->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        about->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        clearAll->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
#if QT_CONFIG(shortcut)
        clearAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Del", nullptr));
#endif // QT_CONFIG(shortcut)
        lexsButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\275\320\276\320\266\320\265\321\201\321\202\320\262\320\260 \320\262\320\275\320\265\321\210\320\275\320\265\320\271 \321\203\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\320\270", nullptr));
        linsButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\275\320\276\320\266\320\265\321\201\321\202\320\262\320\260 \320\262\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\265\320\271 \321\203\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\320\270", nullptr));
        lcsButton->setText(QCoreApplication::translate("MainWindow", "\320\257\320\264\321\200\320\260", nullptr));
        clearLists->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        removeSelectButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\320\265", nullptr));
        findCoresButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214 \320\277\320\276\320\270\321\201\320\272 \321\217\320\264\321\200\320\260", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        propertyMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
