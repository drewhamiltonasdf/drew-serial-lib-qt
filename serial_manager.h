#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialportreader-async.h"
#include "serialportwriter-async.h"
#include "mcu-vendor-id-table.h"
#include <QDebug>
#include <QObject>
#include <DeviceSelector.h>
#include <QElapsedTimer>

class serial_manager : public QObject
{
    Q_OBJECT

    QSerialPort *serialPort;

    SerialPortReader *MCU_reader = nullptr;
    SerialPortWriter *MCU_writer = nullptr;

    int update_rate_millis;     // Update rate for serialParsing routine

    QList<parent_MSG_class*> registered_reader_class_pointers;
    QList<parent_MSG_class*> registered_writer_class_pointers;

    QTimer* send_command_timer;


public:
    serial_manager(QString _vendor_id, int _update_rate_millis);

    ~serial_manager();

    void init();

    void register_new_reader_class(parent_MSG_class *thing);
    void register_new_writer_class(parent_MSG_class *thing);

    void turnOnDebugOutput();
    void turnOffDebugOutput();

    int get_number_of_CRC_errors();


    QString baudString;
    QString COM_port;
    QString device_serial_number;
    QString vendor_id;
    QString product_id;

    // For averaging RX/TX speeds:
    int RX_array_iter = 0;
    int TX_array_iter = 0;
    float RX_Hz_array[25];
    float TX_Hz_array[25];
    float RX_Hz_average = 666;
    float TX_Hz_average = 666;
    QElapsedTimer elapsed_timer_RX;
    QElapsedTimer elapsed_timer_TX;


    void calculate_and_emit_average_RX_hz();
    void calculate_and_emit_average_TX_hz();

private:

    bool debugOutput = false;
    int CRC_ERRORS = 666;
    template <typename T>
    void decode(T *target_thing, Packetizer::Packet *_decoded);

    QString newSerialPortName;  //this is used by a slot if there is a device conflict
    void complete_serial_connection(QString serialPortName);

public slots:
    void handleResults(Packetizer::Packet _decoded);
    void sendCommands();
    void device_conflict_resolved();
    void update_port_SLOT(QString text);
    void handle_RX_raw_logging(QByteArray rawpack);
    void handle_updatedReadQueueSize(int read_queue_size);

signals:
    void operate(const QString &);
    void send_commands_SIGNAL(QByteArray _packet);

    void device_conflict(QList <QSerialPortInfo> all_ports);

    void log_RX_packet_decoded_SIGNAL(QList<QString> decoded);
    void log_TX_packet_decoded_SIGNAL(QList<QString> decoded);
    void log_RX_packet_raw_SIGNAL(QByteArray raw);
    void log_TX_packet_raw_SIGNAL(QByteArray raw);

    void RX_Hz_updated(float RX_Hz_average);
    void TX_Hz_updated(float TX_Hz_average);

    void updatedReadQueueSize(int read_queue_size);

};

#endif // SERIAL_MANAGER_H
