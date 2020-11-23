#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uartpacket.h"
#include "serialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UartPacket;
class SerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnClickedControlButton();
    void OnClickedStopButton();
    void OnClickedSerialPortConnectButton();

private:
    Ui::MainWindow *ui;
    SerialPort *m_SerialPort;
};
#endif // MAINWINDOW_H
