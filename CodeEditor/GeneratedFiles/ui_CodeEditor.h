/********************************************************************************
** Form generated from reading UI file 'CodeEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEEDITOR_H
#define UI_CODEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CodeEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CodeEditorClass)
    {
        if (CodeEditorClass->objectName().isEmpty())
            CodeEditorClass->setObjectName(QStringLiteral("CodeEditorClass"));
        CodeEditorClass->resize(600, 400);
        menuBar = new QMenuBar(CodeEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CodeEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CodeEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CodeEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CodeEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CodeEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CodeEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CodeEditorClass->setStatusBar(statusBar);

        retranslateUi(CodeEditorClass);

        QMetaObject::connectSlotsByName(CodeEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CodeEditorClass)
    {
        CodeEditorClass->setWindowTitle(QApplication::translate("CodeEditorClass", "CodeEditor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CodeEditorClass: public Ui_CodeEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEEDITOR_H
