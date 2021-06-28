/********************************************************************************
** Form generated from reading UI file 'regioni.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIONI_H
#define UI_REGIONI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Regioni
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget_2;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Regioni)
    {
        if (Regioni->objectName().isEmpty())
            Regioni->setObjectName(QString::fromUtf8("Regioni"));
        Regioni->resize(766, 403);
        centralWidget = new QWidget(Regioni);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 20, 651, 391));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        gridLayout_2->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        gridLayout_2->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableWidget_2 = new QTableWidget(gridLayoutWidget);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setMaximumSize(QSize(400, 16777215));

        verticalLayout_4->addWidget(tableWidget_2);


        gridLayout_2->addLayout(verticalLayout_4, 1, 0, 2, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(250, 16777215));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        Regioni->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Regioni);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 766, 21));
        Regioni->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Regioni);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Regioni->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Regioni);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Regioni->setStatusBar(statusBar);

        retranslateUi(Regioni);

        QMetaObject::connectSlotsByName(Regioni);
    } // setupUi

    void retranslateUi(QMainWindow *Regioni)
    {
        Regioni->setWindowTitle(QApplication::translate("Regioni", "Regioni", nullptr));
        label_2->setText(QApplication::translate("Regioni", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Regioni: public Ui_Regioni {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIONI_H
