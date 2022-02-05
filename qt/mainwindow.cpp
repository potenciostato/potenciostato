#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include "qmessagebox.h"

#include "globales.h"
#include "libusb.h"

#include "time.h"

bool debugging = DISABLED;

QVector<double> valoresX(CANT_VALORES), valoresY(CANT_VALORES); // declara vectores con 10 posiciones (0..9)



double primer_curva_paracetamolX[CANT_VALORES] = {
    0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59,
    0.60, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69,
    0.70, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79,
    0.80, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89,
    0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99,
    1.00
};
double primer_curva_paracetamolY[CANT_VALORES] = {
    0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010,
    0.011, 0.020, 0.011, 0.015, 0.011, 0.018, 0.023, 0.011, 0.036, 0.050,
    0.111, 0.332, 0.552, 0.773, 0.994, 1.210, 1.430, 1.660, 1.880, 2.100,
    2.320, 2.540, 2.760, 2.980, 3.200, 3.420, 3.500, 3.550, 3.580, 3.570,
    3.520, 3.460, 3.410, 3.370, 3.320, 3.250, 3.190, 3.140, 3.090, 3.040,
    3.000
};
int p_refresco = 0;
double puntosX[CANT_VALORES] = {0};
double puntosY[CANT_VALORES] = {0};

//char metodo[30] = "BarridoLineal";
char metodo[30] = "BarridoCiclico"; //TODO: rehacer la verificacion del modo con defines
int medicion_habilitada = 0;
char frec_periodo = FRECUENCIA;
bool demostracion = false;
bool grafico_inicial = false;
int grafico_demostracion;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Potenciostato");

    //asocio la accion triggered del ui->actionAyuda a la funcion help() (dentro de slots el mainwindow.h)
    connect(ui->actionAyuda, SIGNAL(triggered()), this, SLOT(help()));
    MainWindow::inicializarGraficos();
    if (demostracion == true){
        grafico_demostracion = 0;
    }
    if (grafico_inicial == true){
        MainWindow::graficarValores();
    }

    // Configuracion timer
    auto timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    timer->start(MILISEGUNDOS_POLLING);
    //Todo: configurar los milisegundos de polling desde el entorno

    //el timer se usara para refrescar el grafico en base a la medicion obtenida por USB del potenciostato
}

MainWindow::~MainWindow() //al cerrar la ventana se llama a este metodo
{
    delete ui;

    MainWindow::desconectarUSB();
}

// Funcion para desconectar el USB
void MainWindow::desconectarUSB(){
    if(connected > 0)
    {
        libusb_free_device_list(devs,1);
        libusb_exit(ctx);

        qDebug() << "Se ha desconectado el Dispositivo: " << Dispositivo;

        connected = 0;
        Dispositivo = -1;
    }
}

