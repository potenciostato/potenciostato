#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QIcon>
#include <QDoubleSpinBox>

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
    void on_pushButton_clicked();
    void on_Conectar_Bt_clicked();
    void on_Desconectar_Bt_clicked();
    void on_Bt_IniciarLineal_clicked();
    void on_Bt_Abortar_clicked();
    void on_Bt_Capturar_clicked();
    void on_Bt_Exportar_clicked();

    void help();

    void makePlot();
    void onTimeout();
    void realtimeData();
    void graficarValores(int curva = 0, double multiplicadorX = 1, double multiplicadorY = 10);
    void refrescarValores(double x[10], double y[10], int curva = 0, double multiplicadorX = 1, double multiplicadorY = 10);
    void limpiarGraficos();
    void inicializarGraficos(int curva = 0);
    void terminoMedicion();
    void desconectarUSB();

    void forzarAbortar();

    void on_Bt_IniciarCiclico_clicked();
    void on_Bt_FTCiclico_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
