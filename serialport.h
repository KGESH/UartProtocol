#ifndef SERIALPORT_H
#define SERIALPORT_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <windows.h>
#else

#endif

#include <QObject>
#include <QSerialPort>
#include <QQueue>
#include "uartpacket.h"
#include <QAction>
#include <QComboBox>

class UartPacket;
class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr, QString portName = "COM3");
    ~SerialPort();
    void Scan_Serial_Port(QComboBox& ui_Serial_ComboBox);
    void SendData(UartPacket packet);
    void SetSerialPortName(QString portName);
    QSerialPort* GetPort() const;

signals:
    void FetchPacketReady();

private slots:
    void ReceiveData();


private:
    void FetchPacket();
    void CheckSerialPort();
    QString TCHARToString(const TCHAR* ptsz);
    QSerialPort *m_Port;
    QQueue<quint8> m_PacketQueue;
    UartPacket packet;

    QString m_PortName;
};

#endif // SERIALPORT_H
