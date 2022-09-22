#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>
#include "qmessagebox.h"

#include "globales.h"
#include "libusb.h"
#include "time.h"

bool debugging = ENABLED;

QVector<double> valoresX(CANT_VALORES), valoresY(CANT_VALORES); // declara vectores con 10 posiciones (0..9)

int p_refresco = 0;
int p_refrescado = 0;

char metodo[30] = "BarridoCiclico"; //TODO: rehacer la verificacion del modo con defines
int medicion_habilitada = 0;
int estado_cursor = SIN_SELECCIONAR;
bool flag_inicial = true;
float a_med_x=0, a_med_y=0, b_med_x=0, b_med_y=0, med_z=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Potenciostato");

    //asocio la accion triggered del ui->actionAyuda a la funcion help() (dentro de slots el mainwindow.h)
    connect(ui->actionAyuda, SIGNAL(triggered()), this, SLOT(help()));

    //asocio la accion triggered del ui->actionAyuda a la funcion () (dentro de slots el mainwindow.h)
    connect(ui->actionAbrir_Medicion, SIGNAL(triggered()), this, SLOT(abrirMedicion()));

    // hace interactivo al grafico para que se pueda arrastrar, hacer zoom y seleccionar las curvas
    //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    // setup policy and connect slot for context menu popup:
    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(menuContextual(QPoint)));

    MainWindow::inicializarGraficos();

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

// Funcion que se debera llamar desde un Timer para refrescar los valores en el grafico
void MainWindow::refrescarValores(int curva){
    int i;
    if (p_refresco > p_refrescado){
        for (i = p_refrescado; (i < p_refresco) && (valoresX[i] != -1) && (valoresY[i] != -1); i++){
            ui->customPlot->graph(curva)->addData(valoresX[i], valoresY[i]);
        }
    }else{
        // en este caso se deberá tomar desde p_refrescado hasta CANTIDAD_VALORES y luego desde 0 hasta p_refresco
        for (i = p_refrescado; (i < CANT_VALORES) && (valoresX[i] != -1) && (valoresY[i] != -1); i++){
            ui->customPlot->graph(curva)->addData(valoresX[i], valoresY[i]);
        }
        for (i = 0; (i < p_refresco) && (valoresX[i] != -1) && (valoresY[i] != -1); i++){
            ui->customPlot->graph(curva)->addData(valoresX[i], valoresY[i]);
        }
    }
    ui->customPlot->replot();
    p_refrescado = p_refresco;
}

