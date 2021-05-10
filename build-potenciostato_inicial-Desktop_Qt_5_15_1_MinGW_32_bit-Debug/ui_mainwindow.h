/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNueva_Medicion;
    QAction *actionAbrir_Medicion;
    QAction *actionOpciones;
    QAction *actionMedir;
    QAction *actionConfiguracion;
    QAction *actionAyuda;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *Conectar_Bt;
    QTabWidget *tabWidget;
    QWidget *medicion;
    QCustomPlot *customPlot;
    QPushButton *Bt_Iniciar;
    QPushButton *Bt_Abortar;
    QPushButton *Bt_Capturar;
    QPushButton *Bt_Exportar;
    QWidget *config_medicion;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuBarrido_Lineal;
    QMenu *menuAyuda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(800, 600);
        actionNueva_Medicion = new QAction(MainWindow);
        actionNueva_Medicion->setObjectName(QString::fromUtf8("actionNueva_Medicion"));
        actionAbrir_Medicion = new QAction(MainWindow);
        actionAbrir_Medicion->setObjectName(QString::fromUtf8("actionAbrir_Medicion"));
        actionOpciones = new QAction(MainWindow);
        actionOpciones->setObjectName(QString::fromUtf8("actionOpciones"));
        actionMedir = new QAction(MainWindow);
        actionMedir->setObjectName(QString::fromUtf8("actionMedir"));
        actionConfiguracion = new QAction(MainWindow);
        actionConfiguracion->setObjectName(QString::fromUtf8("actionConfiguracion"));
        actionAyuda = new QAction(MainWindow);
        actionAyuda->setObjectName(QString::fromUtf8("actionAyuda"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(500, 10, 141, 61));
        Conectar_Bt = new QPushButton(centralwidget);
        Conectar_Bt->setObjectName(QString::fromUtf8("Conectar_Bt"));
        Conectar_Bt->setGeometry(QRect(650, 10, 141, 61));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 60, 781, 491));
        medicion = new QWidget();
        medicion->setObjectName(QString::fromUtf8("medicion"));
        customPlot = new QCustomPlot(medicion);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(10, 50, 621, 381));
        Bt_Iniciar = new QPushButton(medicion);
        Bt_Iniciar->setObjectName(QString::fromUtf8("Bt_Iniciar"));
        Bt_Iniciar->setGeometry(QRect(640, 50, 131, 41));
        Bt_Abortar = new QPushButton(medicion);
        Bt_Abortar->setObjectName(QString::fromUtf8("Bt_Abortar"));
        Bt_Abortar->setEnabled(false);
        Bt_Abortar->setGeometry(QRect(640, 100, 131, 41));
        Bt_Abortar->setAutoFillBackground(false);
        Bt_Capturar = new QPushButton(medicion);
        Bt_Capturar->setObjectName(QString::fromUtf8("Bt_Capturar"));
        Bt_Capturar->setEnabled(false);
        Bt_Capturar->setGeometry(QRect(640, 150, 131, 41));
        Bt_Exportar = new QPushButton(medicion);
        Bt_Exportar->setObjectName(QString::fromUtf8("Bt_Exportar"));
        Bt_Exportar->setEnabled(false);
        Bt_Exportar->setGeometry(QRect(640, 200, 131, 41));
        Bt_Exportar->setAutoFillBackground(false);
        tabWidget->addTab(medicion, QString());
        config_medicion = new QWidget();
        config_medicion->setObjectName(QString::fromUtf8("config_medicion"));
        tabWidget->addTab(config_medicion, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        menuBarrido_Lineal = new QMenu(menubar);
        menuBarrido_Lineal->setObjectName(QString::fromUtf8("menuBarrido_Lineal"));
        menuAyuda = new QMenu(menubar);
        menuAyuda->setObjectName(QString::fromUtf8("menuAyuda"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuBarrido_Lineal->menuAction());
        menubar->addAction(menuAyuda->menuAction());
        menuArchivo->addAction(actionNueva_Medicion);
        menuArchivo->addAction(actionAbrir_Medicion);
        menuArchivo->addAction(actionOpciones);
        menuBarrido_Lineal->addAction(actionMedir);
        menuBarrido_Lineal->addAction(actionConfiguracion);
        menuAyuda->addAction(actionAyuda);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNueva_Medicion->setText(QCoreApplication::translate("MainWindow", "Nueva Medici\303\263n", nullptr));
        actionAbrir_Medicion->setText(QCoreApplication::translate("MainWindow", "Abrir Medici\303\263n", nullptr));
        actionOpciones->setText(QCoreApplication::translate("MainWindow", "Opciones", nullptr));
        actionMedir->setText(QCoreApplication::translate("MainWindow", "Medir", nullptr));
        actionConfiguracion->setText(QCoreApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
        actionAyuda->setText(QCoreApplication::translate("MainWindow", "Ayuda", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Prueba", nullptr));
        Conectar_Bt->setText(QCoreApplication::translate("MainWindow", "Testear conexi\303\263n USB", nullptr));
        Bt_Iniciar->setText(QCoreApplication::translate("MainWindow", "Iniciar Medici\303\263n", nullptr));
        Bt_Abortar->setText(QCoreApplication::translate("MainWindow", "Abortar", nullptr));
        Bt_Capturar->setText(QCoreApplication::translate("MainWindow", "Capturar", nullptr));
        Bt_Exportar->setText(QCoreApplication::translate("MainWindow", "Exportar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(medicion), QCoreApplication::translate("MainWindow", "Medici\303\263n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(config_medicion), QCoreApplication::translate("MainWindow", "Configuraci\303\263n de la medici\303\263n", nullptr));
        menuArchivo->setTitle(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        menuBarrido_Lineal->setTitle(QCoreApplication::translate("MainWindow", "Barrido Lineal", nullptr));
        menuAyuda->setTitle(QCoreApplication::translate("MainWindow", "Ayuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