// Funcion para inicializar y graficar una sola vez una curva, no apta para ser llamada dentro de un Timer
void MainWindow::graficarValores(int curva, double multiplicadorX, double  multiplicadorY){
    int i;
    double tempX[CANT_VALORES] = {0};
    double tempY[CANT_VALORES] = {0};

    // aplicamos escalamiento por multiplicadores de unidades

    // multiplicadorX = 1.00;
    for (i=0; i<CANT_VALORES; ++i)
    {
        tempX[i] = primer_curva_paracetamolX[i]*multiplicadorX;
    }

    // multiplicadorY = 10.00;
    for (i=0; i<CANT_VALORES; ++i)
    {
        tempY[i] = primer_curva_paracetamolY[i]*multiplicadorY;
    }

    // se almacena en valoresX y valoresY que son los QVectors que se grafican
    for (i=0; i<CANT_VALORES; ++i)
    {
        valoresX[i] = tempX[i];
        valoresY[i] = tempY[i];
    }

    // inicializar graficos
    MainWindow::inicializarGraficos(curva);
    ui->customPlot->graph(curva)->setData(valoresX, valoresY);
    ui->customPlot->replot();

    // hace interactivo al grafico para que se pueda arrastrar, hacer zoom y seleccionar las curvas
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

// Funcion que se debera llamar desde un Timer para refrescar los valores en el grafico
void MainWindow::refrescarValores(double x[CANT_VALORES], double y[CANT_VALORES], int curva, double multiplicadorX, double multiplicadorY){
    // opcionalmente, para hallar el largo del vector x
    //size_t n = (&x)[1] - x;
    //int largo = (int) n;
    int i;
    double tempX[CANT_VALORES] = {0};
    double tempY[CANT_VALORES] = {0};

    // Se aplica la escala correspondiente
    // multiplicadorX = 1.00;
    for (i=0; i < CANT_VALORES; ++i)
    {
        tempX[i] = x[i]*multiplicadorX;
    }

    // multiplicadorY = 10.00;
    for (i=0; i < CANT_VALORES; ++i)
    {
        tempY[i] = y[i]*multiplicadorY;
    }

    for (i=0; i < CANT_VALORES; ++i)
    {
        valoresX[i] = tempX[i];
        valoresY[i] = tempY[i];
    }
    // poner datos en el grafico
    //ui->customPlot->addGraph();
    ui->customPlot->graph(curva)->setData(valoresX, valoresY);
    ui->customPlot->replot();

    // hace interactivo al grafico para que se pueda arrastrar, hacer zoom y seleccionar las curvas
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::onTimeout(){
    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len, i=0;
    int send_ret, recv_ret;

    unsigned int cuentas_corriente, cuentas_tension;
    float volts_tension, volts_corriente;
    //qDebug() << clock() << "TimeOut";
    for(i=0;i<PUNTOS_RECIBIDOS;i++){
        if (demostracion == false){
            //Se envia inicio de medición al LPC
            //envio....
            //se queda esperando al Recibido
            // si llega recibido OK continuar

            if (connected == 1 && medicion_habilitada == 1){
                //se enviara un SEND DATA
                buffer[0] = OC_SENDDATA;
                qDebug() << clock() << "Se pide Dato";
                send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
                qDebug() << clock() << "Pedido Dato enviado";
                recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
                //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);
                qDebug() << clock() << "Dato recibido";
                if (debugging == ENABLED){
                    qDebug() << clock();
                    qDebug() << "codigo envio" << send_ret;
                    qDebug() << "dato enviado" << buffer[0];
                    qDebug() << "codigo recepcion" << recv_ret;
                    qDebug() << "OP Code recibido" << recv_data[0];
                    qDebug() << "Byte libre" << recv_data[1];
                    qDebug() << "Corriente: " << recv_data[3] << recv_data[2];
                    qDebug() << "Tension: " << recv_data[5] << recv_data[4];
                    qDebug() << "Bytes libres: " << recv_data[7] << recv_data[6];
                }

                if (recv_data[0] == OC_SENDDATA){ //si hay datos
                    cuentas_corriente = ((recv_data[3] << 8) | (recv_data[2]));
                    cuentas_tension = ((recv_data[5] << 8) | (recv_data[4]));
                    if (debugging == ENABLED){
                        qDebug() << "Cuentas corriente: " << cuentas_corriente;
                        qDebug() << "Cuentas tension: " << cuentas_tension;
                    }
                    //volts_corriente = cuentas_corriente;
                    //volts_tension = cuentas_tension;
                    volts_corriente = (cuentas_corriente * ADC_CORRIENTE_MAX) / pow(2,ADC_CORRIENTE_BITS) / 10;
                    volts_tension = (cuentas_tension * ADC_TENSION_MAX) / pow(2,ADC_TENSION_BITS) / 10;
                    if (debugging == ENABLED){
                        qDebug() << "Corriente [V]: " << volts_corriente;
                        qDebug() << "Tension [V]: " << volts_tension;
                    }

                    puntosX[p_refresco] = volts_tension; //ANTES: el rango en el grafico va desde 0 a 1
                    puntosY[p_refresco] = volts_corriente; //ANTES: el rango en el grafico va desde 0 a 3

                    //TODO: si no hay mas datos esperar un tiempo para pedir
                    //if (recv_data[0] == OC_SENDDATA_ERR){
                    //APLICAR RETARDO
                    //}
                }
                if (recv_data[0] == OC_CYCLEEND){ //si termino la medicion
                    //Se termina la medición
                    qDebug() << "INFO: OC_CYCLEEND recibido";
                    qDebug() << "INFO: Termino la medición => se procederá a abortar la medición";
                    MainWindow::forzarAbortar();
                }

                if (recv_data[0] == OC_SENDDATAEND){ //si ya no hay mas datos
                    //Se termina la medición
                    qDebug() << "INFO: OC_SENDDATAEND recibido";
                    qDebug() << "INFO: Ya no hay mas datos";

                    qDebug() << "Envío de refresco al gráfico";
                    qDebug() << clock() << "inicio refrescar valores";
                    MainWindow::refrescarValores(puntosX, puntosY);
                    qDebug() << clock() << "termino refrescar valores";
                    //Se termina la medición
                    qDebug() << "Termino la medicion";
                    medicion_habilitada = 0;
                    MainWindow::terminoMedicion();
                    if (demostracion == false){
                        p_refresco = 0;
                        medicion_habilitada = 0;
                        for(int i=0; i<CANT_VALORES; i++){
                            puntosX[i] = 0;
                            puntosY[i] = 0;
                        }
                    }
                    if (demostracion == true){
                        p_refresco = 0;
                        medicion_habilitada = 0;
                    }
                }
            }
        }
        if (demostracion == true){
            for (i=0; i < p_refresco; ++i)
            {
                puntosX[i] = primer_curva_paracetamolX[i];
                puntosY[i] = primer_curva_paracetamolY[i];
            }
        }

        // ESTE IF TODAVIA NO ESTA PROBADO
        /*if (demostracion == false){
            if (strcmp(metodo,"BarridoLineal") == 0 && medicion_habilitada == 1){
                //este if debera ser la condicion para el termino de la medicion
                //es decir, se recibe el dato, si no es el fin de la medicion se appendea el dato
                //si es el fin de la medicion se envia el Recibido y se termina la medicion
                if (true){
                    qDebug() << "Termino la medicion";
                    medicion_habilitada = 0;
                    MainWindow::terminoMedicion();
                }else{
                    p_refresco ++;
                    qDebug() << "Envio de refresco al grafico";
                    MainWindow::refrescarValores(tempX, tempY);
                }
            }
        }*/

        if (demostracion == false){
            if (strcmp(metodo,"BarridoCiclico") == 0  && medicion_habilitada == 1){ //antes era Reiterativo
                if (p_refresco >= (CANT_VALORES-1)){
                    p_refresco = 0;
                    qDebug() << "Limpieza de graficos";
                    MainWindow::limpiarGraficos();
                    qDebug() << "Inicializacion del grafico 0";
                    MainWindow::inicializarGraficos();
                }else{
                    p_refresco ++;
                    if (p_refresco % PUNTOS_REFRESCO == 0){
                        qDebug() << clock() << "Envío de refresco al gráfico";
                        MainWindow::refrescarValores(puntosX, puntosY);
                        qDebug() << clock() << "termino refrescar valores";
                    }
                }
            }
        }
        if (demostracion == true){
        if (strcmp(metodo,"BarridoLineal") == 0 && medicion_habilitada == 1){
            if (p_refresco >= CANT_VALORES && grafico_demostracion == 0){
                p_refresco = 0;
                qDebug() << "Termino el primer grafico de demostracion";
                grafico_demostracion = 1;
                MainWindow::inicializarGraficos(grafico_demostracion);
            }
            else if (p_refresco >= CANT_VALORES && grafico_demostracion == 1){
                p_refresco = 0;
                qDebug() << "Termino el segundo grafico de demostracion";
                grafico_demostracion = 2;
                MainWindow::inicializarGraficos(grafico_demostracion);
            }
            else if (p_refresco >= CANT_VALORES && grafico_demostracion == 2){
                p_refresco = 0;
                qDebug() << "Termino el tercer grafico de demostracion";
                grafico_demostracion = 3;
                MainWindow::inicializarGraficos(grafico_demostracion);
            }
            else if (p_refresco >= CANT_VALORES && grafico_demostracion == 3){
                p_refresco = 0;
                qDebug() << "Termino la medicion";
                medicion_habilitada = 0;
                MainWindow::terminoMedicion();
            }else{
                p_refresco ++;
                qDebug() << "Envío de refresco al gráfico";
                MainWindow::refrescarValores(puntosX, puntosY,
                                             grafico_demostracion,
                                             1,
                                             10*(1-grafico_demostracion*0.15));
            }
        }

        if (strcmp(metodo,"BarridoCiclico") == 0  && medicion_habilitada == 1){ //antes era Reiterativo
            if (p_refresco >= CANT_VALORES){
                p_refresco = 0;
                qDebug() << "Limpieza de graficos";
                MainWindow::limpiarGraficos();
                qDebug() << "Inicializacion del grafico 0";
                MainWindow::inicializarGraficos();
            }else{
                p_refresco ++;
                qDebug() << "Envío de refresco al gráfico";
                MainWindow::refrescarValores(puntosX, puntosY);
            }
        }
    }
    }
}

// Funcion para inicializar las curvas de los graficos
void MainWindow::inicializarGraficos(int curva){
    // se crea el graph
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("Tension [V]");
    ui->customPlot->yAxis->setLabel("Corriente [uA]");
    // se puede especificar el rango fijo
    ui->customPlot->xAxis->setRange(0, 3.0);
    ui->customPlot->yAxis->setRange(0, 50);

    // hace que los ejes escalen automaticamente
    ui->customPlot->graph(curva)->rescaleAxes();
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // modificar apariencia del grafico
    if (curva == 0){
        ui->customPlot->graph(curva)->setPen(QPen(Qt::blue));
        //ui->customPlot->graph(curva)->setBrush(QBrush(QColor(255, 0, 0, 20)));
        ui->customPlot->graph(curva)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(curva)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    }
    if (curva == 1){
        ui->customPlot->graph(curva)->setPen(QPen(Qt::green));
        ui->customPlot->graph(curva)->setBrush(QBrush(QColor(0, 255, 0, 20)));
    }
    if (curva == 2){
        ui->customPlot->graph(curva)->setPen(QPen(Qt::red));
        ui->customPlot->graph(curva)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    }
    if (curva == 3){
        ui->customPlot->graph(curva)->setPen(QPen(Qt::black));
        ui->customPlot->graph(curva)->setBrush(QBrush(QColor(0, 0, 0, 20)));
    }

}

void MainWindow::limpiarGraficos(){
    ui->customPlot->clearGraphs();
}

// Es llamada cuando el LPC y el QT estan al tanto del termino de la medición
void MainWindow::terminoMedicion(){
    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len;
    int send_ret, recv_ret;

    qDebug() << "Terminar Medición";

    //se enviara un END MEASUREMENT
    buffer[0] = OC_ENDMEASUREMENT;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado" << buffer[0];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

    ui->Bt_IniciarLineal->setEnabled(true);
    ui->Bt_IniciarCiclico->setEnabled(true);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Capturar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "hola";
}

void MainWindow::on_Bt_IniciarLineal_clicked()
{
    if (connected != 1){
        qDebug() << "Dispositivo no conectado";
        return;
    }

    qDebug() << "Iniciar Medición";
    //Deshabilita Iniciar
    ui->Bt_IniciarLineal->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);

    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len;
    int send_ret, recv_ret;
    uint8_t tension_pico = 0;
    //int tension_pico = 0;
    uint32_t frecuencia = 0;

    //Se procesa la configuración elegida
    tension_pico = (255 * (1000 * ui->Num_VLineal->value())) / MV_TENSION_MAXIMA;
    frecuencia = ui->Num_HzLineal->value() * 1000;

    qDebug() << "tension_pico: " << tension_pico;
    qDebug() << "frecuencia: " << frecuencia;

    //se enviara un INIT MEASUREMENT LINEAL
    buffer[0] = OC_INITMEASUREMENTLINEAL;
    buffer[1] = 0x00;
    buffer[2] = tension_pico;
    buffer[3] = (uint8_t) ((frecuencia & 0xFF0000) >> 16);
    buffer[4] = (uint8_t) ((frecuencia & 0x00FF00) >> 8);
    buffer[5] = (uint8_t) (frecuencia & 0x0000FF);
    buffer[6] = 0x00;
    buffer[7] = 0x00;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado completo"
             << buffer[0] << buffer[1] << buffer[2] << buffer[3]
             << buffer[4] << buffer[5] << buffer[6] << buffer[7];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

    //Limpia el gráfico y lo inicializa
    MainWindow::limpiarGraficos();
    MainWindow::inicializarGraficos();

    //TODO: verificar que el LPC responda con el OP_CODE correspondiente
    //      y asi, iniciar la medicion

    //Se activa la medicion en el Timer
    medicion_habilitada = 1;

    if (demostracion == true){
        p_refresco = 0;
    }

    //Habilita abortar y capturar
    ui->Bt_Abortar->setEnabled(true);
    ui->Bt_Capturar->setEnabled(true);

}

void MainWindow::on_Bt_IniciarCiclico_clicked()
{
    if (connected != 1){
        qDebug() << "Dispositivo no conectado";
        return;
    }

    qDebug() << "Iniciar Medición";
    //Deshabilita Iniciar
    ui->Bt_IniciarCiclico->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);

    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len;
    int send_ret, recv_ret;
    uint8_t tension_pico = 0;
    //int tension_pico = 0;
    uint32_t frecuencia = 0;
    uint8_t ciclos = 0;

    //Se procesa la configuración elegida
    tension_pico = (255 * (1000 * ui->Num_VCiclico->value())) / MV_TENSION_MAXIMA;
    if (frec_periodo == FRECUENCIA){
        frecuencia = ui->Num_HzCiclico->value() * 1000;
    }else{
        frecuencia = (1/ui->Num_SegCiclico->value()) * 1000;
    }
    ciclos = ui->Num_CicCiclico->value();

    qDebug() << "tension_pico: " << tension_pico;
    qDebug() << "frecuencia: " << frecuencia;
    qDebug() << "ciclos: " << ciclos;

    //se enviara un INIT MEASUREMENT CYCLICAL
    buffer[0] = OC_INITMEASUREMENTCYCLICAL;
    buffer[1] = 0x00;
    buffer[2] = (uint8_t) tension_pico;
    buffer[3] = (uint8_t) ((frecuencia & 0xFF0000) >> 16);
    buffer[4] = (uint8_t) ((frecuencia & 0x00FF00) >> 8);
    buffer[5] = (uint8_t) (frecuencia & 0x0000FF);
    buffer[6] = (uint8_t) ciclos;
    buffer[7] = 0x00;


    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado completo"
             << buffer[0] << buffer[1] << buffer[2] << buffer[3]
             << buffer[4] << buffer[5] << buffer[6] << buffer[7];
    qDebug() << "dato enviado [0]" << buffer[0];

    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

    //Limpia el gráfico y lo inicializa
    MainWindow::limpiarGraficos();
    MainWindow::inicializarGraficos();

    //TODO: verificar que el LPC responda con el OP_CODE correspondiente
    //      y asi, iniciar la medicion

    //Se activa la medicion en el Timer
    medicion_habilitada = 1;

    if (demostracion == true){
        p_refresco = 0;
    }

    //Habilita abortar y capturar
    ui->Bt_Abortar->setEnabled(true);
    ui->Bt_Capturar->setEnabled(true);
}