void MainWindow::onTimeout(){
    unsigned char buffer[LARGO_MENSAJE_SALIDA] = {0x0};
    unsigned char recv_data[LARGO_MENSAJE_ENTRADA] = {0x0};
    int len, i=0, j=0;
    int send_ret, recv_ret;

    unsigned int cuentas_corriente, cuentas_tension;
    float volts_tension, volts_corriente;
    //qDebug() << clock() << "TimeOut";
    for(i=0;i<REPORTES_A_RECIBIR;i++){
        //Se envia inicio de medición al LPC
        if (connected == 1 && medicion_habilitada == 1){
            //se enviara un SEND DATA
            buffer[0] = OC_SENDDATA;
            qDebug() << clock() << "Se pide Dato";
            send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * BITS_EN_UN_BYTE, &len, 1000);
            qDebug() << clock() << "Pedido Dato enviado";
            recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * BITS_EN_UN_BYTE, &len, 1000);

            if (debugging == ENABLED){
                qDebug() << "codigo envio" << send_ret;
                qDebug() << "dato enviado" << buffer[0];
                qDebug() << "codigo recepcion" << recv_ret;
                qDebug() << "OP Code recibido" << recv_data[0];
            }

            if (recv_ret < 0)
                continue;

            qDebug() << clock() << "Dato recibido";
            if (debugging == ENABLED){
                qDebug() << clock();
                qDebug() << "OP Code recibido" << recv_data[0];
                qDebug() << "Cantidad puntos:" << recv_data[1];
                //qDebug() << "respuesta[2]: " << recv_data[2];   //(medicion.corriente & 0xFF);
                //qDebug() << "respuesta[3]:" << recv_data[3];    //((medicion.corriente >> 8) & 0x0F) | ((medicion.tension & 0x0F) << 4);
                //qDebug() << "respuesta[4]:" << recv_data[4];    //(((medicion.tension) >> 4) & 0xFF);
                //qDebug() << "respuesta[5]: " << recv_data[5];
                //qDebug() << "respuesta[6]:" << recv_data[6];
                //qDebug() << "respuesta[7]: " << recv_data[7];
            }

            if (recv_data[0] == OC_SENDDATA){ // Si hay datos, ver cuantos
                for (j = 0; j < recv_data[1]; j++){
                    cuentas_corriente = (((recv_data[3+3*j] & 0x0F) << 8) | (recv_data[2+3*j]));
                    cuentas_tension = ((recv_data[4+3*j] << 4) | ((recv_data[3+3*j] & 0xF0) >> 4));
                    if (debugging == ENABLED){
                        qDebug() << "Cuentas corriente: " << cuentas_corriente;
                        qDebug() << "Cuentas tension: " << cuentas_tension;
                    }
                    // Se hace la cuenta para pasar de cuentas a Volts para la tension y la corriente
                    volts_corriente = (cuentas_corriente * ADC_CORRIENTE_MAX) / pow(2,ADC_CORRIENTE_BITS) / 10;
                    volts_tension = (cuentas_tension * ADC_TENSION_MAX) / pow(2,ADC_TENSION_BITS) / 10;
                    if (debugging == ENABLED){
                        qDebug() << "Corriente [V]: " << volts_corriente;
                        qDebug() << "Tension [V]: " << volts_tension;
                    }

                    // probablemente aca haya que aplicar algun multiplicador (o no)
                    // en graficarValores tengo double multiplicadorX = 1, double multiplicadorY = 10

                    valoresX[p_refresco] = (volts_tension-OFFSET_TENSION) * MULT_TENSION; //ANTES: el rango en el grafico va desde 0 a 1
                    valoresY[p_refresco] = (volts_corriente-OFFSET_CORRIENTE) * MULT_CORRIENTE; //ANTES: el rango en el grafico va desde 0 a 3

                    if (p_refresco >= (CANT_VALORES-1)){
                        p_refresco = 0;
                    }else{
                        p_refresco ++;
                        if (p_refresco % PUNTOS_REFRESCO == 0){
                            qDebug() << clock() << "Envío de refresco al gráfico";
                            MainWindow::refrescarValores();
                            qDebug() << clock() << "termino refrescar valores";
                        }
                    }

                }
            }
            if (recv_data[0] == OC_CYCLEEND){ //si termino la medicion
                //Se termina la medición
                qDebug() << "INFO: OC_CYCLEEND recibido";
                // Se deshabilita el boton de abortar
                ui->Bt_Abortar->setEnabled(false);
            }

            if (recv_data[0] == OC_SENDDATAEND){ //si ya no hay mas datos
                //Se termina la medición
                qDebug() << "INFO: OC_SENDDATAEND recibido";
                qDebug() << "INFO: Ya no hay mas datos";

                qDebug() << "Envío de refresco al gráfico";
                qDebug() << clock() << "inicio refrescar valores";
                MainWindow::refrescarValores();
                qDebug() << clock() << "termino refrescar valores";
                MainWindow::autoCentrar();
                //Se termina la medición
                qDebug() << "Termino la medicion";
                medicion_habilitada = 0;
                MainWindow::terminoMedicion();
                p_refresco = 0;
            }
        }
    }
}

