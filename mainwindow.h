#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtNetwork>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void commandWrite(QString command);


private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_vertSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_vertHorzSli_valueChanged(int value);

    void on_shiftVertSli_valueChanged(int value);

    void on_shiftHorzSli_valueChanged(int value);

    void on_DGR_currentTextChanged(const QString &arg1);

    void on_blankUpSli_valueChanged(int value);

    void on_noiseRed_currentTextChanged(const QString &arg1);

    void on_eth_clicked();

    void on_host_textChanged(const QString &arg1);

    void on_eport_textChanged(const QString &arg1);

    void on_com_clicked();

    void on_port_textChanged(const QString &arg1);

    void on_TVsystem_currentTextChanged(const QString &arg1);

    void on_dayView_currentTextChanged(const QString &arg1);

    void on_sharpSli_valueChanged(int value);

    void on_clockSlider_valueChanged(int value);

    void on_keySlider_valueChanged(int value);

    void on_DVIE_currentTextChanged(const QString &arg1);

    void on_clear_clicked();

    void on_setName_textChanged(const QString &arg1);

    void on_aspectVideo_currentTextChanged(const QString &arg1);

    void on_aspectRGB_currentTextChanged(const QString &arg1);

    void on_aspectVi_currentTextChanged(const QString &arg1);

    void on_syRGB1_currentTextChanged(const QString &arg1);

    void on_sysDVIA_currentTextChanged(const QString &arg1);

    void on_sysDVID_currentTextChanged(const QString &arg1);

    void on_sysHDMI_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
