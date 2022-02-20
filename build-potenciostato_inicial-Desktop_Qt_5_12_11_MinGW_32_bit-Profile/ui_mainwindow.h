/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
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
    QPushButton *Bt_Abortar;
    QPushButton *Bt_Capturar;
    QPushButton *Bt_Exportar;
    QTabWidget *tipoMedicion;
    QWidget *tab;
    QPushButton *Bt_IniciarLineal;
    QDoubleSpinBox *Num_VLineal;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *Num_HzLineal;
    QWidget *tab_2;
    QLabel *label_3;
    QDoubleSpinBox *Num_VCiclico;
    QDoubleSpinBox *Num_HzCiclico;
    QPushButton *Bt_IniciarCiclico;
    QLabel *label_4;
    QDoubleSpinBox *Num_CicCiclico;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *Num_SegCiclico;
    QPushButton *Bt_FTCiclico;
    QPushButton *Desconectar_Bt;
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
        pushButton->setGeometry(QRect(450, 10, 61, 61));
        Conectar_Bt = new QPushButton(centralwidget);
        Conectar_Bt->setObjectName(QString::fromUtf8("Conectar_Bt"));
        Conectar_Bt->setGeometry(QRect(520, 10, 131, 61));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 60, 781, 491));
        medicion = new QWidget();
        medicion->setObjectName(QString::fromUtf8("medicion"));
        customPlot = new QCustomPlot(medicion);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(10, 50, 561, 381));
        Bt_Abortar = new QPushButton(medicion);
        Bt_Abortar->setObjectName(QString::fromUtf8("Bt_Abortar"));
        Bt_Abortar->setEnabled(false);
        Bt_Abortar->setGeometry(QRect(580, 240, 191, 41));
        Bt_Abortar->setAutoFillBackground(false);
        Bt_Capturar = new QPushButton(medicion);
        Bt_Capturar->setObjectName(QString::fromUtf8("Bt_Capturar"));
        Bt_Capturar->setEnabled(false);
        Bt_Capturar->setGeometry(QRect(580, 290, 91, 41));
        Bt_Exportar = new QPushButton(medicion);
        Bt_Exportar->setObjectName(QString::fromUtf8("Bt_Exportar"));
        Bt_Exportar->setEnabled(false);
        Bt_Exportar->setGeometry(QRect(680, 290, 91, 41));
        Bt_Exportar->setAutoFillBackground(false);
        tipoMedicion = new QTabWidget(medicion);
        tipoMedicion->setObjectName(QString::fromUtf8("tipoMedicion"));
        tipoMedicion->setGeometry(QRect(580, 10, 191, 221));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        Bt_IniciarLineal = new QPushButton(tab);
        Bt_IniciarLineal->setObjectName(QString::fromUtf8("Bt_IniciarLineal"));
        Bt_IniciarLineal->setEnabled(false);
        Bt_IniciarLineal->setGeometry(QRect(40, 100, 111, 41));
        Num_VLineal = new QDoubleSpinBox(tab);
        Num_VLineal->setObjectName(QString::fromUtf8("Num_VLineal"));
        Num_VLineal->setGeometry(QRect(120, 10, 62, 22));
        Num_VLineal->setMaximum(3.300000000000000);
        Num_VLineal->setSingleStep(0.100000000000000);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 21));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 91, 21));
        Num_HzLineal = new QDoubleSpinBox(tab);
        Num_HzLineal->setObjectName(QString::fromUtf8("Num_HzLineal"));
        Num_HzLineal->setGeometry(QRect(120, 40, 62, 22));
        Num_HzLineal->setDecimals(0);
        Num_HzLineal->setMaximum(10000.000000000000000);
        Num_HzLineal->setSingleStep(1.000000000000000);
        tipoMedicion->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 91, 21));
        Num_VCiclico = new QDoubleSpinBox(tab_2);
        Num_VCiclico->setObjectName(QString::fromUtf8("Num_VCiclico"));
        Num_VCiclico->setGeometry(QRect(120, 10, 62, 22));
        Num_VCiclico->setMaximum(3.300000000000000);
        Num_VCiclico->setSingleStep(0.100000000000000);
        Num_HzCiclico = new QDoubleSpinBox(tab_2);
        Num_HzCiclico->setObjectName(QString::fromUtf8("Num_HzCiclico"));
        Num_HzCiclico->setGeometry(QRect(120, 40, 62, 22));
        Num_HzCiclico->setDecimals(3);
        Num_HzCiclico->setMinimum(0.200000000000000);
        Num_HzCiclico->setMaximum(8000.000000000000000);
        Num_HzCiclico->setSingleStep(0.001000000000000);
        Num_HzCiclico->setValue(1.000000000000000);
        Bt_IniciarCiclico = new QPushButton(tab_2);
        Bt_IniciarCiclico->setObjectName(QString::fromUtf8("Bt_IniciarCiclico"));
        Bt_IniciarCiclico->setEnabled(false);
        Bt_IniciarCiclico->setGeometry(QRect(40, 150, 111, 41));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 40, 91, 21));
        Num_CicCiclico = new QDoubleSpinBox(tab_2);
        Num_CicCiclico->setObjectName(QString::fromUtf8("Num_CicCiclico"));
        Num_CicCiclico->setGeometry(QRect(120, 100, 62, 22));
        Num_CicCiclico->setDecimals(0);
        Num_CicCiclico->setMaximum(10000.000000000000000);
        Num_CicCiclico->setSingleStep(1.000000000000000);
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 91, 21));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 70, 91, 21));
        Num_SegCiclico = new QDoubleSpinBox(tab_2);
        Num_SegCiclico->setObjectName(QString::fromUtf8("Num_SegCiclico"));
        Num_SegCiclico->setEnabled(false);
        Num_SegCiclico->setGeometry(QRect(120, 70, 62, 22));
        Num_SegCiclico->setDecimals(5);
        Num_SegCiclico->setMinimum(0.000130000000000);
        Num_SegCiclico->setMaximum(5.000000000000000);
        Num_SegCiclico->setSingleStep(0.000010000000000);
        Num_SegCiclico->setValue(1.000000000000000);
        Bt_FTCiclico = new QPushButton(tab_2);
        Bt_FTCiclico->setObjectName(QString::fromUtf8("Bt_FTCiclico"));
        Bt_FTCiclico->setEnabled(true);
        Bt_FTCiclico->setGeometry(QRect(40, 130, 111, 21));
        tipoMedicion->addTab(tab_2, QString());
        tabWidget->addTab(medicion, QString());
        Desconectar_Bt = new QPushButton(centralwidget);
        Desconectar_Bt->setObjectName(QString::fromUtf8("Desconectar_Bt"));
        Desconectar_Bt->setEnabled(false);
        Desconectar_Bt->setGeometry(QRect(660, 10, 131, 61));
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
        tipoMedicion->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNueva_Medicion->setText(QApplication::translate("MainWindow", "Nueva Medici\303\263n", nullptr));
        actionAbrir_Medicion->setText(QApplication::translate("MainWindow", "Abrir Medici\303\263n", nullptr));
        actionOpciones->setText(QApplication::translate("MainWindow", "Opciones", nullptr));
        actionMedir->setText(QApplication::translate("MainWindow", "Medir", nullptr));
        actionConfiguracion->setText(QApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
        actionAyuda->setText(QApplication::translate("MainWindow", "Ayuda", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Prueba", nullptr));
        Conectar_Bt->setText(QApplication::translate("MainWindow", "Iniciar Conexi\303\263n USB", nullptr));
        Bt_Abortar->setText(QApplication::translate("MainWindow", "Abortar", nullptr));
        Bt_Capturar->setText(QApplication::translate("MainWindow", "Capturar", nullptr));
        Bt_Exportar->setText(QApplication::translate("MainWindow", "Exportar", nullptr));
        Bt_IniciarLineal->setText(QApplication::translate("MainWindow", "Iniciar Medici\303\263n", nullptr));
        label->setText(QApplication::translate("MainWindow", "Tensi\303\263n m\303\241xima [V]", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Frecuencia [Hz]", nullptr));
        tipoMedicion->setTabText(tipoMedicion->indexOf(tab), QApplication::translate("MainWindow", "Barrido Lineal", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Tensi\303\263n m\303\241xima [V]", nullptr));
        Bt_IniciarCiclico->setText(QApplication::translate("MainWindow", "Iniciar Medici\303\263n", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Frecuencia [Hz]", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Cant. de Ciclos", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Per\303\255odo [Seg]", nullptr));
        Bt_FTCiclico->setText(QApplication::translate("MainWindow", "Frec. <=> Per\303\255odo", nullptr));
        tipoMedicion->setTabText(tipoMedicion->indexOf(tab_2), QApplication::translate("MainWindow", "Barrido C\303\255clico", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(medicion), QApplication::translate("MainWindow", "Medici\303\263n", nullptr));
        Desconectar_Bt->setText(QApplication::translate("MainWindow", "Terminar Conexi\303\263n USB", nullptr));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", nullptr));
        menuBarrido_Lineal->setTitle(QApplication::translate("MainWindow", "Barrido Lineal", nullptr));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Ayuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