// Funcion para inicializar las curvas de los graficos
void MainWindow::inicializarGraficos(int curva){
    // se crea el graph
    ui->customPlot->addGraph(); //para la medicion
    ui->customPlot->addGraph(); //para la linea que une los cursores [1]
    ui->customPlot->addGraph(); //para la linea horizontal del cursor A [2]
    ui->customPlot->addGraph(); //para la linea vertical del cursor A [3]
    ui->customPlot->addGraph(); //para la linea horizontal del cursor B [4]
    ui->customPlot->addGraph(); //para la linea vertical del cursor B [5]
    ui->customPlot->xAxis->setLabel("Tension [mV]");
    ui->customPlot->yAxis->setLabel("Corriente [uA]");

    // hace que los ejes escalen automaticamente con los valores actuales
    ui->customPlot->graph(curva)->rescaleAxes();

    // se puede especificar el rango fijo
    if (flag_inicial == true){
        // TODO: se debera hacer una calibración para saber donde centrar el gráfico
        ui->customPlot->xAxis->setRange(-1800, 1300);
        ui->customPlot->yAxis->setRange(-1200, 1000);
        flag_inicial = false;
    }
    ui->customPlot->axisRect()->setupFullAxesBox();
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // modificar apariencia del grafico
    if (curva == 0){
        ui->customPlot->graph(curva)->setPen(QPen(Qt::blue));
        //ui->customPlot->graph(curva)->setBrush(QBrush(QColor(255, 0, 0, 20)));
        ui->customPlot->graph(curva)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(curva)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

        ui->customPlot->graph(1)->setPen(QPen(Qt::green));
        //ui->customPlot->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20)));
        ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
        //ui->customPlot->graph(curva+1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, QColor(0, 255, 0, 20), 2));

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

void MainWindow::autoCentrar(){
    ui->customPlot->graph(0)->rescaleAxes(false);
    ui->customPlot->replot();
}

// Es llamada cuando el LPC y el QT estan al tanto del término de la medición
void MainWindow::terminoMedicion(){
    unsigned char buffer[LARGO_MENSAJE_SALIDA] = {0x0};
    unsigned char recv_data[LARGO_MENSAJE_ENTRADA] = {0x0};
    int len;
    int send_ret, recv_ret;

    qDebug() << "Terminar Medición";

    //se enviara un END MEASUREMENT
    buffer[0] = OC_ENDMEASUREMENT;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * BITS_EN_UN_BYTE, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * BITS_EN_UN_BYTE, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado" << buffer[0];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

    ui->Bt_IniciarCiclico->setEnabled(true);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(true);
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

    unsigned char buffer[LARGO_MENSAJE_SALIDA] = {0x0};
    unsigned char recv_data[LARGO_MENSAJE_ENTRADA] = {0x0};
    int len;
    int send_ret, recv_ret;
    int tension_punto1 = 0;    //min: -1000 mV, max: 1000 mV
    int tension_punto2 = 0;    //min: -1000 mV, max: 1000 mV
    int tension_punto3 = 0;    //min: -1000 mV, max: 1000 mV
    uint8_t velocidad = 0;         //max: 255 mV/s
    uint8_t tiempo_retencion = 0;  //max: 255 seg
    int16_t tension_retencion = 0; //min: -1000 mV, max: 1000 mV
    uint8_t ciclos = 0;            //max: 255 ciclos
    QString str_ganancia_corriente;
    uint8_t ganancia_corriente = GAN_CORRIENTE_X1;

    //Se procesa la configuración elegida
    //la cual consiste en el protocolo detallado en: https://docs.google.com/document/d/1LWbUOdiwlQI_1ugtcBbvklIMVfBlg8_1/edit#heading=h.v8ol8v6hjwx
    tension_punto1 = ui->Num_mVTen1Ciclico->value();
    tension_punto2 = ui->Num_mVTen2Ciclico->value();
    tension_punto3 = ui->Num_mVTen3Ciclico->value();
    tension_retencion = ui->Num_mVTenRetCiclico->value();
    velocidad = ui->Num_mVSegVelCiclico->value();
    tiempo_retencion = ui->Num_SegRetCiclico->value();
    ciclos = ui->Num_CicCiclico->value();
    str_ganancia_corriente = ui->Num_GanCorriente->currentText();

    if (str_ganancia_corriente.compare("x0.1") == 0)
        ganancia_corriente = GAN_CORRIENTE_X01;
    if (str_ganancia_corriente.compare("x1") == 0)
        ganancia_corriente = GAN_CORRIENTE_X1;
    if (str_ganancia_corriente.compare("x5") == 0)
        ganancia_corriente = GAN_CORRIENTE_X5;
    if (str_ganancia_corriente.compare("x10") == 0)
        ganancia_corriente = GAN_CORRIENTE_X10;

    qDebug() << "tension_punto1:" << tension_punto1;
    qDebug() << "tension_punto2:" << tension_punto2;
    qDebug() << "tension_punto3:" << tension_punto3;
    qDebug() << "tension_retencion:" << tension_retencion;
    qDebug() << "velocidad:" << velocidad;
    qDebug() << "tiempo_retencion:" << tiempo_retencion;
    qDebug() << "ciclos:" << ciclos;
    qDebug() << "str_ganancia corriente:" << str_ganancia_corriente;
    qDebug() << "ganancia_corriente:" << ganancia_corriente;

    // para simplificar el envio se le adiciona GEN_PTO_MEDIO a cada valor de tension a enviar
    uint16_t tension_punto1_aenviar;
    uint16_t tension_punto2_aenviar;
    uint16_t tension_punto3_aenviar;
    uint16_t tension_retencion_aenviar;

    tension_punto1_aenviar = (uint16_t) (tension_punto1 + GEN_PTO_MEDIO);
    tension_punto2_aenviar = (uint16_t) (tension_punto2 + GEN_PTO_MEDIO);
    tension_punto3_aenviar = (uint16_t) (tension_punto3 + GEN_PTO_MEDIO);
    tension_retencion_aenviar = (uint16_t) (tension_retencion + GEN_PTO_MEDIO);

    qDebug() << "tension_punto1_aenviar:" << tension_punto1_aenviar;
    qDebug() << "tension_punto2_aenviar:" << tension_punto2_aenviar;
    qDebug() << "tension_punto3_aenviar:" << tension_punto3_aenviar;
    qDebug() << "tension_retencion_aenviar:" << tension_retencion_aenviar;

    /*
     * el mensaje a enviar, segun protocolo v4, sera:
     * 0xA1;
     * 0x00;
     * 8 bits mas significativos de tension_punto1
     *  => ((tension_punto1 & 0x3FC0) >> 6);
     * 6 bits menos significativos de tension_punto1 y los 2 bits mas significativos de tension_punto2
     *  => ((tension_punto1 & 0x003F) << 2) | ((tension_punto2 & 0x3000) >> 12);
     * 8 bits menos significativos (parte alta) de tension_punto2
     *  => ((tension_punto2 & 0x0FF0) >> 4);
     * 4 bits menos significativos (parte baja) de tension_punto2 y los 4 bits mas significativos de tension_punto3
     *  => ((tension_punto2 & 0x000F) << 4) | ((tension_punto3 & 0x3C00) >> 10);
     * 8 bits menos significativos (parte alta) de tension_punto3
     *  => ((tension_punto3 & 0x03FC) >> 2);
     * 2 bits menos significativos (parte baja) de tension_punto3 y los 6 bits mas significativos de tension_retencion
     *  => ((tension_punto3 & 0x0003) << 6) | ((tension_retencion & 0xCF00) >> 8);
     * 8 bits menos significativos (parte alta) de tension_retencion
     *  => (tension_retencion & 0x00FF);
     * 8 bits de velocidad
     *  => velocidad;
     * 8 bits tiempo de retencion
     *  => tiempo_retencion;
     * 8 bits de ciclos
     *  => ciclos;
     *
    */
    //se enviara un INIT MEASUREMENT CYCLICAL
    buffer[0] = OC_INITMEASUREMENTCYCLICAL;
    buffer[1] = 0x00;
    buffer[2] = (uint8_t) ((tension_punto1_aenviar & 0x3FC0) >> 6);
    buffer[3] = (uint8_t) (((tension_punto1_aenviar & 0x003F) << 2) | ((tension_punto2_aenviar & 0x3000) >> 12));
    buffer[4] = (uint8_t) ((tension_punto2_aenviar & 0x0FF0) >> 4);
    buffer[5] = (uint8_t) (((tension_punto2_aenviar & 0x000F) << 4) | ((tension_punto3_aenviar & 0x3C00) >> 10));
    buffer[6] = (uint8_t) ((tension_punto3_aenviar & 0x03FC) >> 2);
    buffer[7] = (uint8_t) (((tension_punto3_aenviar & 0x0003) << 6) | ((tension_retencion_aenviar & 0xCF00) >> 8));
    buffer[8] = (uint8_t) (tension_retencion_aenviar & 0x00FF);
    buffer[9] = (uint8_t) (velocidad & 0x0FF);
    buffer[10] = (uint8_t) (tiempo_retencion & 0x0FF);
    buffer[11] = (uint8_t) (ciclos & 0x0FF);
    buffer[12] = (uint8_t) (ganancia_corriente & 0x0FF);

    qDebug() << "dato a enviar completo"
             << buffer[0] << buffer[1] << buffer[2] << buffer[3] << buffer[4] << buffer[5]
             << buffer[6] << buffer[7] << buffer[8] << buffer[9] << buffer[10] << buffer[11] << buffer[12];

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * BITS_EN_UN_BYTE, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * BITS_EN_UN_BYTE, &len, 1000);

    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado completo"
             << buffer[0] << buffer[1] << buffer[2] << buffer[3] << buffer[4] << buffer[5]
             << buffer[6] << buffer[7] << buffer[8] << buffer[9] << buffer[10] << buffer[11] << buffer[12];

    qDebug() << "dato enviado [0]" << buffer[0];

    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

    //Limpia el gráfico y lo inicializa
    MainWindow::limpiarGraficos();
    MainWindow::inicializarGraficos();

    //Se limpia el vector de valores con valores invalidos
    for(int i=0; i<CANT_VALORES; i++){
        valoresX[i] = -1;
        valoresY[i] = -1;
    }

    //Se activa la medicion en el Timer
    medicion_habilitada = 1;

    //Habilita abortar
    ui->Bt_Abortar->setEnabled(true);
}

void MainWindow::on_Bt_Abortar_clicked()
{
    uint8_t ciclos = 0;
    ciclos = ui->Num_CicCiclico->value();

    MainWindow::forzarAbortar();
    if (ciclos == 0){
        // TODO: hacer esto funcion, porque el codigo se repite en Timeout()
        qDebug() << "Envío de refresco al gráfico";
        qDebug() << clock() << "inicio refrescar valores";
        MainWindow::refrescarValores();
        qDebug() << clock() << "termino refrescar valores";
        //Se termina la medición
        qDebug() << "Termino la medicion";
        medicion_habilitada = 0;
        MainWindow::terminoMedicion();
        p_refresco = 0;
    }
}

void MainWindow::on_Bt_Exportar_clicked()
{
    qDebug() << "Exportar Medición";

    // Almacena en la carpeta mediciones los datos que se ven en pantalla en CSV
    MainWindow::exportarCSV();

    // Almacena una foto de la medición final

    // (opcional) Recibe la elección del nombre de los 2 archivos a guardar (imagen y datos en csv)

    // Notifica el correcto (o no) almacenado del archivo
    //QMessageBox::about(this,
    //                   "Potenciostato - UTN FRA",
    //                   "Proyecto Final: Potenciostato\nIntegrantes de grupo:\n    Arluna Gustavo\n    Gómez Caamaño Axel Lucas\n    Trinidad Hernán Matías\n\nFacultad Regional Avellaneda - Universidad Tecnológica Nacional");
    //QMessageBox::Information(this, "hola");
    QMessageBox::information(this,"Potenciostato","Archivo guardado satisfactoriamente");
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
    ui->Bt_IniciarCiclico->setEnabled(true);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);
    ui->Conectar_Bt->setEnabled(false);
    ui->Desconectar_Bt->setEnabled(true);

    libusb_claim_interface(dev_handle, 0);

    qDebug() << Dispositivo;
}

