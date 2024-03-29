#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_SerialPort(new SerialPort(this))
{
    ui->setupUi(this);
    connect(ui->ui_motor_control_button, SIGNAL(released()), this, SLOT(OnClickedControlButton()));
    connect(ui->ui_motor_stop_button, SIGNAL(released()), this, SLOT(OnClickedStopButton()));
    connect(ui->ui_serial_port_connect_button, SIGNAL(released()), this, SLOT(OnClickedSerialPortConnectButton()));

    m_SerialPort->Scan_Serial_Port(*ui->ui_serial_port_combo_box);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OnClickedSerialPortConnectButton()
{
    m_SerialPort->SetSerialPortName(ui->ui_serial_port_combo_box->currentText());

    if(!m_SerialPort->GetPort()->open(QIODevice::ReadWrite)){
        qDebug() << "\n Serial port open Error \n";
    } else {
        qDebug() << "connect";
    }
}


void MainWindow::OnClickedControlButton()
{
    QString text = ui->ui_motor_speed_control_edit_box->text();
    UartPacket packet;
    packet.SetPacketFromString(text);
    m_SerialPort->SendData(packet);
}


void MainWindow::OnClickedStopButton()
{
    UartPacket packet;
    packet.SetHeader(PC_SEND_HEADER_HIGH_BYTE, PC_SEND_HEADER_LOW_BYTE);
    packet.SetAddressOfReceiver(PC_SEND_ROBOT_CONTROL_ADDRESS_TESTVERSION);
    packet.SetCommand(PC_SEND_COMMAND_PC_STOP);
    packet.SetData(0x00,0x00,0x00,0x0D);    // ??
    packet.SetCheckByteSum();
    m_SerialPort->SendData(packet);
}
