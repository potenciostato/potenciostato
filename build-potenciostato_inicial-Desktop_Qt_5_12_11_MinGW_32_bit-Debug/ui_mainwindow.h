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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
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
    QAction *actionAyuda;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *medicion;
    QCustomPlot *customPlot;
    QPushButton *Bt_Abortar;
    QPushButton *Bt_Exportar;
    QTabWidget *tipoMedicion;
    QWidget *tabCiclico;
    QGroupBox *grupoPeriodoRetencion_2;
    QDoubleSpinBox *Num_SegRetCiclico;
    QLabel *Lb_TenRetCiclico;
    QDoubleSpinBox *Num_mVTenRetCiclico;
    QLabel *Lb_TiemRetCiclico;
    QGroupBox *grupoPeriodoRetencion_3;
    QDoubleSpinBox *Num_mVTen1Ciclico;
    QLabel *Lb_VelCiclico;
    QDoubleSpinBox *Num_mVTen2Ciclico;
    QLabel *Lb_CicCiclico;
    QDoubleSpinBox *Num_mVTen3Ciclico;
    QLabel *Lb_TenCiclico;
    QDoubleSpinBox *Num_mVSegVelCiclico;
    QDoubleSpinBox *Num_CicCiclico;
    QPushButton *Bt_IniciarCiclico;
    QComboBox *Num_GanCorriente;
    QLabel *Lb_GanCorriente;
    QPushButton *Bt_AutoCentrar;
    QLabel *Lb_deltaY;
    QLabel *Lb_deltaX;
    QLabel *Lb_deltaZ;
    QLabel *Num_deltaX;
    QLabel *Num_deltaY;
    QLabel *Num_deltaZ;
    QPushButton *Bt_Cursores;
    QPushButton *Conectar_Bt;
    QPushButton *Desconectar_Bt;
    QLabel *Lb_deltaXa;
    QLabel *Lb_deltaXb;
    QLabel *Num_deltaXa;
    QLabel *Num_deltaXb;
    QLabel *Lb_deltaYa;
    QLabel *Lb_deltaYb;
    QLabel *Num_deltaYb;
    QLabel *Num_deltaYa;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuAyuda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(1024, 625);
        actionNueva_Medicion = new QAction(MainWindow);
        actionNueva_Medicion->setObjectName(QString::fromUtf8("actionNueva_Medicion"));
        actionAbrir_Medicion = new QAction(MainWindow);
        actionAbrir_Medicion->setObjectName(QString::fromUtf8("actionAbrir_Medicion"));
        actionOpciones = new QAction(MainWindow);
        actionOpciones->setObjectName(QString::fromUtf8("actionOpciones"));
        actionAyuda = new QAction(MainWindow);
        actionAyuda->setObjectName(QString::fromUtf8("actionAyuda"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 1011, 661));
        medicion = new QWidget();
        medicion->setObjectName(QString::fromUtf8("medicion"));
        customPlot = new QCustomPlot(medicion);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(10, 50, 751, 501));
        Bt_Abortar = new QPushButton(medicion);
        Bt_Abortar->setObjectName(QString::fromUtf8("Bt_Abortar"));
        Bt_Abortar->setEnabled(false);
        Bt_Abortar->setGeometry(QRect(780, 490, 211, 31));
        QFont font;
        font.setPointSize(9);
        Bt_Abortar->setFont(font);
        Bt_Abortar->setAutoFillBackground(false);
        Bt_Exportar = new QPushButton(medicion);
        Bt_Exportar->setObjectName(QString::fromUtf8("Bt_Exportar"));
        Bt_Exportar->setEnabled(false);
        Bt_Exportar->setGeometry(QRect(780, 520, 211, 31));
        Bt_Exportar->setFont(font);
        Bt_Exportar->setAutoFillBackground(false);
        tipoMedicion = new QTabWidget(medicion);
        tipoMedicion->setObjectName(QString::fromUtf8("tipoMedicion"));
        tipoMedicion->setGeometry(QRect(770, 90, 231, 391));
        tipoMedicion->setFont(font);
        tipoMedicion->setTabPosition(QTabWidget::North);
        tipoMedicion->setTabShape(QTabWidget::Rounded);
        tipoMedicion->setElideMode(Qt::ElideRight);
        tipoMedicion->setUsesScrollButtons(false);
        tipoMedicion->setDocumentMode(false);
        tipoMedicion->setTabsClosable(false);
        tipoMedicion->setMovable(false);
        tabCiclico = new QWidget();
        tabCiclico->setObjectName(QString::fromUtf8("tabCiclico"));
        grupoPeriodoRetencion_2 = new QGroupBox(tabCiclico);
        grupoPeriodoRetencion_2->setObjectName(QString::fromUtf8("grupoPeriodoRetencion_2"));
        grupoPeriodoRetencion_2->setGeometry(QRect(0, 10, 221, 81));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        grupoPeriodoRetencion_2->setFont(font1);
        Num_SegRetCiclico = new QDoubleSpinBox(grupoPeriodoRetencion_2);
        Num_SegRetCiclico->setObjectName(QString::fromUtf8("Num_SegRetCiclico"));
        Num_SegRetCiclico->setGeometry(QRect(140, 20, 71, 22));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        Num_SegRetCiclico->setFont(font2);
        Num_SegRetCiclico->setDecimals(0);
        Num_SegRetCiclico->setMaximum(255.000000000000000);
        Num_SegRetCiclico->setSingleStep(1.000000000000000);
        Lb_TenRetCiclico = new QLabel(grupoPeriodoRetencion_2);
        Lb_TenRetCiclico->setObjectName(QString::fromUtf8("Lb_TenRetCiclico"));
        Lb_TenRetCiclico->setGeometry(QRect(10, 50, 91, 21));
        Lb_TenRetCiclico->setFont(font2);
        Num_mVTenRetCiclico = new QDoubleSpinBox(grupoPeriodoRetencion_2);
        Num_mVTenRetCiclico->setObjectName(QString::fromUtf8("Num_mVTenRetCiclico"));
        Num_mVTenRetCiclico->setGeometry(QRect(140, 50, 71, 22));
        Num_mVTenRetCiclico->setFont(font2);
        Num_mVTenRetCiclico->setDecimals(0);
        Num_mVTenRetCiclico->setMinimum(-3000.000000000000000);
        Num_mVTenRetCiclico->setMaximum(3000.000000000000000);
        Num_mVTenRetCiclico->setSingleStep(10.000000000000000);
        Lb_TiemRetCiclico = new QLabel(grupoPeriodoRetencion_2);
        Lb_TiemRetCiclico->setObjectName(QString::fromUtf8("Lb_TiemRetCiclico"));
        Lb_TiemRetCiclico->setGeometry(QRect(10, 20, 91, 21));
        Lb_TiemRetCiclico->setFont(font2);
        grupoPeriodoRetencion_3 = new QGroupBox(tabCiclico);
        grupoPeriodoRetencion_3->setObjectName(QString::fromUtf8("grupoPeriodoRetencion_3"));
        grupoPeriodoRetencion_3->setGeometry(QRect(0, 100, 221, 171));
        grupoPeriodoRetencion_3->setFont(font1);
        Num_mVTen1Ciclico = new QDoubleSpinBox(grupoPeriodoRetencion_3);
        Num_mVTen1Ciclico->setObjectName(QString::fromUtf8("Num_mVTen1Ciclico"));
        Num_mVTen1Ciclico->setGeometry(QRect(10, 50, 61, 22));
        Num_mVTen1Ciclico->setFont(font2);
        Num_mVTen1Ciclico->setDecimals(0);
        Num_mVTen1Ciclico->setMinimum(-3000.000000000000000);
        Num_mVTen1Ciclico->setMaximum(3000.000000000000000);
        Num_mVTen1Ciclico->setSingleStep(10.000000000000000);
        Lb_VelCiclico = new QLabel(grupoPeriodoRetencion_3);
        Lb_VelCiclico->setObjectName(QString::fromUtf8("Lb_VelCiclico"));
        Lb_VelCiclico->setGeometry(QRect(10, 100, 111, 21));
        Lb_VelCiclico->setFont(font2);
        Num_mVTen2Ciclico = new QDoubleSpinBox(grupoPeriodoRetencion_3);
        Num_mVTen2Ciclico->setObjectName(QString::fromUtf8("Num_mVTen2Ciclico"));
        Num_mVTen2Ciclico->setGeometry(QRect(80, 50, 61, 22));
        Num_mVTen2Ciclico->setFont(font2);
        Num_mVTen2Ciclico->setDecimals(0);
        Num_mVTen2Ciclico->setMinimum(-3000.000000000000000);
        Num_mVTen2Ciclico->setMaximum(3000.000000000000000);
        Num_mVTen2Ciclico->setSingleStep(10.000000000000000);
        Lb_CicCiclico = new QLabel(grupoPeriodoRetencion_3);
        Lb_CicCiclico->setObjectName(QString::fromUtf8("Lb_CicCiclico"));
        Lb_CicCiclico->setGeometry(QRect(10, 140, 111, 21));
        Lb_CicCiclico->setFont(font2);
        Lb_CicCiclico->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Num_mVTen3Ciclico = new QDoubleSpinBox(grupoPeriodoRetencion_3);
        Num_mVTen3Ciclico->setObjectName(QString::fromUtf8("Num_mVTen3Ciclico"));
        Num_mVTen3Ciclico->setGeometry(QRect(150, 50, 61, 22));
        Num_mVTen3Ciclico->setFont(font2);
        Num_mVTen3Ciclico->setDecimals(0);
        Num_mVTen3Ciclico->setMinimum(-3000.000000000000000);
        Num_mVTen3Ciclico->setMaximum(3000.000000000000000);
        Num_mVTen3Ciclico->setSingleStep(10.000000000000000);
        Lb_TenCiclico = new QLabel(grupoPeriodoRetencion_3);
        Lb_TenCiclico->setObjectName(QString::fromUtf8("Lb_TenCiclico"));
        Lb_TenCiclico->setGeometry(QRect(10, 20, 201, 21));
        Lb_TenCiclico->setFont(font2);
        Lb_TenCiclico->setAlignment(Qt::AlignCenter);
        Num_mVSegVelCiclico = new QDoubleSpinBox(grupoPeriodoRetencion_3);
        Num_mVSegVelCiclico->setObjectName(QString::fromUtf8("Num_mVSegVelCiclico"));
        Num_mVSegVelCiclico->setGeometry(QRect(140, 100, 71, 22));
        Num_mVSegVelCiclico->setFont(font2);
        Num_mVSegVelCiclico->setDecimals(0);
        Num_mVSegVelCiclico->setMinimum(0.000000000000000);
        Num_mVSegVelCiclico->setMaximum(255.000000000000000);
        Num_mVSegVelCiclico->setSingleStep(1.000000000000000);
        Num_mVSegVelCiclico->setValue(0.000000000000000);
        Num_CicCiclico = new QDoubleSpinBox(grupoPeriodoRetencion_3);
        Num_CicCiclico->setObjectName(QString::fromUtf8("Num_CicCiclico"));
        Num_CicCiclico->setGeometry(QRect(140, 140, 71, 22));
        Num_CicCiclico->setFont(font2);
        Num_CicCiclico->setDecimals(0);
        Num_CicCiclico->setMaximum(255.000000000000000);
        Num_CicCiclico->setSingleStep(1.000000000000000);
        Lb_VelCiclico->raise();
        Num_mVTen1Ciclico->raise();
        Num_mVTen2Ciclico->raise();
        Lb_CicCiclico->raise();
        Lb_TenCiclico->raise();
        Num_mVSegVelCiclico->raise();
        Num_CicCiclico->raise();
        Num_mVTen3Ciclico->raise();
        Bt_IniciarCiclico = new QPushButton(tabCiclico);
        Bt_IniciarCiclico->setObjectName(QString::fromUtf8("Bt_IniciarCiclico"));
        Bt_IniciarCiclico->setEnabled(false);
        Bt_IniciarCiclico->setGeometry(QRect(50, 320, 121, 41));
        Bt_IniciarCiclico->setFont(font);
        Num_GanCorriente = new QComboBox(tabCiclico);
        Num_GanCorriente->addItem(QString());
        Num_GanCorriente->addItem(QString());
        Num_GanCorriente->addItem(QString());
        Num_GanCorriente->addItem(QString());
        Num_GanCorriente->setObjectName(QString::fromUtf8("Num_GanCorriente"));
        Num_GanCorriente->setGeometry(QRect(140, 280, 69, 22));
        Lb_GanCorriente = new QLabel(tabCiclico);
        Lb_GanCorriente->setObjectName(QString::fromUtf8("Lb_GanCorriente"));
        Lb_GanCorriente->setGeometry(QRect(10, 280, 111, 21));
        Lb_GanCorriente->setFont(font2);
        Lb_GanCorriente->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tipoMedicion->addTab(tabCiclico, QString());
        Bt_AutoCentrar = new QPushButton(medicion);
        Bt_AutoCentrar->setObjectName(QString::fromUtf8("Bt_AutoCentrar"));
        Bt_AutoCentrar->setGeometry(QRect(700, 10, 61, 41));
        Bt_AutoCentrar->setFont(font);
        Lb_deltaY = new QLabel(medicion);
        Lb_deltaY->setObjectName(QString::fromUtf8("Lb_deltaY"));
        Lb_deltaY->setGeometry(QRect(390, 30, 21, 20));
        QFont font3;
        font3.setPointSize(10);
        Lb_deltaY->setFont(font3);
        Lb_deltaX = new QLabel(medicion);
        Lb_deltaX->setObjectName(QString::fromUtf8("Lb_deltaX"));
        Lb_deltaX->setGeometry(QRect(390, 10, 21, 20));
        Lb_deltaX->setFont(font3);
        Lb_deltaZ = new QLabel(medicion);
        Lb_deltaZ->setObjectName(QString::fromUtf8("Lb_deltaZ"));
        Lb_deltaZ->setGeometry(QRect(510, 20, 21, 20));
        Lb_deltaZ->setFont(font3);
        Num_deltaX = new QLabel(medicion);
        Num_deltaX->setObjectName(QString::fromUtf8("Num_deltaX"));
        Num_deltaX->setGeometry(QRect(410, 10, 81, 20));
        Num_deltaX->setFont(font3);
        Num_deltaX->setLayoutDirection(Qt::LeftToRight);
        Num_deltaX->setTextFormat(Qt::AutoText);
        Num_deltaX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Num_deltaY = new QLabel(medicion);
        Num_deltaY->setObjectName(QString::fromUtf8("Num_deltaY"));
        Num_deltaY->setGeometry(QRect(410, 30, 81, 20));
        Num_deltaY->setFont(font3);
        Num_deltaY->setLayoutDirection(Qt::LeftToRight);
        Num_deltaY->setTextFormat(Qt::AutoText);
        Num_deltaY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Num_deltaZ = new QLabel(medicion);
        Num_deltaZ->setObjectName(QString::fromUtf8("Num_deltaZ"));
        Num_deltaZ->setGeometry(QRect(520, 20, 81, 20));
        Num_deltaZ->setFont(font3);
        Num_deltaZ->setLayoutDirection(Qt::LeftToRight);
        Num_deltaZ->setTextFormat(Qt::AutoText);
        Num_deltaZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Bt_Cursores = new QPushButton(medicion);
        Bt_Cursores->setObjectName(QString::fromUtf8("Bt_Cursores"));
        Bt_Cursores->setGeometry(QRect(620, 10, 71, 41));
        Bt_Cursores->setFont(font);
        Bt_Cursores->setCheckable(false);
        Conectar_Bt = new QPushButton(medicion);
        Conectar_Bt->setObjectName(QString::fromUtf8("Conectar_Bt"));
        Conectar_Bt->setGeometry(QRect(780, 10, 211, 41));
        Conectar_Bt->setFont(font);
        Desconectar_Bt = new QPushButton(medicion);
        Desconectar_Bt->setObjectName(QString::fromUtf8("Desconectar_Bt"));
        Desconectar_Bt->setEnabled(false);
        Desconectar_Bt->setGeometry(QRect(780, 50, 211, 31));
        Desconectar_Bt->setFont(font);
        Lb_deltaXa = new QLabel(medicion);
        Lb_deltaXa->setObjectName(QString::fromUtf8("Lb_deltaXa"));
        Lb_deltaXa->setGeometry(QRect(10, 10, 21, 20));
        Lb_deltaXa->setFont(font3);
        Lb_deltaXb = new QLabel(medicion);
        Lb_deltaXb->setObjectName(QString::fromUtf8("Lb_deltaXb"));
        Lb_deltaXb->setGeometry(QRect(10, 30, 21, 20));
        Lb_deltaXb->setFont(font3);
        Num_deltaXa = new QLabel(medicion);
        Num_deltaXa->setObjectName(QString::fromUtf8("Num_deltaXa"));
        Num_deltaXa->setGeometry(QRect(30, 10, 81, 20));
        Num_deltaXa->setFont(font3);
        Num_deltaXa->setLayoutDirection(Qt::LeftToRight);
        Num_deltaXa->setTextFormat(Qt::AutoText);
        Num_deltaXa->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Num_deltaXb = new QLabel(medicion);
        Num_deltaXb->setObjectName(QString::fromUtf8("Num_deltaXb"));
        Num_deltaXb->setGeometry(QRect(30, 30, 81, 20));
        Num_deltaXb->setFont(font3);
        Num_deltaXb->setLayoutDirection(Qt::LeftToRight);
        Num_deltaXb->setTextFormat(Qt::AutoText);
        Num_deltaXb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Lb_deltaYa = new QLabel(medicion);
        Lb_deltaYa->setObjectName(QString::fromUtf8("Lb_deltaYa"));
        Lb_deltaYa->setGeometry(QRect(140, 10, 21, 20));
        Lb_deltaYa->setFont(font3);
        Lb_deltaYb = new QLabel(medicion);
        Lb_deltaYb->setObjectName(QString::fromUtf8("Lb_deltaYb"));
        Lb_deltaYb->setGeometry(QRect(140, 30, 21, 20));
        Lb_deltaYb->setFont(font3);
        Num_deltaYb = new QLabel(medicion);
        Num_deltaYb->setObjectName(QString::fromUtf8("Num_deltaYb"));
        Num_deltaYb->setGeometry(QRect(160, 30, 81, 20));
        Num_deltaYb->setFont(font3);
        Num_deltaYb->setLayoutDirection(Qt::LeftToRight);
        Num_deltaYb->setTextFormat(Qt::AutoText);
        Num_deltaYb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Num_deltaYa = new QLabel(medicion);
        Num_deltaYa->setObjectName(QString::fromUtf8("Num_deltaYa"));
        Num_deltaYa->setGeometry(QRect(160, 10, 81, 20));
        Num_deltaYa->setFont(font3);
        Num_deltaYa->setLayoutDirection(Qt::LeftToRight);
        Num_deltaYa->setTextFormat(Qt::AutoText);
        Num_deltaYa->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(medicion, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        menuAyuda = new QMenu(menubar);
        menuAyuda->setObjectName(QString::fromUtf8("menuAyuda"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuAyuda->menuAction());
        menuArchivo->addAction(actionNueva_Medicion);
        menuArchivo->addAction(actionAbrir_Medicion);
        menuArchivo->addAction(actionOpciones);
        menuAyuda->addAction(actionAyuda);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tipoMedicion->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNueva_Medicion->setText(QApplication::translate("MainWindow", "Nueva Medici\303\263n", nullptr));
        actionAbrir_Medicion->setText(QApplication::translate("MainWindow", "Abrir Medici\303\263n", nullptr));
        actionOpciones->setText(QApplication::translate("MainWindow", "Opciones", nullptr));
        actionAyuda->setText(QApplication::translate("MainWindow", "Ayuda", nullptr));
        Bt_Abortar->setText(QApplication::translate("MainWindow", "Abortar", nullptr));
        Bt_Exportar->setText(QApplication::translate("MainWindow", "Exportar", nullptr));
        grupoPeriodoRetencion_2->setTitle(QApplication::translate("MainWindow", "Per\303\255odo retenci\303\263n", nullptr));
        Lb_TenRetCiclico->setText(QApplication::translate("MainWindow", "Tensi\303\263n [mV]", nullptr));
        Lb_TiemRetCiclico->setText(QApplication::translate("MainWindow", "Tiempo [seg]", nullptr));
        grupoPeriodoRetencion_3->setTitle(QApplication::translate("MainWindow", "Per\303\255odo rampa", nullptr));
        Lb_VelCiclico->setText(QApplication::translate("MainWindow", "Velocidad [mV/seg]", nullptr));
        Lb_CicCiclico->setText(QApplication::translate("MainWindow", "Ciclos", nullptr));
        Lb_TenCiclico->setText(QApplication::translate("MainWindow", "Tensi\303\263n [mV]", nullptr));
        Bt_IniciarCiclico->setText(QApplication::translate("MainWindow", "Iniciar Medici\303\263n", nullptr));
        Num_GanCorriente->setItemText(0, QApplication::translate("MainWindow", "x0.1", nullptr));
        Num_GanCorriente->setItemText(1, QApplication::translate("MainWindow", "x1", nullptr));
        Num_GanCorriente->setItemText(2, QApplication::translate("MainWindow", "x5", nullptr));
        Num_GanCorriente->setItemText(3, QApplication::translate("MainWindow", "x10", nullptr));

        Lb_GanCorriente->setText(QApplication::translate("MainWindow", "Ganancia Corriente:", nullptr));
        tipoMedicion->setTabText(tipoMedicion->indexOf(tabCiclico), QApplication::translate("MainWindow", "Barrido C\303\255clico", nullptr));
        Bt_AutoCentrar->setText(QApplication::translate("MainWindow", "Centrar", nullptr));
        Lb_deltaY->setText(QApplication::translate("MainWindow", "\316\224Y:", nullptr));
        Lb_deltaX->setText(QApplication::translate("MainWindow", "\316\224X:", nullptr));
        Lb_deltaZ->setText(QApplication::translate("MainWindow", "Z:", nullptr));
        Num_deltaX->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Num_deltaY->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Num_deltaZ->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Bt_Cursores->setText(QApplication::translate("MainWindow", "Cursores", nullptr));
        Conectar_Bt->setText(QApplication::translate("MainWindow", "Iniciar Conexi\303\263n USB", nullptr));
        Desconectar_Bt->setText(QApplication::translate("MainWindow", "Terminar Conexi\303\263n USB", nullptr));
        Lb_deltaXa->setText(QApplication::translate("MainWindow", "Xa:", nullptr));
        Lb_deltaXb->setText(QApplication::translate("MainWindow", "Xb:", nullptr));
        Num_deltaXa->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Num_deltaXb->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Lb_deltaYa->setText(QApplication::translate("MainWindow", "Ya:", nullptr));
        Lb_deltaYb->setText(QApplication::translate("MainWindow", "Yb:", nullptr));
        Num_deltaYb->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        Num_deltaYa->setText(QApplication::translate("MainWindow", "0.000", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(medicion), QApplication::translate("MainWindow", "Medici\303\263n", nullptr));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", nullptr));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Ayuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