void MainWindow::help()
{
    qDebug() << "Ayuda";
    //link a documentacion https://doc.qt.io/qt-5/qmessagebox.html#about
    QMessageBox::about(this,
                       "Potenciostato - UTN FRA",
                       "Proyecto Final: Potenciostato\nIntegrantes de grupo:\n    Arluna Gustavo\n    Gómez Caamaño Axel Lucas\n    Trinidad Hernán Matías\n\nFacultad Regional Avellaneda - Universidad Tecnológica Nacional");
}

void MainWindow::abrirMedicion(){
    QString nom_archivo;
    bool archivo_valido = false;

    QFileDialog fd(this);
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setNameFilter(tr("Mediciones (*.csv)"));
    if (fd.exec()) {
        nom_archivo = fd.selectedFiles().constFirst();

        qDebug() << "archivo seleccionado: " << nom_archivo;
        QFile arch(nom_archivo);
        if ( arch.open(QIODevice::ReadOnly | QIODevice::Text) )
        {

            MainWindow::limpiarGraficos();
            MainWindow::resetearValores();

            MainWindow::inicializarGraficos();

            QTextStream in(&arch);
            while (!in.atEnd()) {
                QString linea = in.readLine();
                //qDebug() << linea;
                QStringList palabras = linea.split( "," );
                if (archivo_valido == true){
                    valoresX[p_refresco] = palabras[0].toFloat();
                    valoresY[p_refresco] = palabras[1].toFloat();
                    if (p_refresco >= (CANT_VALORES-1)){
                        p_refresco = 0;
                    }
                    else{
                        p_refresco++;
                    }
                }
                if (palabras[0].compare("Tension") == 0 && palabras[1].compare("Corriente") == 0){
                    archivo_valido = true;
                }
            }
            MainWindow::refrescarValores();
            qDebug() << clock() << "termino refrescar valores";
            MainWindow::autoCentrar();
        }
        arch.close();
    }
}

