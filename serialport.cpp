#include "serialport.h"
#include <QDebug>
#include <cstring>

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
    , m_Port(new QSerialPort)
{
    m_Port->setPortName("COM3");
    m_Port->setBaudRate(QSerialPort::Baud9600);
    m_Port->setDataBits(QSerialPort::Data8);
    m_Port->setParity(QSerialPort::NoParity);
    m_Port->setStopBits(QSerialPort::OneStop);
    m_Port->setFlowControl(QSerialPort::NoFlowControl);

    connect(m_Port, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
    connect(m_Port, SIGNAL(FetchPacketReady()), this, SLOT(FetchPacket()));

}


void SerialPort::FetchPacket()
{
    if(m_PacketQueue.constFirst() != PC_RECEIVE_HEADER_HIGH_BYTE){
        /***  Something TODO  ***/
        return;
    }

    packet.SetHeader(m_PacketQueue.dequeue(),m_PacketQueue.dequeue());
    packet.SetAddressOfReceiver(m_PacketQueue.dequeue());
    packet.SetCommand(m_PacketQueue.dequeue());
    packet.SetData(m_PacketQueue.dequeue(), m_PacketQueue.dequeue(), m_PacketQueue.dequeue(), m_PacketQueue.dequeue());
    packet.SetCheckByteSum();

    /***  Something TODO  ***/
}


void SerialPort::ReceiveData()
{
    qDebug() << "receive";

    QByteArray readData;
    readData = m_Port->readAll();
    quint8 packet[readData.size()]; // ??
    std::memcpy(packet, (quint8 *)readData.data(), sizeof(packet));

    for (int i=0;i<readData.size();i++){
        m_PacketQueue.enqueue(packet[i]);
    }

    if(m_PacketQueue.size() >= 9){
        emit FetchPacketReady();
    }

    qDebug() << QString::fromStdString(readData.toStdString());
}


void SerialPort::SendData(UartPacket packet)
{
    qDebug() << "send";
    CheckSerialPort();

    QByteArray sendData = packet.GetPacket();

    m_Port->write(sendData);
    m_Port->close();
}


void SerialPort::CheckSerialPort()
{
    if (!m_Port->open(QIODevice::ReadWrite)){
        qDebug() << "Serial Port Open Error!";
    } else {
        qDebug() << "connect!";
    }
}
