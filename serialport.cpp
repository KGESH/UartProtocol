#include "serialport.h"
#include <QDebug>
#include <cstring>

SerialPort::SerialPort(QObject *parent, QString portName)
    : QObject(parent)
    , m_Port(new QSerialPort)
    , m_PortName(portName)
{
    m_Port->setPortName(portName);
    m_Port->setBaudRate(QSerialPort::Baud9600);
    m_Port->setDataBits(QSerialPort::Data8);
    m_Port->setParity(QSerialPort::NoParity);
    m_Port->setStopBits(QSerialPort::OneStop);
    m_Port->setFlowControl(QSerialPort::NoFlowControl);

    connect(m_Port, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
    connect(m_Port, SIGNAL(FetchPacketReady()), this, SLOT(FetchPacket()));

}


SerialPort::~SerialPort()
{
    m_Port->close();
    delete m_Port;
}


QSerialPort* SerialPort::GetPort() const
{
    return m_Port;
}


void SerialPort::SetSerialPortName(QString portName)
{
    m_Port->setPortName(portName);
}


void SerialPort::FetchPacket()
{
    if(m_PacketQueue.constFirst() != PC_RECEIVE_HEADER_HIGH_BYTE){
        /***  Exception Something TODO  ***/
        return;
    }

    packet.SetHeader(m_PacketQueue.dequeue(),m_PacketQueue.dequeue());
    packet.SetAddressOfReceiver(m_PacketQueue.dequeue());
    packet.SetCommand(m_PacketQueue.dequeue());
    packet.SetData(m_PacketQueue.dequeue(), m_PacketQueue.dequeue(), m_PacketQueue.dequeue(), m_PacketQueue.dequeue());
    packet.SetCheckByteSum();

    qDebug() << "receive Packet : " << packet.GetHeaderHighByte() << packet.GetHeaderLowByte() << packet.GetRobotAddress()
             << packet.GetCommnad() << packet.GetDataH1() << packet.GetData2() << packet.GetData3() << packet.GetDataL4()
             << packet.GetByteSum();

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

    qDebug() << "from stdString " << QString::fromStdString(readData.toStdString());
}


void SerialPort::SendData(UartPacket packet)
{
    qDebug() << "send";

    QByteArray sendData = packet.GetPacket();

    m_Port->write(sendData);
    //m_Port->close();
}


void SerialPort::Scan_Serial_Port(QComboBox& ui_Serial_ComboBox)
{
        //열린 시리얼 포트 검색
        HKEY hKey; //레지스트리에 접근하는 변수
        RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

        TCHAR szData[20], szName[100];
        DWORD index = 0, dwSize=100, dwSize2 = 20, dwType = REG_SZ;
        memset(szData, 0x00, sizeof(szData));  //초기화
        memset(szName, 0x00, sizeof(szName));

        while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL)){
           index++;

           RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
           QString tem = TCHARToString(szData);

           ui_Serial_ComboBox.addItem(tem);
           memset(szData, 0x00, sizeof(szData));  //초기화
           memset(szName, 0x00, sizeof(szName));
           dwSize = 100;
           dwSize2 = 20;
       }
       RegCloseKey(hKey);
}


QString SerialPort::TCHARToString(const TCHAR* ptsz){
 int len = wcslen((wchar_t*)ptsz);
 char* psz = new char[2*len + 1];
 wcstombs(psz, (wchar_t*)ptsz, 2*len + 1);
 QString s = psz;
 delete [] psz;
 return s;
}
