#ifndef SERIALPORTREADERASYNC_H
#define SERIALPORTREADERASYNC_H

#include <QByteArray>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QQueue>

#include "Packetizer.h"
#include "MsgPack.h"
#include "MsgPack_types.h"

#define PACKETIZER_USE_CRC_AS_DEFAULT
#define PACKETIZER_USE_INDEX_AS_DEFAULT

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QSerialPort *serialPort, QObject *parent = nullptr);
    void turnOnDebugOutput();
    void turnOffDebugOutput();
   ~SerialPortReader();

    int get_number_of_CRC_errors();

private slots:
    void handleReadyRead();
    void handleParseQueue();
    void handleParseCommands();
    void handleError(QSerialPort::SerialPortError error);

private:

    bool debugOutput = false;

    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;

    QTimer command_parse_timer;

    QByteArray raw_serial_queue;
    QQueue<Packetizer::Packet> decoded_packet_queue;

    int CRC_ERRORS = 0;
    bool USE_CRC = true;
    bool USE_INDEX = true;

signals:
    void commandRecieved(Packetizer::Packet _decoded);   //Emits the command, whatever type, and the corresponding index of the command type.
    void raw_RX_Packet_log_SIGNAL(QByteArray rawpack);
    void updatedReadQueueSize(int queue_size);               //Emits the current serial readqueue size. Good for logging, to see if and when there might be more data than the program can handle.
};

#endif // SERIALPORTREADERASYNC_H