void MainWindow::on_Bt_Abortar_clicked()
{
    MainWindow::forzarAbortar();
}

void MainWindow::on_Bt_Capturar_clicked()
{
    qDebug() << "Capturar Medición";

    //Almacena en la carpeta mediciones una foto de la medición actual
    // con un timestamp y los datos en csv correspondientes.

}

void MainWindow::on_Bt_Exportar_clicked()
{
    qDebug() << "Exportar Medición";

    //Almacena en la carpeta mediciones una foto de la medición final
    // con un timestamp y los datos en csv correspondientes.
    //Recibe la elección del nombre de los 2 archivos a guardar (imagen y datos en csv)

}


void MainWindow::on_Conectar_Bt_clicked()
{
    signed int r;
    unsigned int cnt;
    unsigned char i;
    signed int j, k, p;

    r = libusb_init(&ctx);

    //libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation

    cnt = libusb_get_device_list(ctx,&devs);

    qDebug() << "INFO: Hay" << cnt << "dispositivos conectados";

    for (i = 0; i < cnt; i++)
    {
        r = libusb_get_device_descriptor(devs[i],&desc);

        if(r < 0)
        {
            qDebug() << "Error con el device descriptor del dispositivo";
        }

        if(desc.idProduct == MY_PRODUCT && desc.idVendor == MY_VENDOR)
        {
            //ui->Enviar_Bt->setEnabled(true);

            Dispositivo = i;

            qDebug() << "Mi dispositivo es el" << i;
            qDebug() << "Tiene " << desc.bNumConfigurations << " cantidad de configuraciones";
            qDebug() << "Vendor ID: " << desc.idVendor;
            qDebug() << "Product ID: " << desc.idProduct;
            qDebug() << "Device Class: " << desc.bDeviceClass;
            qDebug() << "Serial Number: " << desc.iSerialNumber;


            libusb_get_config_descriptor(devs[Dispositivo], 0, &config);


            qDebug() <<"Interfaces: "<<(uint8_t)config->bNumInterfaces;

            for(j=0; j<(uint8_t )(config->bNumInterfaces); j++)
            {
                inter = &config->interface[j];

                qDebug()<<"Cantidad de conf. alternativas: "<<(uint8_t) (inter->num_altsetting);

                for(k=0; k < (uint8_t) (inter->num_altsetting); k++)
                {
                    interdesc = &inter->altsetting[k];

                    qDebug() << "Cant. de Interfaces: "<<(uint8_t )interdesc->bInterfaceNumber;

                    qDebug() << "Cant. de Endpoints: "<<(uint8_t )interdesc->bNumEndpoints;

                    for(p= 0 ; p<(uint8_t )interdesc->bNumEndpoints; p++)
                    {
                        epdesc = &interdesc->endpoint[p];

                        qDebug() << "Tipo de Descriptor: "<<(uint8_t )epdesc->bDescriptorType;

                        qDebug() << "Dirección de EP: "<<(uint8_t )epdesc->bEndpointAddress;

                    }

                }
            }

            libusb_free_config_descriptor(config);

            r = libusb_open(devs[Dispositivo],&dev_handle);

            if(r<0)
            {
                qDebug() << "Error" << r << "abriendo dispositivo";
                return;
            }
        }
    }

    if (Dispositivo == -1){
        qDebug() << "ERROR: Error al querer conectar con el dispositivo";
        qDebug() << "¿Está conectado el LPC por USB?";
        return;
    }

    // Si llega hasta aca es porque esta conectado
    connected = 1;

    // Se habilita el inicio de medición
    ui->Bt_IniciarLineal->setEnabled(true);
    ui->Bt_IniciarCiclico->setEnabled(true);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Capturar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);
    ui->Conectar_Bt->setEnabled(false);
    ui->Desconectar_Bt->setEnabled(true);

    //QString Buff;

    unsigned int Datos;
    unsigned int Potencia;

    //unsigned char TxData [4];
    unsigned char TxData[4];
    //unsigned char RxData [4];
    unsigned char RxData[4];

    int Enviados=0;

    int actual_length;

    //Buff = ui->TBox->toPlainText();

    //Datos = Buff.toInt();


    /*for (i=0 ; i < 4; i++)
    {
        TxData[3-i] = Datos % 10;
        Datos = Datos / 10;
    }

    qDebug() << "-----Inicio Bytes Enviados-----";
    qDebug() << TxData[0];
    qDebug() << TxData[1];
    qDebug() << TxData[2];
    qDebug() << TxData[3];
    qDebug() << "-----Fin Bytes Enviados-----";
    */

    //if(data1 > 80)
    //{
    //    QMessageBox::warning(this,"Error","El valor ingresado es inválido",QMessageBox::Retry);

    //    return;
    //}

    libusb_claim_interface(dev_handle, 0);

