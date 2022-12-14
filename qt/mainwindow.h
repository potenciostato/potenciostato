#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QIcon>
#include <QDoubleSpinBox>
#include "qcustomplot.h"
#include "axistag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Conectar_Bt_clicked();
    void on_Desconectar_Bt_clicked();
    void on_Bt_IniciarCiclico_clicked();
    void on_Bt_Abortar_clicked();
    void on_Bt_Exportar_clicked();
    void on_Bt_AutoCentrar_clicked();
    void on_Bt_Cursores_clicked();

    void help();
    void abrirMedicion();

    void resetearValores();
    void selectionChanged();
    void mousePress(QMouseEvent* event);
    void mouseWheel();

    void makePlot();
    void onTimeout();
    void realtimeData();
    void graficarValores(int curva = 0, double multiplicadorX = 1, double multiplicadorY = 10);
    void refrescarValores(int curva = 0);
    void limpiarGraficos();
    void inicializarGraficos(int curva = 0);
    void autoCentrar();
    void menuContextual(QPoint pos);
    void calcularCursor(int x, int y, char cursor);
    void graficarCursor(char cursor);
    void refrescarDeltas();
    void habilitarCursor();
    void terminoMedicion();
    void desconectarUSB();

    void forzarAbortar();
    void exportarCSV();

private:
    Ui::MainWindow *ui;
    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
};
#endif // MAINWINDOW_H
