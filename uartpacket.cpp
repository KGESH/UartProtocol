#include "uartpacket.h"


void UartPacket::SetPacketFromString(QString packet)
{
    m_packet = packet.toUtf8();
}


void UartPacket::SetHeader(const quint8& pre_h, const quint8& pre_l)
{
    this->m_Pre_h = pre_h;
    this->m_Pre_l = pre_l;
}


void UartPacket::SetAddressOfReceiver(const quint8& address)
{
    this->m_Add = address;
}


void UartPacket::SetCommand(const quint8& command)
{
    this->m_Code = command;
}


void UartPacket::SetData(const quint8& dataH1, const quint8& data2, const quint8& data3, const quint8& dataL4)
{
    this->m_DataH1 = dataH1;
    this->m_Data2 = data2;
    this->m_Data3 = data3;
    this->m_DataL4 = dataL4;
}


//void UartPacket::SetData(quint32 data)
//{
//    /***  데이터 비트 나누기  ***//
//}


void UartPacket::SetCheckByteSum()
{
    this->m_Sum = m_Pre_h + m_Pre_l + m_Add + m_Code
            + m_DataH1 + m_Data2 + m_Data3 + m_DataL4;  // ??
}


QByteArray UartPacket::GetPacket() const
{
    return m_packet;
}


quint8 UartPacket::GetHeaderHighByte() const
{
    return m_Pre_h;
}


quint8 UartPacket::GetHeaderLowByte() const
{
    return m_Pre_l;
}


quint8 UartPacket::GetRobotAddress() const
{
    return m_Add;
}


quint8 UartPacket::GetCommnad() const
{
    return m_Code;
}


quint8 UartPacket::GetDataH1() const
{
    return m_DataH1;
}


quint8 UartPacket::GetData2() const
{
    return m_Data2;
}


quint8 UartPacket::GetData3() const
{
    return m_Data3;
}


quint8 UartPacket::GetDataL4() const
{
    return m_DataL4;
}


quint8 UartPacket::GetByteSum() const
{
    return m_Sum;
}