/*    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len;
    int send_ret, recv_ret;

    //se enviara un INIT MEASUREMENT
    buffer[0] = OC_INITMEASUREMENT;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado" << buffer[0];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];*/

    /*Enviados = libusb_interrupt_transfer(dev_handle , 0x01 , TxData , (sizeof (TxData)) * 4, &actual_length , 1000);
    libusb_interrupt_transfer(dev_handle , 0x81 , RxData , (sizeof (RxData)) * 4, &actual_length , 1000);

    //Datos = 0;

    for (i=0 ; i < 4; i++)
    {
        Potencia = (unsigned int) pow((double) 10 , (double) i);
        //Datos += RxData[3-i] * Potencia;
    }

    //Buff=QString::number(Datos);

    //ui->TBox_2->setText(Buff);

    qDebug() << "-----Inicio Bytes Recibidos-----";
    qDebug() << RxData[0];
    qDebug() << RxData[1];
    qDebug() << RxData[2];
    qDebug() << RxData[3];
    qDebug() << "-----Fin Bytes Recibidos-----";*/
    qDebug() << Dispositivo;
    qDebug() << Enviados;
}

void MainWindow::help()
{
    qDebug() << "Ayuda";
    //link a documentacion https://doc.qt.io/qt-5/qmessagebox.html#about
    QMessageBox::about(this,"Sobre Potenciostato","Potenciostato versión 1.0");
}