void MainWindow::resetearValores(){
    p_refresco = 0;
    p_refrescado = 0;
    for (int i = 0; i < CANT_VALORES; i++)
    {
        valoresX[i] = -1;
        valoresY[i] = -1;
    }
}

void MainWindow::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->customPlot->graph(i);
    QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
    }
  }
}


void MainWindow::mousePress(QMouseEvent* event)
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

    /*if (debugging == ENABLED){
        qDebug() << "x" << event->pos().x() << ", y: " << event->pos().y();
        qDebug() << "global" << ui->customPlot->mapToGlobal(event->pos());
        qDebug() << ui->customPlot->xAxis->range(); //49 a 546
        qDebug() << ui->customPlot->yAxis->range(); //14 a 341
    }*/

    //TODO: verificar que el click haya sido el boton izquierdo (y no el derecho)
    switch (estado_cursor){
    case SIN_SELECCIONAR:
        break;
    case SELECCIONAR_A:
        calcularCursor(event->pos().x(), event->pos().y(), CUR_A);
        graficarCursor(CUR_A);
        estado_cursor = SELECCIONAR_B;
        break;
    case SELECCIONAR_B:
        calcularCursor(event->pos().x(), event->pos().y(), CUR_B);
        graficarCursor(CUR_B);
        refrescarDeltas();
        estado_cursor = SIN_SELECCIONAR;
        break;
    default:
        break;
    }



    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::calcularCursor(int x, int y, char cursor)
{
    float medX, medY, medZ;
    float minRangeX, maxRangeX, minRangeY, maxRangeY;
    if (debugging == ENABLED){
        qDebug() << "x" << x << ", y: " << y; //49 a 546 en x; 14 a 341 en y;
        //qDebug() << "global" << ui->customPlot->mapToGlobal(pos());
        qDebug() << ui->customPlot->xAxis->range();
        qDebug() << ui->customPlot->yAxis->range();
    }
    minRangeX = ui->customPlot->xAxis->range().lower;
    maxRangeX = ui->customPlot->xAxis->range().upper;
    minRangeY = ui->customPlot->yAxis->range().lower;
    maxRangeY = ui->customPlot->yAxis->range().upper;
    if (debugging == ENABLED){
        //qDebug() << "minRangeX: " << minRangeX << ", maxRangeX" << maxRangeX;
        //qDebug() << "minRangeY: " << minRangeY << ", maxRangeY" << maxRangeY;
    }
    medX = x;
    medX = ((medX - POS_X_MINIMA)/(POS_X_MAXIMA - POS_X_MINIMA)*(maxRangeX-minRangeX))+minRangeX;
    medY = y;
    medY = -((-POS_Y_MAXIMA + medY)/(POS_Y_MAXIMA - POS_Y_MINIMA)*(maxRangeY-minRangeY))+minRangeY;

    if (cursor == CUR_A){
        a_med_x = medX;
        a_med_y = medY;
    }
    if (cursor == CUR_B){
        b_med_x = medX;
        b_med_y = medY;
        medZ = (b_med_x-a_med_x)/(b_med_y-a_med_y);
        if (medZ < 0){
            medZ = -medZ;
        }
        if (medZ >= 0){
            //medZ = medZ;
        }
        med_z = medZ;
    }

    if (debugging == ENABLED){
        qDebug() << "med_x" << medX;
        qDebug() << "med_y" << medY;
        qDebug() << "med_z" << medZ;
    }

}

