#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->setProxy(QNetworkProxy::NoProxy);

    serial = new QSerialPort;
    serial->setPortName("COM1");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::WriteOnly);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (serial) {
        serial->close();
        delete serial;
    }
    if (socket) {
       socket->close();
       delete socket;
    }
}

void MainWindow::commandWrite(QString command) {

    QByteArray arr;
    arr.append("\x02");
    arr.append(command.toUtf8());
    arr.append("\x03");

    if (ui->eth->isChecked()) {
        socket->write(arr);
    }
    else if (ui->com->isChecked()) {
        serial->write(arr);
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "INTERNAL"){
        commandWrite("ADZZ;OZT:0");
    }
    else if (arg1 == "FULL"){
        commandWrite("ADZZ;OZT:1");
    }
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1 == "OFF"){
        commandWrite("ADZZ;OZS:0");
    }
    else if (arg1 == "ON"){
        commandWrite("ADZZ;OZS:1");
    }
}

void MainWindow::on_vertSlider_valueChanged(int value)
{
    commandWrite("ADZZ;OZV:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    commandWrite("ADZZ;OZH:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_vertHorzSli_valueChanged(int value)
{
    commandWrite("ADZZ;OZO:"+QString::number(value).rightJustified(3, '0'));
}

void MainWindow::on_shiftVertSli_valueChanged(int value)
{
    commandWrite("ADZZ;VTV:"+QString::number(value).rightJustified(4, '0'));
}


void MainWindow::on_shiftHorzSli_valueChanged(int value)
{
    commandWrite("ADZZ;VTH:"+QString::number(value).rightJustified(4, '0'));
}


void MainWindow::on_DGR_currentTextChanged(const QString &arg1)
{
    if(arg1 == "AUTO"){
        commandWrite("ADZZ;OPD:0");
    }
    else if (arg1 == "OFF"){
        commandWrite("ADZZ;OPD:1");
    }
}


void MainWindow::on_blankUpSli_valueChanged(int value)

{
    commandWrite("ADZZ;DBU:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_noiseRed_currentTextChanged(const QString &arg1)
{
    if(arg1 == "OFF"){
        commandWrite("ADZZ;VNS:0");
    }
    else if (arg1 == "ON"){
        commandWrite("ADZZ;VNS:1");
    }
}


void MainWindow::on_eth_clicked()
{
    serial->close();
    socket->connectToHost(ui->host->text(), ui->eport->text().toInt());
}

void MainWindow::on_host_textChanged(const QString &arg1)
{
    socket->close();
    socket->connectToHost(ui->host->text(), ui->eport->text().toInt());
}


void MainWindow::on_eport_textChanged(const QString &arg1)
{
    socket->close();
    QMessageBox::warning(this, "fds", ui->eport->text());
    socket->connectToHost(ui->host->text(), ui->eport->text().toInt());
}


void MainWindow::on_com_clicked()
{
    socket->close();
    serial->setPortName("COM" + ui->port->text());
    serial->open(QIODevice::WriteOnly);

}


void MainWindow::on_port_textChanged(const QString &arg1)
{
    serial->close();
    serial->setPortName("COM" + ui->port->text());
    serial->open(QIODevice::WriteOnly);
}


void MainWindow::on_TVsystem_currentTextChanged(const QString &arg1)
{
    if(arg1 == "AUTO"){
        commandWrite("ADZZ;VSG:AT1");
    }
    else if (arg1 == "NTSC"){
        commandWrite("ADZZ;VNS:NTS");
    }
    else if (arg1 == "NTSC4.43"){
        commandWrite("ADZZ;VNS:N44");
    }
    else if (arg1 == "PAL"){
        commandWrite("ADZZ;VNS:PAL");
    }
    else if (arg1 == "PAL-M"){
        commandWrite("ADZZ;VNS:PAM");
    }
    else if (arg1 == "PAL-N"){
        commandWrite("ADZZ;VNS:PAN");
    }
    else if (arg1 == "SECAM"){
        commandWrite("ADZZ;VNS:SEC");
    }
    else if (arg1 == "PAL60"){
        commandWrite("ADZZ;VNS:P60");
    }
}


void MainWindow::on_dayView_currentTextChanged(const QString &arg1)
{
    if(arg1 == "OFF"){
        commandWrite("ADZZ;VXX:DLVI0=+00000");
    }
    else if (arg1 == "AUTO"){
        commandWrite("ADZZ;VXX:DLVI0=+00001");
    }
    else if (arg1 == "1"){
        commandWrite("ADZZ;VXX:DLVI0=+00003");
    }
    else if (arg1 == "2"){
        commandWrite("ADZZ;VXX:DLVI0=+00004");
    }
    else if (arg1 == "3"){
        commandWrite("ADZZ;VXX:DLVI0=+00005");
    }
}


void MainWindow::on_sharpSli_valueChanged(int value)
{
    commandWrite("ADZZ;VSR:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_clockSlider_valueChanged(int value)
{
    commandWrite("ADZZ;VCP:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_keySlider_valueChanged(int value)
{
    commandWrite("ADZZ;OKS:"+QString::number(value).rightJustified(3, '0'));
}


void MainWindow::on_DVIE_currentTextChanged(const QString &arg1)
{
    if(arg1 == "AUTO"){
        commandWrite("ADZZ;VXX:DEQI0=+00000");
    }
    else if (arg1 == "LOW"){
        commandWrite("ADZZ;VXX:DEQI0=+00001");
    }
    else if (arg1 == "MID"){
        commandWrite("ADZZ;VXX:DEQI0=+00002");
    }
    else if (arg1 == "HIGH"){
        commandWrite("ADZZ;VXX:DEQI0=+00003");
    }

}


void MainWindow::on_clear_clicked()
{
    commandWrite("ADZZ;VXX:NCLI1=+00000");
}


void MainWindow::on_setName_textChanged(const QString &arg1)
{
    commandWrite("ADZZ;VXX:NCGS1="+arg1);
}


void MainWindow::on_aspectVideo_currentTextChanged(const QString &arg1)
{
    if(arg1 == "NORMAL"){
        commandWrite("ADZZ;VSE:00");
    }
    else if (arg1 == "NATIVE"){
        commandWrite("ADZZ;VSE:05");
    }
    else if (arg1 == "WIDE"){
        commandWrite("ADZZ;VSE:02");
    }
    else if (arg1 == "4:3"){
        commandWrite("ADZZ;VSE:01");
    }
    else if(arg1 == "H FIT"){
        commandWrite("ADZZ;VSE:09");
    }
    else if (arg1 == "V FIT"){
        commandWrite("ADZZ;VSE:10");
    }
    else if (arg1 == "FULL"){
        commandWrite("ADZZ;VSE:06");
    }
}


void MainWindow::on_aspectRGB_currentTextChanged(const QString &arg1)
{
    if(arg1 == "AUTO"){
        commandWrite("ADZZ;VSE:00");
    }
    else if (arg1 == "NATIVE"){
        commandWrite("ADZZ;VSE:05");
    }
    else if (arg1 == "WIDE"){
        commandWrite("ADZZ;VSE:02");
    }
    else if (arg1 == "4:3"){
        commandWrite("ADZZ;VSE:01");
    }
    else if(arg1 == "H FIT"){
        commandWrite("ADZZ;VSE:09");
    }
    else if (arg1 == "V FIT"){
        commandWrite("ADZZ;VSE:10");
    }
    else if (arg1 == "FULL"){
        commandWrite("ADZZ;VSE:06");
    }
}


void MainWindow::on_aspectVi_currentTextChanged(const QString &arg1)
{
    if (arg1 == "NATIVE"){
        commandWrite("ADZZ;VSE:05");
    }
    else if (arg1 == "WIDE"){
        commandWrite("ADZZ;VSE:02");
    }
    else if (arg1 == "4:3"){
        commandWrite("ADZZ;VSE:01");
    }
    else if(arg1 == "H FIT"){
        commandWrite("ADZZ;VSE:09");
    }
    else if (arg1 == "V FIT"){
        commandWrite("ADZZ;VSE:10");
    }
    else if (arg1 == "FULL"){
        commandWrite("ADZZ;VSE:06");
    }
}


void MainWindow::on_syRGB1_currentTextChanged(const QString &arg1)
{
    if (arg1 == "RGB"){
        commandWrite("ADZZ;ORF:0");
    }
    else if (arg1 == "YPBPR"){
        commandWrite("ADZZ;ORF:1");
    }
    else if (arg1 == "YCBCR"){
        commandWrite("ADZZ;ORF:1");
    }
    else if (arg1 == "VGA60"){
        commandWrite("ADZZ;ORF:0");
    }
    else if(arg1 == "480p"){
        commandWrite("ADZZ;ORF:1");
    }
    else if (arg1 == "480pRGB"){
        commandWrite("ADZZ;ORF:3");
    }
}


void MainWindow::on_sysDVIA_currentTextChanged(const QString &arg1)
{
    if (arg1 == "RGB"){
        commandWrite("ADZZ;ORF:0");
    }
    else if (arg1 == "YPBPR"){
        commandWrite("ADZZ;ORF:1");
    }
    else if (arg1 == "YCBCR"){
        commandWrite("ADZZ;ORF:1");
    }
}


void MainWindow::on_sysDVID_currentTextChanged(const QString &arg1)
{
    if (arg1 == "RGB"){
        commandWrite("ADZZ;ORF:0");
    }
    else if (arg1 == "YCBCR444"){
        commandWrite("ADZZ;ORF:4");
    }
    else if (arg1 == "YCBCR422"){
        commandWrite("ADZZ;ORF:5");
    }
}


void MainWindow::on_sysHDMI_currentTextChanged(const QString &arg1)
{
    if (arg1 == "AUTO"){
        commandWrite("ADZZ;ORF:2");
    }
    else if (arg1 == "RGB"){
        commandWrite("ADZZ;ORF:0");
    }
    else if (arg1 == "YCBCR444"){
        commandWrite("ADZZ;ORF:4");
    }
    else if (arg1 == "YCBCR422"){
        commandWrite("ADZZ;ORF:5");
    }
}