void MainWindow::forzarAbortar()
{

    qDebug() << "Abortar Medición";
    //Deshabilita Abortar
    ui->Bt_Abortar->setEnabled(false);

    //Se envia abortar la medición al LPC
    //envio....
    //se queda esperando al Recibido
    // si llega recibido OK continuar

    unsigned char buffer[8] = {0x0};
    unsigned char recv_data[8] = {0x0};
    int len;
    int send_ret, recv_ret;

    //Se envia inicio de medición al LPC
    //envio....
    //se queda esperando al Recibido
    // si llega recibido OK continuar

    //se enviara un INIT MEASUREMENT
    buffer[0] = OC_ABORTMEASUREMENT;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * 8, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 8, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado" << buffer[0];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

}


/* -------------------- FUNCIONES DEPRECADAS -------------------- */


void MainWindow::makePlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
void MainWindow::realtimeData(){
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        // add data to lines:
        ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
        ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
        // rescale value (vertical) axis to fit the current data:
        //ui->customPlot->graph(0)->rescaleValueAxis();
        //ui->customPlot->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        /*ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
                , 0);*/
        qDebug() << QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size());
        lastFpsKey = key;
        frameCount = 0;
    }
}





void MainWindow::on_Desconectar_Bt_clicked()
{
    MainWindow::desconectarUSB();

    medicion_habilitada = 0;

    //Habilita la conexión
    ui->Conectar_Bt->setEnabled(true);
    ui->Bt_IniciarLineal->setEnabled(false);
    ui->Bt_IniciarCiclico->setEnabled(false);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Capturar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);
    ui->Desconectar_Bt->setEnabled(false);

}

void MainWindow::on_Bt_FTCiclico_clicked()
{
    if (frec_periodo == FRECUENCIA){
        frec_periodo = PERIODO;
        ui->Num_SegCiclico->setEnabled(true);
        ui->Num_HzCiclico->setEnabled(false);
    }
    else
    {
        frec_periodo = FRECUENCIA;
        ui->Num_SegCiclico->setEnabled(false);
        ui->Num_HzCiclico->setEnabled(true);
    }
}

