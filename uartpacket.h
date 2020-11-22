#ifndef UARTPACKET_H
#define UARTPACKET_H
#include <QObject>
#include <qglobal.h>

/***  PC SEND PROTOCOL  ***/
const quint8 PC_SEND_HEADER_HIGH_BYTE    = 0x44;      //  'D'
const quint8 PC_SEND_HEADER_LOW_BYTE     = 0x53;      //  'S'
const quint8 PC_SEND_ROBOT_CONTROL_ADDRESS_BROADCAST = 0x00;
const quint8 PC_SEND_ROBOT_CONTROL_ADDRESS_TESTVERSION = 0x01;
/***  Command List  ***
 ***  0x01 ~ 0x8F   ***
 ***                ***/
const quint8 PC_SEND_COMMAND_MOTOR_STOP = 0x02;
const quint8 PC_SEND_COMMAND_ROBOT_RESET = 0x06;
const quint8 PC_SEND_COMMAND_PC_STOP = 0x22;    // ??
const quint8 PC_SEND_COMMAND_INTERVAL_SEND = 0x24;
//const quint8 PC_SEND_COMMAND_0x26 = 0x26;    //??
const quint8 PC_SEND_COMMAND_MOTOR_CONTROL = 0x62;


/***  PC RECEIVE PROTOCOL  ***/
const quint8 PC_RECEIVE_HEADER_HIGH_BYTE = 0x53;      //  'S'
const quint8 PC_RECEIVE_HEADER_LOW_BYTE  = 0x44;      //  'D'
const quint8 PC_RECEIVE_ROBOT_CONTROL_ADDRESS = 0x01;
/***  Command List  ***
 ***  0x01 ~ 0xFF   ***
 ***                ***/
const quint8 PC_RECEIVE_COMMAND_PERIODIC_RESPONSE = 0xB3;
const quint8 PC_RECEIVE_COMMAND_INSTRUCTION_RESPONSE = 0xB5;
const quint8 PC_RECEIVE_COMMAND_EMERGENCY_RESPONSE = 0xE1;


class UartPacket{

private:
    quint8 m_Pre_h = 0;     //  unsigned char : 1byte
    quint8 m_Pre_l = 0;
    quint8 m_Add = 0;
    quint8 m_Code = 0;
    //quint32 m_Data = 0;
    quint8 m_DataH1 = 0;
    quint8 m_Data2 = 0;
    quint8 m_Data3 = 0;
    quint8 m_DataL4 = 0;
    quint8 m_Sum = 0;
    QByteArray m_packet;


public:
    void SetHeader(const quint8& pre_h, const quint8& pre_l);
    void SetAddressOfReceiver(const quint8& address);
    void SetCommand(const quint8& command);
    void SetData(const quint8& dataH1, const quint8& data2, const quint8& data3, const quint8& dataL4);
    //void SetData(quint32 data);
    void SetCheckByteSum();
    void SetPacketFromString(QString packet);

    QByteArray GetPacket() const;
    quint8 GetHeaderHighByte() const;
    quint8 GetHeaderLowByte() const;
    quint8 GetRobotAddress() const;
    quint8 GetCommnad() const;
    quint8 GetDataH1() const;
    quint8 GetData2() const;
    quint8 GetData3() const;
    quint8 GetDataL4() const;
    quint8 GetByteSum() const;

};

#endif // UARTPACKET_H