void MainWindow::graficarCursor(char cursor){
    //float x, y;
    QVector<double> x(2), y(2);
    QVector<double> x1_horiz(2), y1_horiz(2), x1_vert(2), y1_vert(2);
    QVector<double> x2_horiz(2), y2_horiz(2), x2_vert(2), y2_vert(2);
    switch(cursor){
    case CUR_A: //con un click, que aparezca el punto seleccionado
        x[0] = a_med_x;
        y[0] = a_med_y;
        x[1] = a_med_x;
        y[1] = a_med_y;
        x1_horiz[0] = -9999;
        x1_horiz[1] = +9999;
        y1_horiz[0] = a_med_y;
        y1_horiz[1] = a_med_y;
        x1_vert[0] = a_med_x;
        x1_vert[1] = a_med_x;
        y1_vert[0] = -9999;
        y1_vert[1] = +9999;
        x2_horiz[0] = -9999;
        x2_horiz[1] = +9999;
        y2_horiz[0] = a_med_y;
        y2_horiz[1] = a_med_y;
        x2_vert[0] = a_med_x;
        x2_vert[1] = a_med_x;
        y2_vert[0] = -9999;
        y2_vert[1] = +9999;
        break;
    case CUR_B: //con el segundo click, que aparezca la linea completa
        x[0] = a_med_x;
        y[0] = a_med_y;
        x[1] = b_med_x;
        y[1] = b_med_y;
        x1_horiz[0] = -9999;
        x1_horiz[1] = +9999;
        y1_horiz[0] = a_med_y;
        y1_horiz[1] = a_med_y;
        x1_vert[0] = a_med_x;
        x1_vert[1] = a_med_x;
        y1_vert[0] = -9999;
        y1_vert[1] = +9999;
        x2_horiz[0] = -9999;
        x2_horiz[1] = +9999;
        y2_horiz[0] = b_med_y;
        y2_horiz[1] = b_med_y;
        x2_vert[0] = b_med_x;
        x2_vert[1] = b_med_x;
        y2_vert[0] = -9999;
        y2_vert[1] = +9999;
        break;
    }
    //ui->customPlot->graph(1)->setData(x, y, false);
    ui->customPlot->graph(2)->setData(x1_horiz, y1_horiz, false); //se grafica linea vertical
    ui->customPlot->graph(3)->setData(x1_vert, y1_vert, false); //se grafica linea horizontal
    ui->customPlot->graph(4)->setData(x2_horiz, y2_horiz, false); //se grafica linea vertical
    ui->customPlot->graph(5)->setData(x2_vert, y2_vert, false); //se grafica linea horizontal
    ui->customPlot->replot();
}

