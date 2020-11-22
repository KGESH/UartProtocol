#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QQueue>
#include "uartpacket.h"

class UartPacket;
class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);

    void SendData(UartPacket packet);

signals:
    void FetchPacketReady();

private slots:
    void ReceiveData();


private:
    void FetchPacket();
    void CheckSerialPort();
    QSerialPort *m_Port;
    QQueue<quint8> m_PacketQueue;
    UartPacket packet;
};

#endif // SERIALPORT_H
