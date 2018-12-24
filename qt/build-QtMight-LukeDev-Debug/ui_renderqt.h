/********************************************************************************
** Form generated from reading UI file 'renderqt.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERQT_H
#define UI_RENDERQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderQt
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *RenderQt)
    {
        if (RenderQt->objectName().isEmpty())
            RenderQt->setObjectName(QStringLiteral("RenderQt"));
        RenderQt->resize(320, 240);
        RenderQt->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(RenderQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        RenderQt->setCentralWidget(centralwidget);

        retranslateUi(RenderQt);

        QMetaObject::connectSlotsByName(RenderQt);
    } // setupUi

    void retranslateUi(QMainWindow *RenderQt)
    {
        RenderQt->setWindowTitle(QApplication::translate("RenderQt", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderQt: public Ui_RenderQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERQT_H