void MainWindow::refrescarDeltas(){
    ui->Num_deltaX->setText(QString::number(b_med_x-a_med_x, 'f', 2));
    ui->Num_deltaY->setText(QString::number(b_med_y-a_med_y, 'f', 2));
    ui->Num_deltaZ->setText(QString::number(med_z, 'f', 2));
    ui->Num_deltaXa->setText(QString::number(a_med_x, 'f', 2));
    ui->Num_deltaYa->setText(QString::number(a_med_y, 'f', 2));
    ui->Num_deltaXb->setText(QString::number(b_med_x, 'f', 2));
    ui->Num_deltaYb->setText(QString::number(b_med_y, 'f', 2));
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::menuContextual(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    //qDebug() << "x: " << pos << ", y: " << pos;

    if (ui->customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
        menu->addAction("Cursor X", this, SLOT(habilitarCursor()))->setData((int)(CUR_A));
        menu->addAction("Cursor Y", this, SLOT(habilitarCursor()))->setData((int)(CUR_B));
    } else  // general context menu on graphs requested
    {
        menu->addAction("Cursor X", this, SLOT(habilitarCursor()))->setData((int)(CUR_A));
        menu->addAction("Cursor Y", this, SLOT(habilitarCursor()))->setData((int)(CUR_B));
    }

    menu->popup(ui->customPlot->mapToGlobal(pos));
}

void MainWindow::habilitarCursor(){
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
      bool ok;
      int dataInt = contextAction->data().toInt(&ok);
      if (debugging == ENABLED)
        qDebug() << "Cursor a cambiar" << dataInt;
      if (ok)
      {
          if (dataInt == CUR_A){
              //ui->customPlot->setInteractions(0x0);
              //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
              //                                QCP::iSelectLegend | QCP::iSelectPlottables);
              //qDebug() << dataInt;
          }
          if (dataInt == CUR_B){
              //qDebug() << dataInt;
          }
        //ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
        //ui->customPlot->replot();
      }
    }
}

