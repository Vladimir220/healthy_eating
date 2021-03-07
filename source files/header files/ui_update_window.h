/********************************************************************************
** Form generated from reading UI file 'update_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATE_WINDOW_H
#define UI_UPDATE_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UpdateWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *listView;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListView *listView_2;
    QLabel *label_3;
    QListView *listView_3;
    QToolBar *toolBar;

    void setupUi(QMainWindow *UpdateWindow)
    {
        if (UpdateWindow->objectName().isEmpty())
            UpdateWindow->setObjectName(QString::fromUtf8("UpdateWindow"));
        UpdateWindow->setWindowModality(Qt::NonModal);
        UpdateWindow->setEnabled(true);
        UpdateWindow->resize(435, 323);
        centralwidget = new QWidget(UpdateWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(12);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(label);

        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(11);
        font1.setItalic(true);
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        listView_2 = new QListView(centralwidget);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));

        verticalLayout_2->addWidget(listView_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout_2->addWidget(label_3);

        listView_3 = new QListView(centralwidget);
        listView_3->setObjectName(QString::fromUtf8("listView_3"));

        verticalLayout_2->addWidget(listView_3);


        horizontalLayout->addLayout(verticalLayout_2);

        UpdateWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(UpdateWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        UpdateWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(UpdateWindow);

        QMetaObject::connectSlotsByName(UpdateWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UpdateWindow)
    {
        UpdateWindow->setWindowTitle(QApplication::translate("UpdateWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("UpdateWindow", "\320\221\320\273\321\216\320\264\320\260", nullptr));
        label_4->setText(QString());
        label_5->setText(QString());
        label_2->setText(QApplication::translate("UpdateWindow", "\320\241\320\276\320\262\320\274\320\265\321\201\321\202\320\270\320\274\321\213\320\265 \320\261\320\273\321\216\320\264\320\260", nullptr));
        label_3->setText(QApplication::translate("UpdateWindow", "\320\235\320\265\321\201\320\276\320\262\320\274\320\265\321\201\321\202\320\270\320\274\321\213\320\265 \320\261\320\273\321\216\320\264\320\260", nullptr));
        toolBar->setWindowTitle(QApplication::translate("UpdateWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UpdateWindow: public Ui_UpdateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATE_WINDOW_H