void MainWindow::on_Bt_AutoCentrar_clicked()
{
    MainWindow::autoCentrar();
}


void MainWindow::on_Bt_Cursores_clicked()
{
    if (estado_cursor == SIN_SELECCIONAR)
        estado_cursor = SELECCIONAR_A;

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

    unsigned char buffer[LARGO_MENSAJE_SALIDA] = {0x0};
    unsigned char recv_data[LARGO_MENSAJE_ENTRADA] = {0x0};
    int len;
    int send_ret, recv_ret;


    //se enviara un ABORT MEASUREMENT
    buffer[0] = OC_ABORTMEASUREMENT;

    send_ret = libusb_interrupt_transfer(dev_handle, 0x01, buffer, (sizeof(buffer)) * BITS_EN_UN_BYTE, &len, 1000);
    recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * BITS_EN_UN_BYTE, &len, 1000);
    //int recv_ret = libusb_interrupt_transfer(dev_handle, 0x81, recv_data, (sizeof(recv_data)) * 64, &len, 1000);

    qDebug() << "codigo envio" << send_ret;
    qDebug() << "dato enviado" << buffer[0];
    qDebug() << "codigo recepcion" << recv_ret;
    qDebug() << "dato recibido[0]" << recv_data[0];

}

void MainWindow::on_Desconectar_Bt_clicked()
{
    MainWindow::desconectarUSB();

    medicion_habilitada = 0;

    //Habilita la conexión
    ui->Conectar_Bt->setEnabled(true);
    ui->Bt_IniciarCiclico->setEnabled(false);
    ui->Bt_Abortar->setEnabled(false);
    ui->Bt_Exportar->setEnabled(false);
    ui->Desconectar_Bt->setEnabled(false);

}

void MainWindow::exportarCSV()
{
    QString nom_archivo;
    nom_archivo = QString("med_%1.csv").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd-hh_mm_ss"));
    QFile arch(nom_archivo);
    if ( arch.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &arch );
        stream << "Tension,Corriente" << endl;
        for (int c=0; (c < CANT_VALORES) && ((valoresX[c] != -1 && valoresY[c] != -1)); c++ )
            stream << valoresX[c] << "," << valoresY[c] << endl;
    }
    arch.close();

}


/* -------------------- FUNCIONES DEPRECADAS -------------------- */
// CODIGO DE EJEMPLO PARA LUEGO.......
//QString Buff;
//Buff = ui->TBox->toPlainText();
//Datos = Buff.toInt();
//    QMessageBox::warning(this,"Error","El valor ingresado es inválido",QMessageBox::Retry);
//Datos = 0;
//Buff=QString::number(Datos);
//ui->TBox_2->setText(Buff);

/*
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
        //ui->statusBar->showMessage(
        //    QString("%1 FPS, Total Data points: %2")
        //        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
        //        .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
        //        , 0);
        qDebug() << QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size());
        lastFpsKey = key;
        frameCount = 0;
    }
}*/
